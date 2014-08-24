#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "gravity.h"
#include <fixedsprite.h>
#include "maincharacter.h"
#include "planete.h"

class WorldManager
{
    public:
        static WorldManager* getInstance();
        void load();
        void lectureMonde(std::string monde);
        MainCharacter* getPerso()
        {
            return m_perso;
        }
    protected:
        WorldManager();
        virtual ~WorldManager();
        void init();
        static WorldManager * m_instance;

        Gravity* m_gravity;
        FixedSprite *m_soleil;
        MainCharacter * m_perso;
        std::vector <Planete*> m_planetes;
    private:
};

#endif // WORLDMANAGER_H
