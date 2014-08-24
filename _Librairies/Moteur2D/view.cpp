#include "view.h"
#include "moteur2d.h"

View::View()
{
    //ctor
}

View::~View()
{
    //dtor
}

void View::move(const sf::Vector2f &offset)
{
    sf::View::move(offset);
    Moteur2D::getInstance()->updateView();
}

void View::move(float offsetX, float offsetY)
{
    sf::View::move(offsetX, offsetY);
    Moteur2D::getInstance()->updateView();
}

void View::zoomOnMouse(float factor)
{

    sf::Vector2f mp = getMouseInWorld();
    zoom(factor);

    mp -= getMouseInWorld();
    move(mp);
}


sf::Vector2f View::getMouseInWorld()
{
    const sf::RenderWindow &win = Moteur2D::getInstance()->getWindow() ;
    sf::Vector2i mPos = sf::Mouse::getPosition(win );
    sf::Vector2f ret;
    ret.x = (float)mPos.x / win.getSize().x;
    ret.x *= getSize().x;
    ret.x += getCenter().x;
    ret.x -= getSize().x/2;

    ret.y = (float)mPos.y / win.getSize().y;
    ret.y *= getSize().y;
    ret.y += getCenter().y;
    ret.y -= getSize().y/2;

    return ret;
}

float View::getZoom()
{
    return getSize().x / Moteur2D::getInstance()->getWindow().getSize().x;
}


