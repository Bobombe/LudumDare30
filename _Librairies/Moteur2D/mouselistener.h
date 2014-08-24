#ifndef MOUSELISTENER_H_INCLUDED
#define MOUSELISTENER_H_INCLUDED


#include <SFML/Graphics.hpp>

class MouseListener
{
    public:
        MouseListener();
        virtual ~MouseListener();
        virtual void buttonPressed(sf::Event::MouseButtonEvent mbe)=0;
        virtual void buttonReleased(sf::Event::MouseButtonEvent mbe)=0;
        virtual void mouseMoved(sf::Event::MouseMoveEvent mme)=0;
        virtual void mouseWheel(sf::Event::MouseWheelEvent mwe)=0;
    protected:
        int m_id;
    private:
};



#endif // MOUSELISTENER_H_INCLUDED
