#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SFML/Graphics.hpp>

class EventManager
{
    public:
        EventManager();
        virtual ~EventManager();

        void eventLoop(sf::RenderWindow &window);
    protected:
        sf::Event m_e;
    private:
};

#endif // EVENTMANAGER_H
