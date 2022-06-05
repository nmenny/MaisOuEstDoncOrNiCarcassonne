#ifndef __TUILE_H__
#define __TUILE_H__

#include <string>
#include <array>
#include <iostream>

using namespace std;

namespace Carcassonne {

    enum class directionRotation{droite, gauche};

    class Environnement;

    class Tuile {
    public:

        static const size_t NB_ZONES = 9;

    private:

        const std::string ID = ""; //Identificateur de la carte, pour retrouver son dessin
        array<Environnement*, NB_ZONES> surfaces; //Tableau de taille 8, representant les zones des bordures, partant de haut-gauche, puis dans le sens horaire
    public:

        Tuile() {
            for(size_t zoneIdx = 0; zoneIdx < NB_ZONES; zoneIdx++) {
                surfaces[zoneIdx] = nullptr;
            }
        }

        Tuile(std::string& id, std::string& zonesSurfaces);

        ~Tuile()=default;

        std::string getID() {
            return ID;
        }

        Tuile& rotation(const directionRotation& dir);

        void affiche(ostream& f, bool isinline=false) const;

        string toString(bool isinline=false) const;
    };

}

#endif
