#ifndef GRAVITY_H
#define GRAVITY_H

#include "animatedobject.h"
#include "updatable.h"
#include <vector>
#include "SFML/Graphics.hpp"

class Gravity : public Updatable
{
    public:
        enum GravityType
        {
            UNIFORM, // Direction et intensité de la gravité fixe. Parfait pour simuler la gravité sur terre
            PONCTUAL_UNIFORM, // Intensité fixe, la direction dépend des positions de l'objet et du centre de gravité
            PONCTUAL // g = G*m/d, dir comme PONCTUAL_UNIFORM
        };


        // Constructeur par défaut construit une gravité terrestre uniforme
        Gravity();
        virtual ~Gravity();
        // Methode pour la mise à jour
        void update(float seconds);

        // Supprime tous les objets de sa liste d'objets affectés par sa gravité
        void eraseObjects();
        // Regarde dans la liste d'objets animés du Moteur2D et les ajoute à sa liste d'objets affectés par sa gravité
        void addAllAnimatedObject();
        // Ajoute un objet à sa liste d'objets affectés par sa gravité
        void addAnimatedObject(AnimatedObject * ao)
        {
            m_objects.push_back(ao);
        }

        // SETTERS
        // Exemple gravité Uniforme
        void setTerrestrianGravity();
        // Exemple gravité Uniforme Ponctuelle
        void setTerrestrianPointGravity();
        // Exemple gravité Ponctuelle pour une echelle au system solaire
        void setSolarSystemGravity();
        void setPixMetersScale(float value)
        {
            m_pixMetersScale = value;
        }
        void setGravityVector(const sf::Vector2f & gv)
        {
            m_gravityVector.x = gv.x;
            m_gravityVector.y = gv.y;
        }
        void setGravityType(GravityType gt)
        {
            m_gravityType = gt;
        }
        void setMass(float m)
        {
            m_mass = m;
        }
        void setTemporalScale(float temporalScale)
        {
            m_temporalScale = temporalScale;
        }

        int m_id;
    protected:
        std::vector<AnimatedObject*> m_objects;

        // Echelle pixel/metres
        float m_pixMetersScale;

        // Carac de la gravité
        // Type de gravité
        GravityType m_gravityType;
        // Direction ou point de gravité, dépend du type de gravité
        sf::Vector2f m_gravityVector;
        // Force gravitationnelle
        float m_forceGravitationnelle;
        // Masse de l'objet créant la gravité
        float m_mass;
        // Rapport temporel : temps simu sur temps réel, ex : =86400 -> 1seconde vaut un jour
        float m_temporalScale;

    private:
};

#endif // GRAVITY_H
