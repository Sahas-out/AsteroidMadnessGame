#include"MissileManager.hpp"
MissileManager::MissileManager(sf::RenderWindow* inWindow)
:window(inWindow)
{

}
void MissileManager::addMissile(std::vector<Missile*> newMissileList)
{
    for(auto missile: newMissileList)
    {
        this->missileList.push_back(missile);
    }
}

std::vector<settings::Circle> MissileManager::getAllBounds()
{
    std::vector<settings::Circle> bounds;
    for(auto missile: this->missileList)
    {
        if(missile->getState() == Missile::State::EXLPODE)
        {
            bounds.push_back(missile->getBounds());
        }
    }
    return bounds;
}
void MissileManager::executeMissileBehaviour()
{
    std::vector<int> missilesToDelete;
    for(int i=0; i<this->missileList.size(); i++)
    {
        Missile* missile = this->missileList[i];
        if(missile->getState() == Missile::State::ALIVE)
        {
            missile->move();
        }
        else if (missile->getState() == Missile::State::EXLPODE)
        {
            missile->explode();
        }
        else
        {
            this->missileList.erase(this->missileList.begin() + i);
            i--;
        }
    }

}
void MissileManager::updateStatus()
{
    for(auto missile: this->missileList)
    {
        missile->updateState();
    }
}

MissileManager::~MissileManager()
{
    this->missileList.clear();
}


void MissileManager::render()
{
    for(auto missile: this->missileList)
    {
        missile->draw(*this->window);
    }
}
