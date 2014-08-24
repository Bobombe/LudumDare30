#include "ketboardlistener.h"

#include "moteur2d.h"
MouseListener::MouseListener()
{
    //ctor
    m_id = Moteur2D::getInstance()->addMouseListener(this);
}

MouseListener::~MouseListener()
{
    Moteur2D::getInstance()->deleteMouseListener(m_id);
}
