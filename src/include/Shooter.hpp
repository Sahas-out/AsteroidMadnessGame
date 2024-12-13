#pragma once

#include<SFML/System.hpp>
#include"Missile.hpp"
#include<SFML/Graphics.hpp>
#include<cmath>
#include<vector>
#include<SFML/Audio.hpp>
class Shooter
{
    private:
        sf::Clock  fireInterval;
        int cooldownPeriod;
        bool    cooldownEnabled;
        settings::missileType  attachedMissile;
        bool    onStart;
    protected:
        enum class State
        {
            LOCKED,
            ACTIVE,
            INACTIVE
        };
        sf::Sound missileLaunchSound;
        sf::SoundBuffer missileLaunchBuffer;
        sf::Vector2f position;
        State state;
        sf::Sprite lock;
        sf::Texture lockTexture;
        sf::Sprite invalidSign;
        sf::Texture invalidSignTexture;
    public:
        Shooter(sf::Vector2f inPosition,settings::missileType inMissile ,int  inCooldownPeriod = settings::defaultCooldown);
        void toggleCooldown(bool active);
        void setCooldownPeriod(int  t);
        void checkState();
        void resetTimer();
        virtual std::vector<Missile*> shoot(sf::Vector2f targetPosition);
        virtual void draw(sf::RenderWindow& window );
        virtual void makeAbstract() = 0;
        void unlock();
        Missile* addMissile(sf::Vector2f shooterSize,sf::Vector2f targetPosition);
};

class NormalShooter:public Shooter
{
    private:
        //sf::ConvexShape* graphic;
        sf::Sprite graphics;
        sf::Texture graphicTexture;
        settings::shooterType type;
        sf::Sprite fadedGraphics;
        void setInvalidSign();
        void setLock();
    public:
        NormalShooter(sf::Vector2f inPosition,settings::missileType inMissile,std::string displayImageLocation,int  inCooldownPeriod = settings::defaultCooldown);
        std::vector<Missile*> shoot(sf::Vector2f targetPosition) override;
        void draw(sf::RenderWindow & window) override;
        void makeAbstract() override;
};
class SpreadShooter:public Shooter
{
    private:
        settings::shooterType type;
        sf::Sprite graphics;
        sf::Texture graphicTexture;
        int missileCount ;
        double spread;
        sf::Sprite fadedGraphics;
        void setInvalidSign();
        void setLock();
    public:
        SpreadShooter(sf::Vector2f inPosition,settings::missileType inMissile,std::string displayImageLocation,int  inCooldownPeriod = settings::spreadCooldown);
        std::vector<Missile*> shoot(sf::Vector2f targetPosition) override;
        void draw(sf::RenderWindow & window) override;
        void makeAbstract() override;

};
class RapidShooter:public Shooter
{
    private:
        settings::shooterType type;
        int missileCount;
        sf::Sprite graphics;
        sf::Texture graphicTexture;
        sf::Sprite fadedGraphics;
        void setInvalidSign();
        void setLock();

    public:
        RapidShooter(sf::Vector2f inPosition,settings::missileType inMissile,std::string displayImageLocation,int  inCooldownPeriod = settings::rapidCooldown);
        std::vector<Missile*> shoot(sf::Vector2f targetPosition) override;
        void draw(sf::RenderWindow & window) override;
        void makeAbstract() override;

};
