#include "Asteroid.h"
#include "GameUtils.hpp"

void Asteroid::initTexture()
{
    //load texture form file    
    if(this->type == "Normal"){
        if(!this->texture.loadFromFile(settings::asteroid_textureFiles[0]))
        {
            std::cout << "Error: couldn't load Astroid texture.";
        }
    }
    else if(this->type == "Quick"){
        if(!this->texture.loadFromFile(settings::asteroid_textureFiles[1]))
        {
            std::cout << "Error: couldn't load Astroid texture.";
        }
    }
    else if(this->type == "Strong"){
        if(!this->texture.loadFromFile(settings::asteroid_textureFiles[2]))
        {
            std::cout << "Error: couldn't load Astroid texture.";
        }
    }
}

void Asteroid::initSprite()
{
    //set the texture to the sprite
    this->sprite.setTexture(this->texture);
    this->sprite.scale(scale,scale);
    // this->mask = generatePixelMask(texture);
}


void Asteroid::initAttributes(int type)
{
    
    if (type == 0){
        this->type = "Normal"; 
        this->speed = 2.0f;
        this->hp = 20*(settings::fps/3);
        this->maxHp = 20*(settings::fps/3);
        this->pointsAwarded = 10;
        this->scale = 0.5f;
    }
    else if (type == 1)
    {
        this->type = "Quick"; 
        this->speed = 4.0f;
        this->hp = 10*(settings::fps/3);
        this->maxHp = 10*(settings::fps/3);
        this->pointsAwarded = 20;
        this->scale = 0.3f;
    }
    else if (type == 2){
        this->type = "Strong"; 
        this->speed = 1.0f;
        this->hp = 30*(settings::fps/3);
        this->maxHp = 30*(settings::fps/3);
        this->pointsAwarded = 30;
        this->scale = 0.1f;
    }
    
}

Asteroid::Asteroid(float pos_x,float pos_y,int type)
:sprite(),texture(){
    this->initAttributes(type);
    this->initTexture();
    this->initSprite();
    this->sprite.setPosition(pos_x,pos_y);
    this->spriteColor = sprite.getColor();
}

Asteroid::~Asteroid()
{
}

const sf::FloatRect Asteroid::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

int Asteroid::getHP()
{
    return hp;
}

void Asteroid::decreaseHP()
{
    this->hp -= 10;
}

int Asteroid::getPoints()
{
    return this->pointsAwarded;
}

void Asteroid::update()
{
    this->sprite.move(0.0f,this->speed);
}

void Asteroid::render(sf::RenderTarget &target)
{
    sf::Color fadedColor = this->spriteColor;
    fadedColor.a = (int)((((255.0f - 128.0f)/(this->maxHp ))*this->hp) + 128.0f);
    this->sprite.setColor(fadedColor);
    target.draw(this->sprite);
}

sf::Sprite Asteroid::getSprite()
{
    return this->sprite;
}

