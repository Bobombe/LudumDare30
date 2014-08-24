#ifndef UPDATABLE_H
#define UPDATABLE_H
#include <SFML/Graphics.hpp>

class Updatable
{
    public:
        virtual void update(float seconds)=0;
    protected:
    private:
};

#endif // UPDATABLE_H
