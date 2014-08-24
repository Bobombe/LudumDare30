#ifndef FIXEDSHAPE_H
#define FIXEDSHAPE_H

#include <SFML/Graphics.hpp>
#include "fixedobject.h"

class FixedShape : virtual public FixedObject
{
    public:
        enum ShapeType
        {
            CIRCLE,
            RECTANGLE,
            CONVEX
        };

        FixedShape(ShapeType shapeType = CIRCLE, sf::Vector2f pos = sf::Vector2f(0, 0));
        FixedShape(float radius, sf::Vector2f pos = sf::Vector2f(0, 0));
        FixedShape(sf::Vector2f size, sf::Vector2f pos = sf::Vector2f(0, 0));
        virtual ~FixedShape();

        // SETTERS
        void setColor(const sf::Color &color);

        virtual void setPosition(const sf::Vector2f &pos);

        void setRadius(float r);

        // GETTERS
        virtual sf::Vector2f getPosition();

        virtual bool isCollidablePoint(sf::Vector2f pointInGlobalCoordinate);
    protected:
        sf::Shape * m_shape;
        ShapeType m_shapeType;
    private:
};

#endif // FIXEDSHAPE_H
