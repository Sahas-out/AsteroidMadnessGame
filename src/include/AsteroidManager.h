#pragma once

#include "Asteroid.h"
#include "GameUtils.hpp"
#include "MissileManager.hpp"
#include <SFML/Audio.hpp>
class AsteroidManager
{
private:
    sf::RenderWindow* window;

    int score;
    float spawnTimer;
    float spawnTimerMax;
    std::vector<Asteroid*> asteroids; 
    
    //Audio Effects
    sf::SoundBuffer destructionBuffer;
    sf::Sound destructionSound;

    //private functions
    void initAstroid();
    void loadAudioFiles();


public:
    bool gameOver = false;
    AsteroidManager();
    virtual ~AsteroidManager();

    int getScore();
    void handleCircleCollisons(std::vector<settings::Circle> objects);
    void spawnAsteroids();
    bool checkGameOver();
    void setWindow(sf::RenderWindow*);
    void updateAsteroids();
    void render();
};