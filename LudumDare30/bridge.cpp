#include "bridge.h"
#include "moteur2d.h"
#include "cmath"

#include "iostream"
#include "worldmanager.h"

Bridge::Bridge() : FixedSprite(sf::Vector2f(0, 0), "ressources\\bridge.png")
{
    /*/ctor

    //m_sprite->setTexture(*m_texture);
    //m_sprite->setTextureRect(sf::IntRect(0, 0, 0, 0));

    //m_drawableObject = m_sprite;
//*/
    m_texture = Moteur2D::getInstance()->getTexture("ressources\\bridge.png");
    m_texture->setRepeated(true);
    m_sprite->setOrigin(0, 10);
    m_sprite->setTextureRect(sf::IntRect(0, 0, 0, 00));

    setPosition(sf::Vector2f(0, 0));
    m_idUpdatable = Moteur2D::getInstance()->addPostUpdate(this);
    m_link1=0;
    m_link2=0;

    mouvementBridge = 0;
    m_validated = false;

    Moteur2D::getInstance()->deleteDrawable(m_indexOfDO);//m_sprite
    Moteur2D::getInstance()->addPreDrawable(m_sprite);
    m_indexOfDO=-1;
}

Bridge::~Bridge()
{
    Moteur2D::getInstance()->deletePostUpdate(m_idUpdatable);
    Moteur2D::getInstance()->deletePreDrawable(m_sprite);
    //dtor
}

void Bridge::update(float seconds)
{
    if (m_link1 && m_link2)
    {
        if (!m_validated && collision())
        {
            breackBridge();
        }
        else
        {

            //m_sprite->setTexture(*m_texture);
            sf::Vector2f pos1 = m_link1->getPosition();
            sf::Vector2f delta = m_link2->getPosition()-pos1;
            float length = sqrt(delta.x*delta.x+delta.y*delta.y);
            //delta=delta*(1/length);

            m_sprite->setTextureRect(sf::IntRect(mouvementBridge, 0, length, 20));
            m_sprite->setRotation(atan2(delta.y, delta.x)*180/3.14);

            setPosition(pos1);
            mouvementBridge++;
            if(mouvementBridge>200)
            {
                mouvementBridge=0;
            }
        }
    }
}

bool Bridge::collision()
{

    // Collisions avec les objets fixes
    std::vector <FixedObject*> fos = Moteur2D::getInstance()->getFixedObjects();
    for (unsigned int i = 0; i<fos.size(); i++)
    {
        FixedObject* fo = fos.at(i);
        if ((*fo)!=(*this) /*&& fo->isCollidable()*/ && collideWith(fo))
        {
            return true;
        }

    }
    // Collisions avec les objets mouvants.
    std::vector <AnimatedObject*> aos = Moteur2D::getInstance()->getAnimatedObjects();
    for (unsigned int i = 0; i<aos.size(); i++)
    {
        AnimatedObject* ao = aos.at(i);
        if ((*ao)!=(*m_link1) &&(*ao)!=(*m_link2) &&(*ao)!=(*WorldManager::getInstance()->getPerso()) && collideWith(ao))
        {
            return true;
        }
    }
    return false;
}
bool Bridge::collideWith(FixedObject * fo)
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

void Bridge::breackBridge()
{
    m_sprite->setTextureRect(sf::IntRect(0, 0, 0, 0));
    setPosition(sf::Vector2f(0, 0));
    m_link1 =0;
    m_link2=0;
}

void Bridge::validateBridge()
{
    m_validated = true;
    m_texture = Moteur2D::getInstance()->getTexture("ressources\\bridgeValide.png");
    m_texture->setRepeated(true);
    m_sprite->setTexture(*m_texture);
    Moteur2D::getInstance()->deleteFixedObject(this);
    //m_sprite->setTextureRect(sf::IntRect(0, 0, 0, 00));
}


