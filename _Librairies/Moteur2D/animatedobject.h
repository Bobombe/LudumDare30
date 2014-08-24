#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include <SFML/Graphics.hpp>
#include "updatable.h"
#include "fixedobject.h"

// La vitesse n'est pas inclu dans les drawable contrairement à la position,
// donc on l'implémente ici.
// Cette classe reste abstraite en incluant fixed object
class AnimatedObject : public Updatable, virtual public FixedObject
{
    public:
        AnimatedObject(sf::Vector2f vit = sf::Vector2f(0, 0));
        virtual ~AnimatedObject();


        // GETTERS
        virtual sf::Vector2f getVitesse()
        {
            return m_vit;
        }

        // SETTERS
        virtual void setVitesse(const sf::Vector2f& v)
        {
            m_vit.x= v.x;
            m_vit.y = v.y;
        }

        virtual void update(float seconds);

        virtual void jesuis()
        {
            std::cout << "AnimatedObject" << m_indexOfDO << std::endl;
        }

    protected:

        virtual void checkCollision(float seconds, sf::Vector2f oldPos);
        virtual bool collideWith(const sf::FloatRect &other, const sf::Vector2f & newPos);
        virtual bool collideWith(FixedObject * fo);
        virtual void applyCollision(FixedObject * fo, sf::Vector2f oldPos);

        sf::Vector2f m_vit;
    private:
};

#endif // ANIMATEDOBJECT_H
