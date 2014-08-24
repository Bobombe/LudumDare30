#ifndef MOTEUR2D_H
#define MOTEUR2D_H

#include <map>
#include <vector>

#include <SFML/Graphics.hpp>
#include "updatable.h"
#include "animatedobject.h"
#include "fixedobject.h"
#include "mouselistener.h"
#include "ketboardlistener.h"
#include "gravity.h"
#include "view.h"
#include "concretebackground.h"

class Moteur2D
{
    public:
        static Moteur2D* getInstance();
        void run();

        //Gravity * setEarthGravity();

        void updateView();

        // ADDERS
        int addDrawable(sf::Drawable *d);

        void addPreDrawable(sf::Drawable* d)
        {
            m_preDraw.push_back(d);
        }

        void addPostDrawable(sf::Drawable* d)
        {
            m_postDraw.push_back(d);
        }

        void addConcreteBackground(ConcreteBackground* cb)
        {
            m_concreteBackgrounds.push_back(cb);
        }

        void addFixedObject(FixedObject* fo)
        {
            m_fixedObjects.push_back(fo);
        }
        //FixedSprite * addCollidable(const sf::Vector2f& pos, const std::string& imagePath);

        void addAnimatedObject(AnimatedObject* ao)
        {
            m_animatedObjects.push_back(ao);
        }

        int addKeyboardListener(KeyboardListener* kl)
        {
            ++m_keyboardListenersId;
            m_keyboardListeners[m_keyboardListenersId]=kl;
            return m_keyboardListenersId;
        }
        int addMouseListener(MouseListener* ml)
        {
            ++m_mouseListenersId;
            m_mouseListeners[m_mouseListenersId]=ml;
            return m_mouseListenersId;
        }

        int addPreUpdate(Updatable *u)
        {
            ++m_preUpdateId;
            m_preUpdates[m_preUpdateId]=u;
            return m_preUpdateId;
        }

        int addPostUpdate(Updatable *u)
        {
            ++m_postUpdateId;
            m_postUpdates[m_postUpdateId]=u;
            return m_postUpdateId;
        }

        //Suppression
        void deleteDrawable(int index);
        void deletePreUpdate(int index);
        void deletePostUpdate(int index);
        void deleteKeyboardListener(int index);
        void deleteMouseListener(int index);
        void deleteFixedObject(FixedObject*f);
        void deletePreDrawable(sf::Drawable*d);
        void deleteAnimatedObject(AnimatedObject*a);

        //GETTERS
        View * getView()
        {
            return &m_view;
        }
        sf::RenderWindow & getWindow()
        {
            return *m_window;
        }

        sf::Texture* getTexture(const std::string& imagePath);
        const std::map <int, KeyboardListener*>& getKeyboardListeners()
        {
            return m_keyboardListeners;
        }
        const std::map <int, MouseListener*>& getMouseListeners()
        {
            return m_mouseListeners;
        }
        const std::vector <FixedObject*>& getFixedObjects()
        {
            return m_fixedObjects;
        }
        const std::vector <AnimatedObject*>& getAnimatedObjects()
        {
            return m_animatedObjects;
        }
        const std::vector <ConcreteBackground*>& getConcreteBackgrounds()
        {
            return m_concreteBackgrounds;
        }
        sf::Time getTime()
        {
            return m_clock.getElapsedTime();
        }

        // SETTERS
        //void setWindowSize(int width, int height);
        void init(int width=800, int height=600, std::string windowName ="Youpi");

    protected:
        Moteur2D();
        virtual ~Moteur2D();

        static Moteur2D * m_instance;

        sf::RenderWindow *m_window;
        View m_view;

        std::map<std::string, sf::Texture> m_textures;
        //std::vector <Updatable*> m_updates;


        // First called by eventmanager
        std::map <int, KeyboardListener*> m_keyboardListeners;
        int m_keyboardListenersId;
        std::map <int, MouseListener*> m_mouseListeners;
        int m_mouseListenersId;

        //Then make the Updates needed before updating positions of objects (external forcies like gravity)
        std::map <int, Updatable*> m_preUpdates;
        int m_preUpdateId;

        //then update animated object according to interactions with other objects (collisions)
        std::vector <AnimatedObject*> m_animatedObjects;
        std::vector <FixedObject*> m_fixedObjects;

        //Then make the Updates needed after updating positions of objects (I don't know what yet)
        //std::vector <Updatable*> m_postUpdates;
        std::map <int, Updatable*> m_postUpdates;
        int m_postUpdateId;

        /*/-------- And to finish draw all --------\\

        // TO DO : Pour m_preDraw et m_postDraw : passer en map pouvant avoir plusieurs index égaux représentant la profondeur
        // Dessinables avant perso et autres//*/
        std::vector <sf::Drawable*> m_preDraw;

        // Background tengible
        std::vector <ConcreteBackground*> m_concreteBackgrounds;

        // Dessins au niveau du perso
        std::map <int, sf::Drawable*> m_drawables;
        int m_drawablesIndex;

        // Dessinables après perso et autres
        std::vector <sf::Drawable*> m_postDraw;

        sf::Clock m_clock;
        sf::Time m_t;

    private:
};

#endif // MOTEUR2D_H
