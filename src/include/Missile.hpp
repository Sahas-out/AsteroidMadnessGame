#pragma once
#include<SFML/Graphics.hpp>
#include"GameUtils.hpp"
class Missile
{
    private:
        sf::Vector2f position;
        sf::Vector2f direction;
        sf::Vector2f targetPositon;
    public:
        enum class State
        {
            ALIVE,
            EXLPODE,
            DEAD
        };
        Missile(sf::Vector2f inPosition,sf::Vector2f inTargetPosition);
        void move();
        void updateState();
        virtual void explode();
        virtual void draw(sf::RenderWindow &window);
        const sf::Vector2f& getPositon();
        const sf::Vector2f& getTargetPositon();
        virtual settings::Circle getBounds();
        State getState();
        const sf::Vector2f& getDirection();
        ~Missile();
    protected: 
        double speed;
        double blastRadius;
        State state;
        int explodeDuration;

}; 

class NormalMissile : public Missile
{
    private:
        sf::VertexArray line;
        sf::CircleShape aliveCircle;
        sf::CircleShape explodeCircle;
    public:
        NormalMissile(sf::Vector2f inPosition,sf::Vector2f inTargetPosition);
        void draw(sf::RenderWindow &window) override;
        void explode() override;
        settings::Circle getBounds() override;
        ~NormalMissile();
};

class BigMissile : public Missile
{
    private:
        sf::VertexArray line;
        sf::CircleShape aliveCircle;
        sf::CircleShape explodeCircle;
    public:
        BigMissile(sf::Vector2f inPosition,sf::Vector2f inTargetPosition);
        void draw(sf::RenderWindow &window) override;
        void explode() override;
        settings::Circle getBounds() override;
        ~BigMissile();
};

class NukeMissile : public Missile
{
    private:
        sf::VertexArray line;
        sf::CircleShape aliveCircle;
        sf::CircleShape explodeCircle;
        double increaseFactor;
    public:
        NukeMissile(sf::Vector2f inPosition,sf::Vector2f inTargetPosition);
        void draw(sf::RenderWindow &window) override;
        void explode() override;
        settings::Circle getBounds() override;
        ~NukeMissile();
};

class LineMissile : public Missile
{
    private:
        sf::VertexArray line;
        sf::CircleShape aliveCircle;
        sf::CircleShape explodeCircle;
        double explodeCircleSpeed;
        double reduceFactor;
    public:
        LineMissile(sf::Vector2f inPosition,sf::Vector2f inTargetPosition);
        void draw(sf::RenderWindow &window) override;
        void explode() override;
        settings::Circle getBounds() override;
        ~LineMissile();
};