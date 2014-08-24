#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "fixedsprite.h"
#include "animatedobject.h"
#include "updatable.h"


class AnimatedSprite : public FixedSprite, public  AnimatedObject //*/ Updatable
{
    public:
        AnimatedSprite();
        AnimatedSprite(const std::string& imagePath, const sf::Vector2f& pos = sf::Vector2f(0, 0), sf::Vector2f vit = sf::Vector2f(0, 0));
        AnimatedSprite(const sf::Vector2f& pos, const std::string& imagePath = "");
        virtual ~AnimatedSprite();

        // virtual void update(float seconds);

        /*/ GETTERS
        const sf::Vector2f& getVitesse()
        {
            return m_vit;
        }

        // SETTERS
        void setVitesse(const sf::Vector2f& v)
        {
            m_vit.x= v.x;
            m_vit.y = v.y;
        }
        //*/
        virtual void jesuis()
        {
            std::cout << "AnimatedSprite" << m_indexOfDO << std::endl;
        }

    protected:
        // virtual sf::Vector2f collisionTest(float s);
        //virtual bool collideWith(const sf::FloatRect &other, const sf::Vector2f & newPos);

        //sf::Vector2f m_vit;
    private:
};

#endif // ANIMATEDSPRITE_H
