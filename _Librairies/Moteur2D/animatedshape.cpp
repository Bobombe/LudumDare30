#include "animatedshape.h"

AnimatedShape::AnimatedShape(ShapeType shapeType, sf::Vector2f pos, sf::Vector2f vit) : FixedShape(shapeType, pos), AnimatedObject(vit)
{
    //ctor
}
AnimatedShape::AnimatedShape(float radius, sf::Vector2f pos, sf::Vector2f vit) : FixedShape(radius, pos), AnimatedObject(vit)
{
}
AnimatedShape::AnimatedShape(sf::Vector2f size, sf::Vector2f pos, sf::Vector2f vit) : FixedShape(size, pos), AnimatedObject(vit)
{
}

AnimatedShape::~AnimatedShape()
{
    //dtor
}
