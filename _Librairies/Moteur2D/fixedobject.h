#ifndef FIXEDOBJECT_H
#define FIXEDOBJECT_H
#include "SFML/Graphics.hpp"
#include <iostream>


// Les objets dessinables (sprite, shape ...) implémentent leur position,
// cette classe n'est donc qu'une interface pour accéder aux positions
class FixedObject
{
    public:
        //*
        FixedObject(bool addToFixedObjectList = true);
        virtual ~FixedObject();

        //SETTERS
        virtual void setPosition(const sf::Vector2f &pos) = 0;

        //GETTERS
        virtual sf::Vector2f getPosition() = 0;
        virtual sf::FloatRect getBox()
        {
            return m_bBox;
        }
        virtual sf::Drawable* getDrawableObject()
        {
            return m_drawableObject;
        }

        virtual bool isCollidablePoint(sf::Vector2f pointInGlobalCoordinate)=0;

        // OPERATORS
        bool operator !=(const FixedObject &b) const
        {
            return b.m_indexOfDO != m_indexOfDO;
        }

        virtual void jesuis()
        {
            std::cout << "FixedObject" << std::endl;
        }

    protected:

        int m_indexOfDO;
        sf::FloatRect m_bBox;
        sf::Drawable *m_drawableObject;

    private:
};

#endif // FIXEDOBJECT_H
