#include"ShooterManager.hpp"
ShooterManager::ShooterManager(sf::RenderWindow * inWindow):window(inWindow){
    unlockCounter = -1;
    ShootersYPositon = settings::windowHeight * 0.9f;
    float margin = 50;
    float spaceBetween = (settings::windowWidth - (2*margin) - settings::shooterWidth) / (settings::totalShootersCount -1 );
    for(int i =0; i<settings::totalShootersCount;i++)
    {
        coordinates.push_back(sf::Vector2f((i*spaceBetween)+margin,ShootersYPositon));
    }
    NormalShooter* crap = new NormalShooter(coordinates[3],settings::missileType::normalMissile,settings::shooter1,settings::fps*0.5);
    NormalShooter * alright = new NormalShooter(coordinates[2],settings::missileType::bigMissile,settings::shooter2,settings::fps*2);
    RapidShooter * ohh = new RapidShooter(coordinates[4],settings::missileType::lineMissile,settings::shooter3,settings::fps*3);
    NormalShooter * woahhh= new NormalShooter(coordinates[1],settings::missileType::nukeMissile,settings::shooter4,settings::fps*10);
    SpreadShooter * awesome= new SpreadShooter(coordinates[5],settings::missileType::bigMissile,settings::shooter5,settings::fps*5);
    SpreadShooter * goat = new SpreadShooter(coordinates[0],settings::missileType::lineMissile,settings::shooter6,settings::fps*8);
    RapidShooter * perfect = new RapidShooter(coordinates[6],settings::nukeMissile,settings::shooter7,settings::fps*10);
    this->shooterList.insert(shooterList.end(),{crap,alright,ohh,woahhh,awesome,goat,perfect});
    
    this->unlockNext();
    this->unlockNext();
    this->unlockNext();
    this->unlockNext();
    this->unlockNext();
    this->unlockNext();
    this->unlockNext();

    shooterCursorTexture.loadFromFile(settings::shooterCursorImage);
    shooterCursorGraphics.setTexture(shooterCursorTexture);

    float width = 75;
    float height = width / (shooterCursorTexture.getSize().x / (float)shooterCursorTexture.getSize().y);
    shooterCursorGraphics.setScale(width / shooterCursorTexture.getSize().x, height / shooterCursorTexture.getSize().y);
    this->selectShooter(3);
}
    void ShooterManager::render(){
        sf::Vector2f cursorPos = coordinates[this->getCurrentShooter()] + 
        sf::Vector2f(
            (settings::shooterWidth/2) - (shooterCursorGraphics.getGlobalBounds().getSize().x/2),
        -10 - shooterCursorGraphics.getGlobalBounds().getSize().y);
        shooterCursorGraphics.setPosition(cursorPos);
        for(auto  shooter : shooterList) {shooter->draw(*window);};
        window->draw(shooterCursorGraphics);
    }
    std::vector<Missile*> ShooterManager::shoot(sf::Vector2f target){
        return shooterList[currentShooter]->shoot(target);
    }
    void ShooterManager::selectShooter(int index){
        this->currentShooter = this->positionsToOrder[index];
    }
    void ShooterManager:: unlockNext(){
        shooterList[++unlockCounter]->unlock();
    }
    int ShooterManager::getCurrentShooter()
    {
        
        int position;
        for(position =0 ; position< positionsToOrder.size();position++)
        {
            if(positionsToOrder[position] == currentShooter) return position;
        }
        return -1;
    }