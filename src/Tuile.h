#ifndef __TUILE_H__
#define __TUILE_H__

#include <string>
#include <array>

using namespace std;

namespace Carcassonne {

    class Surface;
    class Chemin;
    class Batiment;

    class Tuile {
    private:

        static const size_t NB_ZONES = 8;

        const std::string ID; //Identificateur de la carte, pour retrouver son dessin
        array<Surface*, NB_ZONES> surfaces; //Tableau de taille 8, representant les zones des bordures, partant de haut-gauche, puis dans le sens horaire
        array<Batiment*, NB_ZONES> batiments;
        array<Chemin*, NB_ZONES> chemins; //Tableau de taille, representant les chemin sur chaque côté, partant du haut, puis sens horaire
    public:
        Tuile(std::string& id, std::string& zonesSurfaces, std::string& zonesChemins);

        ~Tuile()=default;

        std::string getID() {
            return ID;
        }
    };

}

#endif
