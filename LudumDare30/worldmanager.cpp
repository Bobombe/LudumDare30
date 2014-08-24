#include "worldmanager.h"

#include <iostream>
#include <cmath>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "moteur2d.h"
#include <typeinfo>

WorldManager * WorldManager::m_instance = 0;

WorldManager * WorldManager::getInstance()
{
    if (m_instance == 0)
    {
        m_instance = new WorldManager();
        m_instance->init();
    }
    return m_instance;
}

WorldManager::WorldManager()
{
    //ctor
}


WorldManager::~WorldManager()
{
    //dtor
}
void WorldManager::lectureMonde(std::string monde)
{

    /** DEBUT Chargement DU MONDE **/
    float px, py, gain, sens;
    std::ifstream file(monde.c_str(), std::ios::in);

    if(file)
    {
        std::string osef;
        getline(file, osef);
        getline(file, osef);
        getline(file, osef);
        getline(file, osef);
        getline(file, osef);

        file >> px;
        file >> py;
        file >> gain;
        file >> sens;
        float norm = sqrt(px*px+py*py);

        sf::Vector2f pos(px, py);
        m_perso = new MainCharacter(pos*(float)(1.+2./norm));
        sf::Vector2f vit(sens*py/norm*sqrt(100*norm)*gain, -sens*px/norm*sqrt(100*norm)*gain);
        m_planetes.push_back(new Planete("ressources\\Terre.png", pos, vit));

        while(getline(file, osef))
        {

            file >> px;
            file >> py;
            file >> gain;
            file >> sens;
            float norm = sqrt(px*px+py*py);

            sf::Vector2f pos(px, py);
            sf::Vector2f vit(sens*py/norm*sqrt(100*norm)*gain, -sens*px/norm*sqrt(100*norm)*gain);

            m_planetes.push_back(new Planete("ressources\\Terre.png", pos, vit));
        }


    }
    else{std::cout<< "prob";}
    file.close();

}

void WorldManager::init()
{
    lectureMonde("ressources\\Map1.txt");

    // Gravité
     m_gravity = new Gravity;
    m_gravity->setTerrestrianPointGravity();
    m_gravity->addAllAnimatedObject();

    // Soleil
    m_soleil = new FixedSprite(sf::Vector2f(0, 0), "ressources\\Soleil.png");
    try
    {
        sf::Sprite& c = dynamic_cast<sf::Sprite&>(*m_soleil->getDrawableObject());
        c.setOrigin(120, 120);
        m_soleil->setPosition(sf::Vector2f(0, 0));
        //c.scale(1.5, 1.5);
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
    }
//*/

    /** FIN DEFINITION DU MONDE **/

    View *v = Moteur2D::getInstance()->getView();
    v->move(-1024/2, -768/2);
    v->zoom(8);
}

void WorldManager::load()
{
    /** Destructions **/
    for (unsigned int i = 0; i<m_planetes.size(); i++)
    {
        delete m_planetes.at(i);
    }
    m_planetes.clear();

    //delete m_gravity;
    //delete m_soleil;
    delete m_perso;

    lectureMonde("ressources\\Map1.txt");

    m_gravity->addAllAnimatedObject();

}


