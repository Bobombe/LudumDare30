#include "planete.h"
#include <typeinfo>

Planete::Planete(std::string image, sf::Vector2f pos, sf::Vector2f vit) : FixedObject(false), AnimatedSprite(image, pos, vit)
{
    //ctor

    try
    {
        sf::Sprite& c = dynamic_cast<sf::Sprite&>(*m_drawableObject);
        c.setOrigin(25, 25);
        setScale(2.);
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

Planete::~Planete()
{
    //dtor
}



void Planete::applyCollision(FixedObject * fo, sf::Vector2f oldPos)
{

}



