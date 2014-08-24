#ifndef FIXEDSPRITE_H
#define FIXEDSPRITE_H

#include <SFML/Graphics.hpp>
#include "fixedobject.h"
#include "iostream"

class FixedSprite : virtual public FixedObject
{
    public:
        FixedSprite(bool addToFixedObjectList = true);
        FixedSprite(const std::string& imagePath, bool addToFixedObjectList = true);
        FixedSprite(const sf::Vector2f& pos, const std::string& imagePath = "", bool addToFixedObjectList = true);
        virtual ~FixedSprite();

        //SETTERS
        void setSprite(const std::string& imagePath);
        virtual void setPosition(const sf::Vector2f &pos);
        void setRotation(float degree);

        virtual bool isCollidablePoint(sf::Vector2f pointInGlobalCoordinate);

        void setScale(float scale);

        //GETTERS
        virtual sf::Vector2f getPosition();
        sf::Vector2f getSize()
        {
            return m_size;
        }
        float getWidth()
        {
            return m_size.x;
        }
        float getHeight()
        {
            return m_size.y;
        }
        //virtual sf::FloatRect getBox();
        virtual void jesuis()
        {
            std::cout << "FixedSprite" << m_indexOfDO << std::endl;
        }
    protected:
        sf::Sprite * m_sprite;
        sf::Image m_image;

        //Mémorise la taille de l'image
        sf::Vector2f m_size;
    private:
};

#endif // FIXEDSPRITE_H
