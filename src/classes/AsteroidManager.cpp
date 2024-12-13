#include "AsteroidManager.h"

void AsteroidManager::initAstroid()
{
    this->spawnTimerMax = 50.0f;
}

void AsteroidManager::loadAudioFiles()
{
    if (!this->destructionBuffer.loadFromFile(settings::destructionAudio)) {
    std::cerr << "Error loading destruction sound!" << std::endl;
    }
    sf::Sound destructionSound;
    this->destructionSound.setBuffer(destructionBuffer);
    this->destructionSound.setVolume(20); // Set volume (0.0f to 100.0f)
}

AsteroidManager::AsteroidManager()
{  
    this->score = 0;
    this->loadAudioFiles();
    this->initAstroid();
    this->spawnTimer = 0.0f;
}

AsteroidManager::~AsteroidManager()
{

    for(auto *asteroid : asteroids){
        delete asteroid;
    }
}

void AsteroidManager::setWindow(sf::RenderWindow* window)
{
    this->window = window;
}

int AsteroidManager::getScore()
{
    return this->score;
}

void AsteroidManager::handleCircleCollisons(std::vector<settings::Circle> objects)
{
    for(Asteroid* asteroid : this->asteroids)
    {
        for(settings::Circle& object: objects)
        {
            sf::Vector2f asteroidCoord = asteroid->getBounds().getPosition();
            sf::Vector2f asteroidSize = asteroid->getBounds().getSize();
            bool collide = false;
            sf::Vector2f closestPos;
            closestPos.x = std::min(asteroidCoord.x + asteroidSize.x ,std::max(object.pos.x,asteroidCoord.x));
            closestPos.y = std::min(asteroidCoord.y + asteroidSize.y ,std::max(object.pos.y,asteroidCoord.y));
            float distanceFromCenter = ((closestPos.x-object.pos.x)*(closestPos.x-object.pos.x)) + ((closestPos.y-object.pos.y)*(closestPos.y-object.pos.y));
            // when circle and rectangle intersect or rectangle is inside the circle
            if(distanceFromCenter < object.r * object.r) collide = true;
            // when circle is inside the rectangle
            else if(
                (object.pos.x > asteroidCoord.x) && 
                (object.pos.x < asteroidCoord.x + asteroidSize.x) && 
                (object.pos.y > asteroidCoord.y) && 
                (object.pos.y < asteroidCoord.y + asteroidSize.y)) collide = true;
            if(collide)
            {
                asteroid->decreaseHP();
            }
        }
    }
}

void AsteroidManager::updateAsteroids()
{
    //generating a random asteroid at spawm time
    for(int i =0; i<this->asteroids.size();i++)
    {
        if(this->asteroids[i]->getHP() <= 0)
        {
            destructionSound.play();
            this->score+=asteroids[i]->getPoints();
            delete asteroids[i];
            asteroids.erase(this->asteroids.begin()+i);
            i--;
        }
    }
    for(Asteroid* asteroid : asteroids)
    {
        asteroid->update();
    }

}
bool AsteroidManager::checkGameOver()
{
    for(Asteroid* asteroid: asteroids)
    {
        if(asteroid->getBounds().getPosition().y >= settings::earthYPositon) return true;
    }
    return false;
}

void AsteroidManager::render()
{
    for(auto *asteroid : asteroids){
        asteroid->render(*this->window);
    }
}
void AsteroidManager::spawnAsteroids()
{
    this->spawnTimer += 0.1f;
    int collisonHappened = false;
    if(this->spawnTimer >=spawnTimerMax){
        this->asteroids.push_back(new Asteroid(rand() % (this->window->getSize().x - 100),-100.f, rand() % 3));
        this->spawnTimer =0.0f;
    }

}