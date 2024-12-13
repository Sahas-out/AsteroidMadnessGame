#pragma once

#include"Shooter.hpp"
#include<vector>
class ShooterManager{
    private : 
        std::vector<Shooter*>shooterList;
        int currentShooter;
        int unlockCounter;
        sf::RenderWindow *window;
        int totalShootersCount;
        std::vector<sf::Vector2f>coordinates;
        float ShootersYPositon;
        sf::Sprite shooterCursorGraphics;
        sf::Texture shooterCursorTexture;
        std::vector<int> positionsToOrder = {5,3,1,0,2,4,6};  
    public:
    ShooterManager(sf::RenderWindow *inWindow);
    void render();
    std::vector<Missile*> shoot(sf::Vector2f target);
    void selectShooter(int index);
    void unlockNext();
    int getCurrentShooter();

};