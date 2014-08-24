#include "concretebackground.h"
#include "moteur2d.h"
#include <iostream>
#include <typeinfo>

ConcreteBackground::ConcreteBackground(const std::string& imagePath)
{
    //ctor
    m_sprite = 0;
    if (imagePath!="")
    {
        m_sprite = new sf::Sprite;
        m_sprite->setTexture(*Moteur2D::getInstance()->getTexture(imagePath));
        m_image = m_sprite->getTexture()->copyToImage();
    }
    Moteur2D::getInstance()->addConcreteBackground(this);
}

ConcreteBackground::~ConcreteBackground()
{
    //dtor
    if (m_sprite)
        delete m_sprite;
}

bool ConcreteBackground::collidedBy(AnimatedObject * ao, const sf::Vector2f & newObjectPos)
{
    if (!m_sprite)
        return false;



    sf::FloatRect bbox=ao->getBox();
    //sf::Vector2f oldPos = ao->getPosition();
    /*/ Si c'est un Sprite
    try
    {
        sf::Sprite& sprite = dynamic_cast<sf::Sprite&>(*ao->getDrawableObject());

        sf::Image image = sprite.getTexture()->copyToImage();
        sf::Vector2f m= Moteur2D::getInstance()->getView()->getMouseInWorld();

        m=sprite.getTransform().getInverse().transformPoint(m);
        if(m.x>0 && m.y>0&& m.x<image.getSize().x && m.y<image.getSize().y)
    }
    catch (const std::bad_cast& e)
    {
        //std::cerr << e.what() << std::endl;
    }//*/

    // Point Haut/Gauche se place en haut à gauche de la bbox
    sf::Vector2f posUL = sf::Vector2f(bbox.left, bbox.top);
    //posUL += newObjectPos-oldPos;//on le déplace selon le mouvement de l'objet
    //Si ligne suivante commentée, on reste en coordonnées globales
    //posUL-=m_sprite->getPosition();//on le met dans les coordonnées du background

    sf::Vector2f posDR = posUL;
    posDR.x+=ao->getBox().width;
    posDR.y+=ao->getBox().height;

    sf::FloatRect sBB = m_sprite->getGlobalBounds();

    // Si hors du background
    if (posDR.x<sBB.left || posDR.y <sBB.top || posUL.x>sBB.width+sBB.left || posUL.y>sBB.height+sBB.top)
    {
        return false;
    }
    //Si Point Haut/gauche trop en haut/gauche
    if (posUL.x<sBB.left)
    {
        posUL.x=sBB.left;
    }
    if (posUL.y<sBB.top)
    {
        posUL.y=sBB.top;
    }

    //Si Point Bas/droite trop en Bas/droite
    if (posDR.x>sBB.width+sBB.left)
    {
        posDR.x=sBB.width+sBB.left;
    }
    if (posDR.y>sBB.height+sBB.top)
    {
        posDR.y=sBB.height+sBB.top;
    }

    // Les positions sont en coordonées globales
    for (int i = posUL.x; i <posDR.x; i++)
    {
        for (int j = posUL.y; j <posDR.y; j++)
        {
            if (ao->isCollidablePoint(sf::Vector2f(i, j)) && m_image.getPixel(i-sBB.left, j-sBB.top).a>128)
                return true;//collision
        }
    }
    return false;

}

void ConcreteBackground::setImage(const std::string& imagePath)
{
    if (!m_sprite)
        m_sprite = new sf::Sprite;
    m_sprite->setTexture(*Moteur2D::getInstance()->getTexture(imagePath));
    m_image = m_sprite->getTexture()->copyToImage();
}



