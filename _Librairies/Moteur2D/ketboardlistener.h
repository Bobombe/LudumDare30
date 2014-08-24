#ifndef KETBOARDLISTENER_H_INCLUDED
#define KETBOARDLISTENER_H_INCLUDED

#include <SFML/Graphics.hpp>

class KeyboardListener
{
    public:
        KeyboardListener();
        virtual ~KeyboardListener();
        virtual void keyPressed(sf::Keyboard::Key k)=0;
        virtual void keyReleased(sf::Keyboard::Key k)=0;
    protected:
        int m_id;
    private:
};


#endif // KETBOARDLISTENER_H_INCLUDED
