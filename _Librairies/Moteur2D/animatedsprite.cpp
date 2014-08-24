#include "animatedsprite.h"
#include <iostream>
#include "moteur2d.h"

AnimatedSprite::AnimatedSprite() : FixedObject(false)
{
    //ctor
    //m_vit = sf::Vector2f(0, 0);
}

AnimatedSprite::AnimatedSprite(const std::string& imagePath, const sf::Vector2f& pos, sf::Vector2f vit) :FixedObject(false), FixedSprite(pos, imagePath, false), AnimatedObject(vit)
{
    //ctor
    //m_vit = sf::Vector2f(0, 0);
}

AnimatedSprite::AnimatedSprite(const sf::Vector2f& pos, const std::string& imagePath) : FixedObject(false), FixedSprite(pos, imagePath, false)
{
    //ctor
    //m_vit = sf::Vector2f(0, 0);
}

AnimatedSprite::~AnimatedSprite()
{
    //dtor

}

/*
void AnimatedSprite::update(float seconds)
{
    m_sprite->setPosition(collisionTest(seconds));
}
sf::Vector2f AnimatedSprite::collisionTest(float s)
{
    // Calcule la nouvelle position sans collision
    sf::Vector2f newPos = m_sprite->getPosition()+m_vit*s;

    // Pour chaque objets
    // Collisions avec les objets fixes
    std::vector <FixedObject*> fos = Moteur2D::getInstance()->getCollidables();
    for (unsigned int i = 0; i<fos.size(); i++)
    {
        FixedObject* fo = fos.at(i);
        if (fo!=this && collideWith(fo->getBox(), newPos))
        {
            // On traite la collision
            m_vit.x=0;
            m_vit.y=0;
            return m_sprite->getPosition();
        }
    }
    // Collisions avec les objets mouvants.
    std::vector <AnimatedSprite*> ass = Moteur2D::getInstance()->getAnimatedSprites();
    for (unsigned int i = 0; i<ass.size(); i++)
    {
        AnimatedSprite* as = ass.at(i);
        if (as!=this && collideWith(as->getBox(), newPos))
        {
            // On traite la collision
            m_vit.x=0;
            m_vit.y=0;
            return m_sprite->getPosition();
        }
    }
    return newPos;
}

bool AnimatedSprite::collideWith(const sf::FloatRect &other, const sf::Vector2f & newPos)
{
    float bottom1 = newPos.y+m_sprite->getGlobalBounds().height;
    float right1 = newPos.x+m_sprite->getGlobalBounds().width;
    float bottom2 = other.top+other.height;
    float right2 = other.left+other.width;


    return ! (
    (bottom1 < other.top) ||
    (newPos.y > bottom2) ||
    (newPos.x > right2) ||
    (right1 < other.left) );

}
//*/

















