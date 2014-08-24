#include "moteur2d.h"
#include <stdexcept>
#include <iostream>

#include "eventmanager.h"

Moteur2D * Moteur2D::m_instance = 0;

Moteur2D * Moteur2D::getInstance()
{
    if (m_instance == 0)
    {
        m_instance = new Moteur2D();
        //m_instance->init();
    }
    return m_instance;
}

Moteur2D::Moteur2D()
{
    //ctor
    m_drawablesIndex = 0;
}

Moteur2D::~Moteur2D()
{
    //dtor
    if(m_instance)
        delete m_instance;

    // Tous les drawables sont gérés par le moteur et donc il faut les détruire"
    for (unsigned int i = 0; i < m_drawables.size(); i++)
    {
        delete m_drawables.at(i);
    }
    delete m_window;
    // TO DO : Détruire le contenu des vectors
}

void Moteur2D::init(int width, int height, std::string windowName)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), windowName, sf::Style::Default, settings);

    sf::View v = m_window->getDefaultView();
    m_view.setSize(v.getSize());
    m_view.setCenter(v.getCenter());
    updateView();

        // Init des Id
    m_preUpdateId = 0;
    m_postUpdateId = 0;
    m_keyboardListenersId = 0;
    m_mouseListenersId = 0;
}
/*
void Moteur2D::setWindowSize(int width, int height)
{
    m_window->setSize(sf::Vector2u(width, height));

    sf::View v = m_window->getDefaultView();
    m_view.setSize(v.getSize());
    m_view.setCenter(v.getCenter());
    updateView();
}
//*/
void Moteur2D::run()
{

    EventManager em;
    m_t = m_clock.getElapsedTime();
    sf::Time t2;
    float s;


    while(m_window->isOpen())
    {
        // On efface la fenètre dès le début pour permettre aux Updatables de déssiner
        m_window->clear();// efface la fenètre

        do
        {
            t2 = m_clock.getElapsedTime();
            s = (t2-m_t).asSeconds() ;
        }while (s<1/60.);

        // First called by eventmanager
        em.eventLoop(*m_window);

        /*/Then make the Updates needed before updating positions of objects (external forcies like gravity)
        for (unsigned int i =0; i<m_preUpdates.size(); i++)
        {
            m_preUpdates.at(i)->update(s);
        }//*/

        for (std::map<int,Updatable*>::iterator it=m_preUpdates.begin(); it!=m_preUpdates.end(); ++it)
        {
            it->second->update(s);
        }

        //then update animated object according to interactions with other objects (collisions)
        for (unsigned int i =0; i<m_animatedObjects.size(); i++)
        {
            m_animatedObjects.at(i)->update(s);
        }

        //Then make the Updates needed after updating positions of objects (I don't know what yet)
        for (std::map<int,Updatable*>::iterator it=m_postUpdates.begin(); it!=m_postUpdates.end(); ++it)
        {
            it->second->update(s);
        }

        //And to finish draw all
        // Dessine tous les objets dessinables
        for (unsigned int i =0; i<m_preDraw.size(); i++)
        {
            m_window->draw(*m_preDraw.at(i));
        }
        for (unsigned int i =0; i<m_concreteBackgrounds.size(); i++)
        {
            sf::Sprite* sprite= m_concreteBackgrounds.at(i)->getSprite();
            if (sprite)
                m_window->draw(*sprite);
        }

        for (std::map<int,sf::Drawable*>::iterator it=m_drawables.begin(); it!=m_drawables.end(); ++it)
        {
            m_window->draw(*(it->second));
        }

        for (unsigned int i =0; i<m_postDraw.size(); i++)
        {
            m_window->draw(*m_postDraw.at(i));
        }

        m_window->display();// Affiche

        //MaJ temps
        m_t = t2;

    }
}

void Moteur2D::updateView()
{
    m_window->setView(m_view);
}


// Permet l'accès aux textures, si la texture est inexistante cette methode la créera.
sf::Texture* Moteur2D::getTexture(const std::string& imagePath)
{
    try
    {
        return &m_textures.at(imagePath);
    }
    catch (const std::out_of_range& oor)
    {
        // Texture inéxistante, je la charge
        sf::Texture t;
        t.loadFromFile(imagePath);
        m_textures.insert(std::pair<std::string, sf::Texture>(imagePath, t));
    }
    try
    {
        return &m_textures.at(imagePath);
    }
    catch (const std::out_of_range& oor)
    {
        // problem !
        std::cerr << "Problème d'ajout de Texture" << std::endl;
        return 0;
    }
}

/*
void Moteur2D::addUpdatable(Updatable* u)
{
    m_updates.push_back(u);
}//*/

int Moteur2D::addDrawable(sf::Drawable *d)
{
    m_drawablesIndex++;
    m_drawables[m_drawablesIndex] = d;
    return m_drawablesIndex;
}

void Moteur2D::deleteDrawable(int index)
{
    m_drawables.erase(index);
}

void Moteur2D::deletePreUpdate(int index)
{
    m_preUpdates.erase(index);
}

void Moteur2D::deletePostUpdate(int index)
{

    m_postUpdates.erase(index);
}

void Moteur2D::deleteKeyboardListener(int index)
{
    m_keyboardListeners.erase(index);
}

void Moteur2D::deleteMouseListener(int index)
{
    m_mouseListeners.erase(index);
}

void Moteur2D::deleteFixedObject(FixedObject*f)
{
    for (unsigned int i = 0; i < m_fixedObjects.size(); i++)
    {
        if (f==m_fixedObjects.at(i))
        {
            m_fixedObjects.erase(m_fixedObjects.begin()+i);
        }
    }
}

void Moteur2D::deletePreDrawable(sf::Drawable*d)
{
    for (unsigned int i = 0; i < m_preDraw.size(); i++)
    {
        if (d==m_preDraw.at(i))
        {
            m_preDraw.erase(m_preDraw.begin()+i);
        }
    }
}

void Moteur2D::deleteAnimatedObject(AnimatedObject*a)
{
    for (unsigned int i = 0; i < m_animatedObjects.size(); i++)
    {
        if (a==m_animatedObjects.at(i))
        {
            m_animatedObjects.erase(m_animatedObjects.begin()+i);
        }
    }
}

/*
FixedSprite * Moteur2D::addCollidable(const sf::Vector2f& pos, const std::string& imagePath)
{
    FixedSprite *fs = new FixedSprite(pos, imagePath);
    addCollidable(fs);
    return fs;
}
//*/
/*
Gravity * Moteur2D::setEarthGravity()
{
    Gravity * ret;
    if (m_gravities.size()>0)
    {
        ret = m_gravities.at(0);
        // On vide toutes les classes Gravity
        for (unsigned int i = 0; i<m_gravities.size(); i++)
        {
            m_gravities.at(i)->eraseObjects();
        }
        ret->setTerrestrianGravity();
    }
    else
    {
        ret = new Gravity();
        addGravity(ret);
    }

    // On affecte tous les sprites animés à la gravité terrestre
    for (unsigned int i =0; i<m_colliders.size(); i++)
    {
        ret->addAnimatedObject(m_colliders.at(i));
    }
    return ret;
}
//*/


