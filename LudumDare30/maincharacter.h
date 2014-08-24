#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include <animatedsprite.h>
#include "planete.h"
#include "bridge.h"
#include "ketboardlistener.h"
#include "mouselistener.h"
#include <SFML/Graphics.hpp>

#include "bridge.h"
#include <vector>


class MainCharacter : public AnimatedSprite, public KeyboardListener, public MouseListener
{
    public:
        MainCharacter(sf::Vector2f pos = sf::Vector2f(500, 500));
        virtual ~MainCharacter();

        virtual void update(float seconds);

        //Clavier
        virtual void keyPressed(sf::Keyboard::Key k);
        virtual void keyReleased(sf::Keyboard::Key k);

        //Souris
        virtual void buttonPressed(sf::Event::MouseButtonEvent mbe);
        virtual void buttonReleased(sf::Event::MouseButtonEvent mbe);
        virtual void mouseMoved(sf::Event::MouseMoveEvent mme){}
        virtual void mouseWheel(sf::Event::MouseWheelEvent mwe);

        void updateColor();

        virtual void jesuis()
        {
            std::cout << "Perso" << m_indexOfDO << std::endl;
        }
        float getAngleWithBridge();
        void jump();
        void collisionWithPlanete(Planete*p);
    protected:
        virtual void applyCollision(FixedObject * fo, sf::Vector2f oldPos);
        void setPosOnBridge();

        Planete* m_planeteLinked;
        float m_angleOnPlanet;

        Bridge* m_bridgeLinked;
        Bridge* m_bridge;
        bool m_leftSide;
        float m_distToP1Projected;

        std::vector<Bridge*> m_validatedBridges;

        // 0 = no movement
        // 1 = clockwise
        // -1 = counter clockwise
        int m_sensRotation;

        sf::Color m_color;
    private:
};

#endif // MAINCHARACTER_H
