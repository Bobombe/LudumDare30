//*
#include "fixedobject.h"
#include "moteur2d.h"
#include <iostream>

FixedObject::FixedObject(bool addToFixedObjectList)
{
    m_indexOfDO = -1;
    if (addToFixedObjectList)
        Moteur2D::getInstance()->addFixedObject(this);
}

FixedObject::~FixedObject()
{
    Moteur2D::getInstance()->deleteFixedObject(this);
    if (m_drawableObject)
    {
        delete m_drawableObject;
    }

    if (m_indexOfDO>=0)
    {
        Moteur2D::getInstance()->deleteDrawable(m_indexOfDO);
    }
}
//*/
