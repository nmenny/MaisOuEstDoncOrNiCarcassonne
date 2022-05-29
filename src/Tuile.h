#ifndef __TUILE_H__
#define __TUILE_H__

#include <string>
#include <list>

using namespace std;

namespace Carcassonne {

    class Surface;
    class Chemin;

    class Tuile {
    private:
        const std::string ID; //Identificateur de la carte, pour retrouver son dessin
        list<Surface*> surfaces; //Tableau de taille 8, representant les zones des bordures, partant de haut-gauche, puis dans le sens horaire
        //list<Batiment*> batiments;
        list<Chemin*> chemins; //Tableau de taille, representant les chemin sur chaque côté, partant du haut, puis sens horaire
    public:
        Tuile(std::string& id, std::string& zonesSurfaces, std::string& zonesChemins);

        ~Tuile()=default;

        std::string getID() {
            return ID;
        }
    };

}

#endif
