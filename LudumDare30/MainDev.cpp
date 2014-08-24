
#include <iostream>
#include <SFML/Graphics.hpp>
#include "moteur2d.h"

#include "worldmanager.h"

int main()
{
    std::cout << "GO !" << std::endl;

    Moteur2D* moteur = Moteur2D::getInstance();
    moteur->init(1024, 768, "FindingWorlds");


    WorldManager::getInstance()->load();

    moteur->updateView();
    moteur->run();
    std::cout << moteur->getTime().asSeconds() << std::endl;
}
