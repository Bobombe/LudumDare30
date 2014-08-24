#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

class View : public sf::View
{
    public:
        View();
        virtual ~View();

        // Déplace la vue selon l'offset
        void move(const sf::Vector2f &offset);
        void move(float offsetX, float offsetY);

        // Effectue un zoom centré sur la souris (le pixel sous le curseur ne bouge pas)
        //       et selon le facteur (<1 -> zoom=on voit de plus près)
        void zoomOnMouse(float factor);

        //Retrouve la position du curseur dans les coordonnées du monde depuis les coordonnée de l'écran
        sf::Vector2f getMouseInWorld();

        // Retourne le facteur de zoom
        float getZoom();
    protected:
    private:
};

#endif // VIEW_H
