#ifndef CONCRETEBACKGROUND_H
#define CONCRETEBACKGROUND_H

#include <SFML/Graphics.hpp>
#include "animatedobject.h"

class ConcreteBackground
{
    public:
        ConcreteBackground(const std::string& imagePath ="");
        virtual ~ConcreteBackground();

        sf::Sprite* getSprite()
        {
            return m_sprite;
        }
        // Test de collision utilisant la transparence
        bool collidedBy(AnimatedObject * ao, const sf::Vector2f & newObjectPos);

        void setImage(const std::string& imagePath);

    protected:
        sf::Sprite *m_sprite;
        sf::Image m_image;
    private:
};

#endif // CONCRETEBACKGROUND_H
