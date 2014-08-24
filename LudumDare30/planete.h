#ifndef PLANETE_H
#define PLANETE_H

#include <animatedsprite.h>

class Planete : public AnimatedSprite
{
    public:
        Planete(std::string image = "ressources\\Terre.png", sf::Vector2f pos = sf::Vector2f(300, 0), sf::Vector2f vit = sf::Vector2f(0, 150));
        virtual ~Planete();
        virtual void jesuis()
        {
            std::cout << "Planete" << m_indexOfDO << std::endl;
        }
    protected:
        virtual void applyCollision(FixedObject * fo, sf::Vector2f oldPos);
    private:
};

#endif // PLANETE_H
