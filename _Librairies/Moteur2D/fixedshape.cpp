#include "fixedshape.h"
#include "moteur2d.h"
#include <typeinfo>
#include <iostream>


FixedShape::FixedShape(ShapeType shapeType, sf::Vector2f pos)
{
    //ctor

    m_shapeType = shapeType;
    if (shapeType == CIRCLE)
    {
        m_shape = new sf::CircleShape;
    }
    else if (shapeType == RECTANGLE)
    {
        m_shape = new sf::RectangleShape;
    }
    else //if (shapeType == CONVEX)
    {
        m_shape = new sf::ConvexShape;
    }
    m_shape->setPosition(pos);
    m_bBox = m_shape->getGlobalBounds();

    m_drawableObject = m_shape;
    m_indexOfDO=Moteur2D::getInstance()->addDrawable(m_drawableObject);
}
FixedShape::FixedShape(float radius, sf::Vector2f pos)
{
    //ctor
    m_shapeType = CIRCLE;
    m_shape = new sf::CircleShape(radius);
    m_shape->setPosition(pos);
    m_bBox = m_shape->getGlobalBounds();
    m_drawableObject = m_shape;
    m_indexOfDO=Moteur2D::getInstance()->addDrawable(m_drawableObject);

}
FixedShape::FixedShape(sf::Vector2f size, sf::Vector2f pos)
{
    //ctor
    m_shapeType = RECTANGLE;
    m_shape = new sf::RectangleShape(size);
    m_shape->setPosition(pos);
    m_bBox = m_shape->getGlobalBounds();
    m_drawableObject = m_shape;
    m_indexOfDO=Moteur2D::getInstance()->addDrawable(m_drawableObject);
}

FixedShape::~FixedShape()
{
    //dtor
}


void FixedShape::setRadius(float r)
{
    if (m_shapeType == CIRCLE)
    {
        try
        {
            sf::CircleShape& c = dynamic_cast<sf::CircleShape&>(*m_drawableObject);
            c.setRadius(r);
        }
        catch (const std::bad_cast& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

void FixedShape::setColor(const sf::Color &color)
{
    try
    {
        sf::Shape& c = dynamic_cast<sf::Shape&>(*m_drawableObject);
        c.setFillColor(color);
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void FixedShape::setPosition(const sf::Vector2f &pos)
{
    try
    {
        sf::Shape& c = dynamic_cast<sf::Shape&>(*m_drawableObject);
        c.setPosition(pos);
        m_bBox=c.getGlobalBounds();
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
    }
}



sf::Vector2f FixedShape::getPosition()
{
    try
    {
        sf::Shape& c = dynamic_cast<sf::Shape&>(*m_drawableObject);
        return c.getPosition();
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return sf::Vector2f();

}

bool FixedShape::isCollidablePoint(sf::Vector2f pointInGlobalCoordinate)
{

    pointInGlobalCoordinate=m_shape->getTransform().getInverse().transformPoint(pointInGlobalCoordinate);
    if(pointInGlobalCoordinate.x>0 && pointInGlobalCoordinate.y>0&&
       pointInGlobalCoordinate.x<m_bBox.width && pointInGlobalCoordinate.y<m_bBox.height)
    {
        if (m_shapeType == CIRCLE)
        {
            // Si dans le cercle
            if(
            ((pointInGlobalCoordinate.x-m_bBox.width/2.)*(pointInGlobalCoordinate.x-m_bBox.width/2.)+
            (pointInGlobalCoordinate.y-m_bBox.height/2.)*(pointInGlobalCoordinate.y-m_bBox.height/2.))
               <(m_bBox.width/2.)*(m_bBox.width/2.)
               )
            {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;


}
/*
sf::FloatRect FixedShape::getBox()
{

    try
    {
        sf::Shape& s = dynamic_cast<sf::Shape&>(*m_drawableObject);
        return s.getGlobalBounds();
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
    }

//m_shape->getGlobalBounds();

    return m_shape->getGlobalBounds();
}//*/
/*
sf::Vector2f FixedShape::getPosition()
{
    try
    {
        sf::Shape& c = dynamic_cast<sf::Shape&>(*m_drawableObject);
        return c.getPosition();
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return sf::Vector2f();

}
//*/








