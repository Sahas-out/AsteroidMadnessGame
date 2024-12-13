#include "Missile.hpp"
Missile::Missile(sf::Vector2f inPosition,sf::Vector2f inTargetPosition)
{
    position = inPosition;
    targetPositon = inTargetPosition;
    
    direction = targetPositon - inPosition;
    settings::normalise(&direction);
    speed = settings::missileSpeed;
    blastRadius = 30;
    explodeDuration = settings::fps/2;
    state = State::ALIVE;
}
void Missile::move()
{
    if(state != State::ALIVE){return;}
    position = position + settings::scalarProduct(direction,speed);
}
void Missile::updateState()
{
    if(state == State::ALIVE && settings::dotProduct(targetPositon - position,direction) <= 0)
    {
        state = State::EXLPODE;
    }
    else if (state == State::EXLPODE && explodeDuration <= 0)
    {
        state = State::DEAD;
    }
    return;
}
void Missile::draw(sf::RenderWindow &window)
{
    
}
void Missile::explode()
{
    if(state != State::EXLPODE){return;}
    explodeDuration--;
}
Missile::~Missile()
{
    
}
const sf::Vector2f& Missile::getPositon()
{
    return position;
}
const sf::Vector2f& Missile::getTargetPositon()
{
    return targetPositon;
}
Missile::State Missile::getState()
{
    return state;
}
settings::Circle Missile::getBounds()
{
    return settings::Circle();
}
const sf::Vector2f& Missile::getDirection()
{
    return direction;
}



NormalMissile::NormalMissile(sf::Vector2f inPosition,sf::Vector2f inTargetPosition)
:Missile(inPosition,inTargetPosition),
line(sf::Lines,2),
aliveCircle(settings::missileAliveCircleRadius),
explodeCircle()
{
    this->blastRadius=50;
    this->explodeDuration = settings::fps/2;
    line[0].position = inPosition;
    line[0].color = sf::Color::White;
    line[1].position = getPositon();
    line[1].color = sf::Color::Red;
    this->explodeCircle.setRadius(blastRadius);
    aliveCircle.setFillColor(sf::Color::Blue);
    explodeCircle.setFillColor(sf::Color::White);
    explodeCircle.setPosition(getTargetPositon() - sf::Vector2f(blastRadius,blastRadius));
}

void NormalMissile::explode()
{
    if(state != State::EXLPODE){return;}
    explodeDuration--;
}

void NormalMissile::draw(sf::RenderWindow &window)
{
    if(state == State::ALIVE)
    {
        line[1].position = getPositon();
        aliveCircle.setPosition(getPositon() - sf::Vector2f(aliveCircle.getRadius(),aliveCircle.getRadius()));
        window.draw(line);
        window.draw(aliveCircle);
    }
    if(state == State::EXLPODE)
    {

        window.draw(explodeCircle);
    }
}
settings::Circle NormalMissile::getBounds()
{
    if(state != State::EXLPODE){return settings::Circle();}
    return settings::Circle(blastRadius,this->getTargetPositon());
}
NormalMissile::~NormalMissile()
{
    
}

BigMissile::BigMissile(sf::Vector2f inPosition,sf::Vector2f inTargetPosition)
:Missile(inPosition,inTargetPosition),
line(sf::Lines,2),
aliveCircle(settings::missileAliveCircleRadius),
explodeCircle()
{
    
    blastRadius = 120;
    this->explodeDuration = settings::fps/2;
    explodeCircle.setRadius(blastRadius);
    line[0].position = inPosition;
    line[0].color = sf::Color::White;
    line[1].position = getPositon();
    line[1].color = sf::Color::Green;
    aliveCircle.setFillColor(sf::Color::Yellow);
    explodeCircle.setFillColor(sf::Color::White);
    explodeCircle.setPosition(getTargetPositon() - sf::Vector2f(blastRadius,blastRadius));
}
void BigMissile::explode()
{
    if(state != State::EXLPODE){return;}
    explodeDuration--;
}
void BigMissile::draw(sf::RenderWindow &window)
{
    if(state == State::ALIVE)
    {
        line[1].position = getPositon();
        aliveCircle.setPosition(getPositon() - sf::Vector2f(aliveCircle.getRadius(),aliveCircle.getRadius()));
        window.draw(line);
        window.draw(aliveCircle);
    }
    if(state == State::EXLPODE)
    {

        window.draw(explodeCircle);
    }
}
settings::Circle BigMissile::getBounds()
{
    if(state != State::EXLPODE){return settings::Circle();}
    return settings::Circle(blastRadius,this->getTargetPositon());
}

BigMissile::~BigMissile()
{

}

NukeMissile::NukeMissile(sf::Vector2f inPosition,sf::Vector2f inTargetPosition)
:Missile(inPosition,inTargetPosition),
line(sf::Lines,2),
aliveCircle(settings::missileAliveCircleRadius),
explodeCircle()
{   
    this->blastRadius=120;
    this->explodeDuration=settings::fps*1.5;
    this->increaseFactor=(500-this->blastRadius)/this->explodeDuration;
    this->explodeCircle.setRadius(blastRadius);
    line[0].position = inPosition;
    line[0].color = sf::Color::White;
    line[1].position = getPositon();
    line[1].color = sf::Color::Blue;
    aliveCircle.setFillColor(sf::Color::Cyan);
    explodeCircle.setFillColor(sf::Color::White);
    explodeCircle.setPosition(getTargetPositon() - sf::Vector2f(blastRadius,blastRadius));
}

void NukeMissile::explode()
{
    if(state != State::EXLPODE){return;}
    blastRadius += increaseFactor;
    explodeCircle.setRadius(blastRadius);
    explodeCircle.setPosition(getTargetPositon() - sf::Vector2f(blastRadius,blastRadius));
    explodeDuration--;
}

void NukeMissile::draw(sf::RenderWindow &window)
{
    if(state == State::ALIVE)
    {
        line[1].position = getPositon();
        aliveCircle.setPosition(getPositon()- sf::Vector2f(aliveCircle.getRadius(),aliveCircle.getRadius()));
        window.draw(line);
        window.draw(aliveCircle);
    }
    if(state == State::EXLPODE)
    {

        window.draw(explodeCircle);
    }
}
settings::Circle NukeMissile::getBounds()
{
    if(state != State::EXLPODE){return settings::Circle();}
    return settings::Circle(blastRadius,this->getTargetPositon());
}
NukeMissile::~NukeMissile()
{
    
}

LineMissile::LineMissile(sf::Vector2f inPosition,sf::Vector2f inTargetPosition)
:Missile(inPosition,inTargetPosition),
line(sf::Lines,2),
aliveCircle(settings::missileAliveCircleRadius),
explodeCircle()
{   
    this->explodeDuration=settings::fps*0.8;
    this->blastRadius=125;
    this->reduceFactor=(blastRadius-30)/explodeDuration;
    this->explodeCircle.setRadius(blastRadius);
    line[0].position = inPosition;
    line[0].color = sf::Color::White;
    line[1].position = getPositon();
    line[1].color = sf::Color::Magenta;
    aliveCircle.setFillColor(sf::Color::Red);
    explodeCircle.setFillColor(sf::Color::White);
    explodeCircle.setPosition(getTargetPositon() - sf::Vector2f(blastRadius,blastRadius));
    this->explodeCircleSpeed = this->speed * 0.4;
}

void LineMissile::explode()
{
    if(state != State::EXLPODE){return;}
    sf::Vector2f newCenterPos = explodeCircle.getPosition() + (sf::Vector2f(blastRadius,blastRadius)) + settings::scalarProduct(this->getDirection(),explodeCircleSpeed);
    blastRadius -= reduceFactor;
    explodeCircle.setRadius(blastRadius);
    explodeCircle.setPosition(newCenterPos  - sf::Vector2f(blastRadius,blastRadius));
    explodeDuration--;
}

void LineMissile::draw(sf::RenderWindow &window)
{
    if(state == State::ALIVE)
    {
        line[1].position = getPositon();
        aliveCircle.setPosition(getPositon()- sf::Vector2f(aliveCircle.getRadius(),aliveCircle.getRadius()));
        window.draw(line);
        window.draw(aliveCircle);
    }
    if(state == State::EXLPODE)
    {

        window.draw(explodeCircle);
    }
}
settings::Circle LineMissile::getBounds()
{
    if(state != State::EXLPODE){return settings::Circle();}
    return settings::Circle(blastRadius,explodeCircle.getPosition() + sf::Vector2f(blastRadius,blastRadius));
}
LineMissile::~LineMissile()
{
    
}