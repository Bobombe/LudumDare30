#include "maincharacter.h"
#include <typeinfo>
#include <iostream>
#include <cmath>

#include "moteur2d.h"
#include "view.h"
#include "animatedobject.h"

#include "worldmanager.h"

#define vPerso 2.
#define vitPerso 200

MainCharacter::MainCharacter(sf::Vector2f pos) : FixedObject(false), AnimatedSprite("ressources\\PersoBouleJaune.png", pos)
{
    //ctor
    m_color.r=255;
    m_color.g=255;
    m_color.b=255;
    m_color.a=255;
    try
    {
        sf::Sprite& c = dynamic_cast<sf::Sprite&>(*m_drawableObject);
        c.setOrigin(15, 15);
        c.setColor(m_color);
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
    }

    m_planeteLinked=0;
    m_angleOnPlanet=0;
    m_bridgeLinked=0;
    m_sensRotation =0;

    m_leftSide=true;
    m_bridge=new Bridge;
}

MainCharacter::~MainCharacter()
{
    //dtor
    delete m_bridge;
    for (unsigned int i = 0; i< m_validatedBridges.size(); i++)
    {
        delete m_validatedBridges.at(i);
    }
}


void MainCharacter::applyCollision(FixedObject * fo, sf::Vector2f oldPos)
{

    try
    {
        // Link to this planete
        Planete& p = dynamic_cast<Planete&>(*fo);
        m_planeteLinked = &p;

        collisionWithPlanete(m_planeteLinked);
        // Cette fonction exécute ce code :
        /*/ On se place à la bonne hauteur
        sf::Vector2f d = getPosition()-m_planeteLinked->getPosition();
        float n = sqrt(d.x*d.x+d.y*d.y);
        float n2 = getBox().height/2.+p.getBox().height/2.;
        setPosition(m_planeteLinked->getPosition()+d/n*n2);

        // On calcul l'angle
        d=d/n;
        m_angleOnPlanet = atan2(d.y, d.x);

        //RaZ
        m_vit.x=0;
        m_vit.y=0;
        //*/
        return;

    }
    catch (const std::bad_cast& e)
    {
        //std::cerr << e.what() << std::endl;
    }

    try
    {
        // Link to this Bridge
        Bridge& b = dynamic_cast<Bridge&>(*fo);
        m_bridgeLinked = &b;

        //On détermine si on se trouve à gauche ou droite du pond
        m_leftSide = getAngleWithBridge()>0;

        // Repositionnement
        setPosOnBridge();

        //RaZ
        m_vit.x=0;
        m_vit.y=0;
        return;

    }
    catch (const std::bad_cast& e)
    {
        //std::cerr << e.what() << std::endl;
    }

    m_vit.x=0;
    m_vit.y=0;
    setPosition( oldPos);
}

void MainCharacter::update(float seconds)
{
    //updateColor();
    // Rotation du perso
    try
    {
        sf::Sprite& c = dynamic_cast<sf::Sprite&>(*m_drawableObject);
        c.rotate(m_sensRotation*60*seconds*4);
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
    }


    sf::Vector2f oldPos = getPosition();
    sf::Vector2f newPos = oldPos;

    if(!m_bridge->isBuild())
        m_bridgeLinked=0;
    // On est sur le pond
    if(m_bridgeLinked)
    {
        sf::Vector2f vitTranslation;
        if(!m_leftSide)
        {
            //*
            //newPos = oldPos+m_bridge.getNormalisedDirection()*(float)(vitPerso*seconds*m_sensRotation);
            newPos = m_bridge->getPosition()+m_bridge->getNormalisedDirection()*(float)(m_distToP1Projected+vitPerso*m_sensRotation*seconds);
            /*/
            //m_vit += m_bridge.getNormalisedDirection()*(float)(vitPerso*m_sensRotation);
            vitTranslation = m_bridge.getNormalisedDirection()*(float)(vitPerso*m_sensRotation);
            //*/
        }
        else
        {
            //*
            //newPos = oldPos-m_bridge.getNormalisedDirection()*(float)(vitPerso*seconds*m_sensRotation);
            newPos = m_bridge->getPosition()+m_bridge->getNormalisedDirection()*(float)(m_distToP1Projected-vitPerso*m_sensRotation*seconds);
            /*/
            //m_vit -= m_bridge.getNormalisedDirection()*(float)(vitPerso*m_sensRotation);
            vitTranslation = -m_bridge.getNormalisedDirection()*(float)(vitPerso*m_sensRotation);
            //*/
        }
        //*
        setPosition(newPos);
        /*/
        setPosition(newPos+(m_vit+vitTranslation)*seconds);
        //*/
        setPosOnBridge();

        if(collideWith(m_bridge->m_link1))
        {
            try
            {
                Planete& p = dynamic_cast<Planete&>(*m_bridge->m_link1);
                m_bridgeLinked=0;
                m_planeteLinked = &p;
                collisionWithPlanete(m_planeteLinked);
            }
            catch (const std::bad_cast& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        if(collideWith(m_bridge->m_link2))
        {
            try
            {
                Planete& p = dynamic_cast<Planete&>(*m_bridge->m_link2);
                m_bridgeLinked=0;
                m_planeteLinked = &p;
                collisionWithPlanete(m_planeteLinked);
                // Validation
                m_bridge->validateBridge();
                m_validatedBridges.push_back(m_bridge);
                m_bridge = new Bridge;
            }
            catch (const std::bad_cast& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        m_vit = (getPosition()-oldPos-vitTranslation)*60.f;
        return;
    }
    // Mouvements sur planete, plus de gravité
    if(m_planeteLinked)
    {
        m_angleOnPlanet+=vPerso*seconds*m_sensRotation;

        sf::Vector2f planetePos = m_planeteLinked->getPosition();
        sf::Vector2f d(cos(m_angleOnPlanet), sin(m_angleOnPlanet));

        float n2 = m_size.x/2.+m_planeteLinked->getHeight()/2.;
        sf::Vector2f posPerso = planetePos+d*n2;
        setPosition(posPerso);

        // Calcul vitesse perso = getPosition();
        /*float distPerso2 = posPerso.x*posPerso.x+posPerso.y*posPerso.y;
        float distPlanete2 = planetePos.x*planetePos.x+planetePos.y*planetePos.y;

        m_vit = nextPlanetVitesse*(float)(sqrt(distPerso2/distPlanete2)*0.8);//*/
        sf::Vector2f nextPlanetVitesse = m_planeteLinked->getVitesse();
        m_vit = nextPlanetVitesse*(float)0.5;

        // Test si le perso tombe de la planete
        /* Basé sur le code de Gravity.cpp :
        sf::Vector2f d = m_gravityVector-ao->getPosition();
            float n = sqrt(d.x*d.x+d.y*d.y);
            if (n!=0)
            {

                d.x = d.x/n;
                d.y = d.y/n;
        ao->getVitesse()+
                               d*m_pixMetersScale*seconds*m_forceGravitationnelle
                               *m_temporalScale*m_temporalScale

        Si les peremètres changes dans Gravité, ce code ne marchera pas*/
        // vecteur gravité
        d = -planetePos;
        float n = sqrt(d.x*d.x+d.y*d.y);
        d=d*(1/n);

        nextPlanetVitesse+=d*(float)(10.f * 1/60.f * 10 * 1.f *1.f);

        d = -posPerso;
        n = sqrt(d.x*d.x+d.y*d.y);
        d=d*(1/n);
        m_vit+=d*(float)(10. * 1/60. * 10. * 1. *1.);

        sf::Vector2f nextD = getPosition()-planetePos;

        nextD = getPosition()+m_vit*(float)(1/60.)-planetePos-nextPlanetVitesse*(float)(1/60.);
        //if(planetePos.x*d.x+planetePos.y*d.y <=0)
        if(nextD.x*nextD.x+nextD.y*nextD.y >n2*n2)
        {
            //m_planeteLinked=0;
        }//*/
        if(collideWith(m_bridge))
        {
            m_bridgeLinked = m_bridge;

            //On détermine si on se trouve à gauche ou droite du pond
            m_leftSide = getAngleWithBridge()>0;

            // Repositionnement
            setPosOnBridge();
            m_planeteLinked=0;
        }
        m_vit = (getPosition()-oldPos)*60.f;
        return;
    }


    // Calcule la nouvelle position sans collision
    newPos += m_vit*seconds;
    setPosition( newPos);


    m_bridgeLinked=0;

    if (true)//m_isCollidable)
    {
        //setPosition(checkCollision(seconds));
        checkCollision(seconds, oldPos);
    }
    else
    {
        setPosition(getPosition()+m_vit*seconds);
    }
}

void MainCharacter::keyPressed(sf::Keyboard::Key k)
{
    if(k==18)
    {
        m_sensRotation = -1;
    }
    if(k==3)
    {
        m_sensRotation = 0;
    }
    if(k==5)
    {
        m_sensRotation = 1;
    }
    if(k==4)
    {
        //setPosition(sf::Vector2f(0, 350));
        WorldManager::getInstance()->load();

    }
    if(k==57)
    {
        jump();
    }
    std::cout << k << std::endl;
}
void MainCharacter::keyReleased(sf::Keyboard::Key k)
{

}

void MainCharacter::updateColor()
{
    m_color.g--;
    m_color.b--;
    if(m_color.g<0)
    {

        m_color.g=255;
        m_color.b=255;
    }
    try
    {
        sf::Sprite& c = dynamic_cast<sf::Sprite&>(*m_drawableObject);
        c.setColor(m_color);
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void MainCharacter::buttonReleased(sf::Event::MouseButtonEvent mbe)
{
    //setPosition(Moteur2D::getInstance()->getView()->getMouseInWorld());
}

void MainCharacter::buttonPressed(sf::Event::MouseButtonEvent mbe)
{
    if(!m_planeteLinked)
        return;
    sf::Vector2f mousePos = Moteur2D::getInstance()->getView()->getMouseInWorld(); //J'ai clické où ?
    sf::FloatRect bbox;
    std::vector <AnimatedObject*> aos = Moteur2D::getInstance()->getAnimatedObjects();
    for (unsigned int i = 0; i<aos.size(); i++)
    {
        AnimatedObject* ao = aos.at(i);
        if ((*ao)!=(*this))
        {
            bbox=ao->getBox();
            if(mousePos.x>bbox.left && mousePos.x<bbox.left+bbox.width && mousePos.y>bbox.top && mousePos.y<bbox.top+bbox.height)
            {
                m_bridge->setBridge(m_planeteLinked, ao);
            }
        }
    }
}

void MainCharacter::mouseWheel(sf::Event::MouseWheelEvent mwe)
{
    View* v=Moteur2D::getInstance()->getView();
    if(mwe.delta<0 && v->getZoom()<8)
        v->zoom(1.1);
    else if(mwe.delta>0 && v->getZoom()>1)
        v->zoom(1/1.1);
    Moteur2D::getInstance()->updateView();
}

void MainCharacter::setPosOnBridge()
{
    if(m_bridgeLinked)
    {
        sf::Vector2f pos = m_bridge->getPosition();
        sf::Vector2f dir = getPosition()-pos;
        float norm = sqrt(dir.x*dir.x+dir.y*dir.y);
        sf::Vector2f normale = m_bridge->getNormale();
        if(m_leftSide)
        {
            normale=-normale;
        }
        m_distToP1Projected = cos(getAngleWithBridge())*norm;
        setPosition( pos+m_bridge->getNormalisedDirection()*m_distToP1Projected  + normale*(float)(10.+15.) );

    }
}

float MainCharacter::getAngleWithBridge()
{
    if(m_bridgeLinked)
    {
        sf::Vector2f vect = getPosition()-m_bridge->getPosition();
        sf::Vector2f vect2 = m_bridge->getDirection();//getEndPos()-m_bridge.getPosition();
        float angle = atan2(vect.y, vect.x)-atan2(vect2.y, vect2.x);
        if (angle>3.14)
        {
            angle-=2*3.14;
        }
        if (angle<-3.14)
        {
            angle+=2*3.14;
        }
        return angle;
    }
    return 0;
}

void MainCharacter::jump()
{
    float gain = 1;
    if(m_planeteLinked)
    {
        m_vit+=(getPosition()-m_planeteLinked->getPosition())*(float)(vitPerso*gain/65.);
        //setVitesse((getPosition()-m_planeteLinked->getPosition())*(float)(vitPerso*1.5/65.));
        m_planeteLinked=0;
    }
    else if (m_bridgeLinked)
    {
        if(!m_leftSide)
            m_vit+=((m_bridgeLinked->getNormale())*(float)(vitPerso*gain));
            //setVitesse((m_bridgeLinked->getNormale())*(float)(vitPerso*1.5));
        else
            m_vit+=((m_bridgeLinked->getNormale())*(float)(-vitPerso*gain));
            //setVitesse((m_bridgeLinked->getNormale())*(float)(-vitPerso*1.5));
    }
    m_bridgeLinked=0;
    m_bridge->breackBridge();
}

void MainCharacter::collisionWithPlanete(Planete*p)
{

    // On se place à la bonne hauteur
    sf::Vector2f d = getPosition()-p->getPosition();
    float n = sqrt(d.x*d.x+d.y*d.y);
    float n2 = getBox().height/2.+p->getBox().height/2.;
    setPosition(p->getPosition()+d/n*n2);

    // On calcul l'angle
    d=d/n;
    m_angleOnPlanet = atan2(d.y, d.x);

    //RaZ
    m_vit.x=0;
    m_vit.y=0;
}



