#ifndef __TUILE_H__
#define __TUILE_H__

#include <string>
#include <list>
#include "Surface.h"


namespace Carcassonne {
    static class Tuile {
    private :
        list<Surface*> surfaces; //Tableau de taille 8, representant les zones des bordures, partant de haut-gauche, puis dans le sens horaire
        list<Batiment*> batiments;
        list<Chemin*> chemins; //Tableau de taille, representant les chemin sur chaque côté, partant du haut, puis sens horaire
        const std::string ID; //Identificateur de la carte, pour retrouver son dessin
        bool eglise;
    public :
        Tuile(std::string id, list<Surface*>& zonesSurface, list<Batiment>& zonesBatiments, list<Chemin*>& zonesChemins, bool e) : surfaces(zonesSurface), batiments(zonesBatiments), chemins(zonesChemins), ID(id), eglise(e) {}

        ~Tuile()=default;
        
        std::string getID() {
            return ID;
        }

        bool getEglise() {return eglise;}
    };

}

#endif