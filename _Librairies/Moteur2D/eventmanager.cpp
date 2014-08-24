#include "eventmanager.h"
#include "moteur2d.h"

EventManager::EventManager()
{
    //ctor
}

EventManager::~EventManager()
{
    //dtor
}

void EventManager::eventLoop(sf::RenderWindow &window)
{

    while (window.pollEvent(m_e))
    {
        // Click sur la croix -> Fermeture
        if(m_e.type == sf::Event::Closed)
            window.close();

        // Appuis sur touche -> Appel des listener de clavier
        else if (m_e.type == sf::Event::KeyPressed)
        {
            std::map<int,KeyboardListener*> kls = Moteur2D::getInstance()->getKeyboardListeners();
            for (std::map<int,KeyboardListener*>::iterator it=kls.begin(); it!=kls.end(); ++it)
            {
                it->second->keyPressed(m_e.key.code);
            }
        }
        // Relachement d'une touche -> Appel des listener de clavier
        else if (m_e.type == sf::Event::KeyReleased)
        {
            std::map<int,KeyboardListener*> kls = Moteur2D::getInstance()->getKeyboardListeners();
            for (std::map<int,KeyboardListener*>::iterator it=kls.begin(); it!=kls.end(); ++it)
            {
                it->second->keyReleased(m_e.key.code);
            }
        }

        // Appuis sur un bouton de la souris -> Appel des listener de souris
        else if (m_e.type == sf::Event::MouseButtonPressed)
        {
            std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
            {
                it->second->buttonPressed(m_e.mouseButton);
            }
        }
        // Relachement d'un bouton de la souris -> Appel des listener de souris
        else if (m_e.type == sf::Event::MouseButtonReleased)
        {
            std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
            {
                it->second->buttonReleased(m_e.mouseButton);
            }
        }
        // Mouvement de la souris -> Appel des listener de souris
        else if (m_e.type == sf::Event::MouseMoved)
        {
            std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
            {
                it->second->mouseMoved(m_e.mouseMove);
            }
        }
        // Mouvement molette de la souris -> Appel des listener de souris
        else if (m_e.type == sf::Event::MouseWheelMoved)
        {
            std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
            {
                it->second->mouseWheel(m_e.mouseWheel);
            }
        }
    }

}
