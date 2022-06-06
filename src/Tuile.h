#ifndef __TUILE_H__
#define __TUILE_H__

#include <string>
#include <array>
#include <iostream>

using namespace std;

namespace Carcassonne {

    enum class directionRotation{droite, gauche};

    class Environnement;

    class IdentificateurTuile {

        friend class Tuile;

    private:
        const string idString = "";
        string idExtension = "";
        int nbTuile;

        IdentificateurTuile(const string& str);
        ~IdentificateurTuile()=default;

    public:
        const string& getId() const { return idString; }
        const string& getExtension() const { return idExtension; }
        int getNbTuile() const { return nbTuile; }
    };

    class Tuile {
    public:

        static const size_t NB_ZONES = 9;

    private:

        const IdentificateurTuile idTuile; //Identificateur de la carte, pour retrouver son dessin
        array<Environnement*, NB_ZONES> surfaces; //Tableau de taille 8, representant les zones des bordures, partant de haut-gauche, puis dans le sens horaire
    public:
        Tuile(std::string& id, std::string& zonesSurfaces);

        ~Tuile()=default;

        const IdentificateurTuile& getID() const {
            return idTuile;
        }

        Tuile* rotation(const directionRotation& dir);

        void affiche(ostream& f, bool isinline=false) const;

        string toString(bool isinline=false) const;
    };

}

#endif
