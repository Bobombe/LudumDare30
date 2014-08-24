#include "ketboardlistener.h"

#include "moteur2d.h"
KeyboardListener::KeyboardListener()
{
    //ctor
    m_id = Moteur2D::getInstance()->addKeyboardListener(this);
}

KeyboardListener::~KeyboardListener()
{
    Moteur2D::getInstance()->deleteKeyboardListener(m_id);
}
