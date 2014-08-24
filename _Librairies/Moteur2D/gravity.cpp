#include "gravity.h"
#include <cmath>
#include <iostream>
#include "moteur2d.h"
#include <typeinfo>

Gravity::Gravity()
{
    // S'ajoute à la liste de preUpdate du Moteur2D
    m_id = Moteur2D::getInstance()->addPreUpdate(this);

    //ctor par défaut, construit une gravité terrestre
    m_mass = -1; // -1 signifie non paramétré

    // Init des paramètres pour gravité uniforme Terrestre
    m_gravityType = UNIFORM;
    m_gravityVector.x = 0;
    m_gravityVector.y = 1;
    m_forceGravitationnelle = 9.98;
    m_temporalScale = 1;// temps réel
    m_pixMetersScale = 60;// 60 pixels = 1 metre
}

Gravity::~Gravity()
{
    //dtor
    Moteur2D::getInstance()->deletePreUpdate(m_id);
}

void Gravity::update(float seconds)
{
    for (unsigned int i = 0; i< m_objects.size(); i++)
    {
        AnimatedObject* ao = m_objects.at(i);
        if (m_gravityType == UNIFORM)
        {
            ao->setVitesse(ao->getVitesse()+m_gravityVector*m_pixMetersScale*seconds*m_forceGravitationnelle
                           *m_temporalScale*m_temporalScale);
        }
        else if (m_gravityType == PONCTUAL_UNIFORM)
        {
            sf::Vector2f d = m_gravityVector-ao->getPosition();
            float n = sqrt(d.x*d.x+d.y*d.y);
            if (n!=0)
            {

                d.x = d.x/n;
                d.y = d.y/n;
                ao->setVitesse(ao->getVitesse()+
                               d*m_pixMetersScale*seconds*m_forceGravitationnelle
                               *m_temporalScale*m_temporalScale);
            }
        }
        else if (m_gravityType == PONCTUAL)
        {
            // TO DO
            sf::Vector2f dir = m_gravityVector-ao->getPosition();
            float dist = sqrt(dir.x*dir.x+dir.y*dir.y);
            if (dist!=0)
            {
                dir.x = dir.x/dist;
                dir.y = dir.y/dist;
                dist /=  m_pixMetersScale;

                float g = 6.673*pow(10., -11.)*m_mass/(dist*dist); // m/s^2

                // Modifications temporelles 1seconde = 1jour (86400s/jour)
                g = g*m_temporalScale*m_temporalScale;

                ao->setVitesse(ao->getVitesse()+dir*g*seconds*m_pixMetersScale);
            }
        }
    }
}

void Gravity::eraseObjects()
{
    m_objects.clear();
}

void Gravity::setTerrestrianGravity()
{
    m_mass = -1; // -1 signifie non paramétré
    m_gravityType = UNIFORM;
    m_gravityVector.x = 0;
    m_gravityVector.y = 1;
    m_forceGravitationnelle = 9.98;

    m_temporalScale = 1;// temps réel

    m_pixMetersScale = 60;

}

void Gravity::setTerrestrianPointGravity()
{
    m_mass = -1; // -1 signifie non paramétré
    m_gravityType = PONCTUAL_UNIFORM;
    //Centre de gravité en 0,0
    m_gravityVector.x = 0;
    m_gravityVector.y = 0;
    m_forceGravitationnelle = 10.;

    m_temporalScale = 1;// temps réel

    m_pixMetersScale = 10;

}

void Gravity::setSolarSystemGravity()
{
    m_mass = 5.9736*pow(10., 24.); // Masse de la terre
    m_gravityType = PONCTUAL;
    m_gravityVector.x = 400;
    m_gravityVector.y = 300;
    m_forceGravitationnelle = -1; // non utilisé

    m_temporalScale = 86400;// une seconde = un jour

    //m_pixMetersScale = 300/(6.371*pow(10., 6.)); // Terre rempli l'écran diamètre = hauteur (600 pixels)
    m_pixMetersScale = 300/(384.399*pow(10., 6.)); // altitude de la lune

}

void Gravity::addAllAnimatedObject()
{
    m_objects = Moteur2D::getInstance()->getAnimatedObjects();
}











