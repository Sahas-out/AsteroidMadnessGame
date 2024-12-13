#include"GameUtils.hpp"


const double settings::dotProduct(sf::Vector2f a,sf::Vector2f b)
    {
        return ((a.x * b.x) +(a.y * b.y));
    }
settings::Circle::Circle(float radius,sf::Vector2f position)
{
    this->r = radius;
    this->pos = position;
}
settings::Circle::Circle()
{
    this->r = 0;
    this->pos = sf::Vector2f(0,0);
}
const void settings::normalise(sf::Vector2f* vector)
{
    double magnitude = sqrt((vector->x*vector->x)+(vector->y*vector->y));
    vector->x /= magnitude;
    vector->y /= magnitude;
}
const sf::Vector2f settings::scalarProduct(sf::Vector2f vector,float scalar)
{
    vector.x *= scalar;
    vector.y *= scalar;
    return vector;
}