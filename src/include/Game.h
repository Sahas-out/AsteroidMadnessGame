#pragma once
#include <AsteroidManager.h>
#include"MissileManager.hpp"
#include"ShooterManager.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
extern "C"
{
class Game
{
    private:
        sf::RenderWindow* window;
        AsteroidManager* asteroidManager;
        ShooterManager* shooterManager;
        MissileManager* missileManager;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Cursor cursor;
        sf::Image cursorImage;
        sf::Music backgroundMusic;
    
        //score
        sf::Font font;
        std::ostringstream scoreStream;
        sf::Text scoreText;
        int score;
        int highScore;
        bool gameOver;
        sf::Text gameOverText;
    public:
        void initWindow();
        void initScore();
        void clearScreen();
        void displayScore();
        void initBackground();
        void handleKeys(sf::Event & event);
        void setHighScore(int highScore);
        void run();
        int getHighScore();
        Game();
        ~Game();
    

};
}
