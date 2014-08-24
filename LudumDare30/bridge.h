#ifndef BRIDGE_H
#define BRIDGE_H

#include "fixedsprite.h"
#include "updatable.h"
#include "animatedobject.h"
#include "SFML/Graphics.hpp"

#include <iostream>
#include <cmath>


class Bridge : public FixedSprite, public Updatable
{
    public:
        Bridge();
        virtual ~Bridge();

        void setBridge(AnimatedObject * deb, AnimatedObject * fin)
        {
            m_link1 =deb;
            m_link2 = fin;
        }
        bool collision();
        bool collideWith(FixedObject * fo);
        void breackBridge();
        bool isBuild()
        {
            return m_link1 && m_link2;
        }
        virtual void update(float seconds);

        sf::Vector2f getEndPos()
        {
            return m_link2->getPosition();
        }
        sf::Vector2f getDirection()
        {
            return m_link2->getPosition()-getPosition();
        }
        sf::Vector2f getNormalisedDirection()
        {
            sf::Vector2f dir = m_link2->getPosition()-getPosition();
            float norm = sqrt(dir.x*dir.x+dir.y*dir.y);
            return dir*(1/norm);
        }
        float getNorme()
        {
            sf::Vector2f dir = m_link2->getPosition()-getPosition();
            return sqrt(dir.x*dir.x+dir.y*dir.y);
        }
        sf::Vector2f getNormale()
        {
            sf::Vector2f nDir = getNormalisedDirection();
            sf::Vector2f ret;
            ret.x=nDir.y;
            ret.y = -nDir.x;
            return ret;
        }

        virtual void jesuis()
        {
            std::cout << "Bridge" << m_indexOfDO << std::endl;
        }

        void validateBridge();

        AnimatedObject * m_link1;
        AnimatedObject * m_link2;
    protected:

        //sf::Sprite * m_sprite;
        sf::Texture * m_texture;

        int mouvementBridge;

        int m_idUpdatable;

        bool m_validated;
    private:
};

#endif // BRIDGE_H
