#include "animatedobject.h"
#include "moteur2d.h"
#include <iostream>

AnimatedObject::AnimatedObject(sf::Vector2f vit) : FixedObject(false)
{
    //ctor
    m_vit = vit;
    Moteur2D::getInstance()->addAnimatedObject(this);
}

AnimatedObject::~AnimatedObject()
{
    //dtor
    Moteur2D::getInstance()->deleteAnimatedObject(this);
}
//*
void AnimatedObject::update(float seconds)
{
    // Calcule la nouvelle position sans collision
    sf::Vector2f oldPos = getPosition();
    sf::Vector2f newPos = oldPos+m_vit*seconds;
    setPosition( newPos);

    if (true)//m_isCollidable)
    {
        //setPosition(checkCollision(seconds));
        checkCollision(seconds, oldPos);
    }
    else
    {
        setPosition(getPosition()+m_vit*seconds);
    }
}


//sf::Vector2f
void AnimatedObject::checkCollision(float seconds, sf::Vector2f oldPos)
{
    sf::Vector2f newPos = getPosition();


    // Pour chaque objets
    // Collisions avec les objets fixes
    std::vector <FixedObject*> fos = Moteur2D::getInstance()->getFixedObjects();
    for (unsigned int i = 0; i<fos.size(); i++)
    {
        FixedObject* fo = fos.at(i);
        if ((*fo)!=(*this) /*&& fo->isCollidable()*/ && collideWith(fo))
        {
            // On traite la collision
            applyCollision(fo, oldPos);
            return ;
        }

    }
    // Collisions avec les objets mouvants.
    std::vector <AnimatedObject*> aos = Moteur2D::getInstance()->getAnimatedObjects();
    for (unsigned int i = 0; i<aos.size(); i++)
    {
        AnimatedObject* ao = aos.at(i);
        if ((*ao)!=(*this) && /*ao->isCollidable() &&*/ collideWith(ao))
        {
            // On traite la collision
            applyCollision(ao, oldPos);
            return;
        }
    }
    // Collisions avec les arrière plans concrets.
    std::vector <ConcreteBackground*> cbs = Moteur2D::getInstance()->getConcreteBackgrounds();
    for (unsigned int i = 0; i<cbs.size(); i++)
    {
        ConcreteBackground* cb = cbs.at(i);
        if (cb->collidedBy(this, newPos))
        {
            // On traite la collision
            m_vit.x=0;
            m_vit.y=0;
            setPosition( oldPos);
            return;
        }
    }
}

void AnimatedObject::applyCollision(FixedObject * fo, sf::Vector2f oldPos)
{
    m_vit.x=0;
    m_vit.y=0;
    setPosition( oldPos);
}

bool AnimatedObject::collideWith(const sf::FloatRect &other, const sf::Vector2f & newPos)
{
    sf::FloatRect r = getBox();
    sf::Vector2f p = getPosition();

    float left1 = newPos.x-p.x+r.left;
    float top1 = newPos.y-p.y+r.top;
    float right1 = left1+r.width;
    float bottom1 = top1+r.height;

    float bottom2 = other.top+other.height;
    float right2 = other.left+other.width;


    return ! (
    (bottom1 < other.top) ||
    (top1 > bottom2) ||
    (left1 > right2) ||
    (right1 < other.left) );

}


bool AnimatedObject::collideWith(FixedObject * fo)
{
    sf::FloatRect foBox = fo->getBox();

// Point Haut/Gauche se place en haut à gauche de la bbox
    sf::Vector2f posUL = sf::Vector2f(m_bBox.left, m_bBox.top);

    sf::Vector2f posDR = posUL;
    posDR.x+=m_bBox.width;
    posDR.y+=m_bBox.height;

    // Si hors de l'objet
    if (posDR.x<foBox.left || posDR.y <foBox.top || posUL.x>foBox.width+foBox.left || posUL.y>foBox.height+foBox.top)
    {
        return false;
    }
    //Si Point Haut/gauche trop en haut/gauche
    if (posUL.x<foBox.left)
    {
        posUL.x=foBox.left;
    }
    if (posUL.y<foBox.top)
    {
        posUL.y=foBox.top;
    }

    //Si Point Bas/droite trop en Bas/droite
    if (posDR.x>foBox.width+foBox.left)
    {
        posDR.x=foBox.width+foBox.left;
    }
    if (posDR.y>foBox.height+foBox.top)
    {
        posDR.y=foBox.height+foBox.top;
    }

    // Les positions sont en coordonées globales
    for (int i = posUL.x; i <posDR.x; i++)
    {
        for (int j = posUL.y; j <posDR.y; j++)
        {
            if (isCollidablePoint(sf::Vector2f(i, j)) && fo->isCollidablePoint(sf::Vector2f(i, j)))
            {
                return true;
            }
        }
    }
    return false;

}

//*/










