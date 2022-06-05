#include <string>
#include <iostream>
#include <sstream>

#include "Tuile.h"
#include "Symbols.h"
#include "CarcassonneException.h"

#include "GestionnaireMemoireEnvironnement.h"

#include "Surface.h"
#include "Chemin.h"
#include "Batiment.h"


namespace Carcassonne {
    Tuile::Tuile(std::string& id, std::string& zonesSurfaces) : ID(id) {

        size_t arrayIdx = 0;
        for(char buildingChar : zonesSurfaces) {
            switch(buildingChar) {
            case C_PRES:
                surfaces[arrayIdx] = Pres::getInstance()->creer(this);break;
            case C_VILLE:
                surfaces[arrayIdx] = Villes::getInstance()->creer(this);break;
            case C_ABBAYE:
                surfaces[arrayIdx] = Abbayes::getInstance()->creer(this);break;
            case C_JARDIN:
                surfaces[arrayIdx] = Jardins::getInstance()->creer(this);break;
            case C_ROUTE:
                surfaces[arrayIdx] = Routes::getInstance()->creer(this);break;
            case C_RIVIERE:
                surfaces[arrayIdx] = Rivieres::getInstance()->creer(this);break;
            default:
                throw TuileException("Un tel element de decors n'existe pas !");
            }
            arrayIdx++;
        }

    }

    Tuile& Tuile::rotation(const directionRotation& dir) {
        array<Environnement*, NB_ZONES> surfacesTmp;

        // Copie des elements d'environnement dans l'orientation actuelle
        for(size_t envIdx = 0; envIdx < NB_ZONES; envIdx++) {
            surfacesTmp[envIdx] = surfaces[envIdx];
        }

        // rotation
        switch(dir) {
        case directionRotation::gauche:

            for(size_t envIdxLigne = 0; envIdxLigne < NB_ZONES / 3; envIdxLigne++) {
                for(size_t envIdxCol = 0; envIdxCol < NB_ZONES / 3; envIdxCol++) {
                    surfaces[6 - envIdxCol * 3 + envIdxLigne] = surfacesTmp[envIdxLigne * 3 + envIdxCol];
                }
            }

        break;
        case directionRotation::droite:

            for(size_t envIdxLigne = 0; envIdxLigne < NB_ZONES / 3; envIdxLigne++) {
                for(size_t envIdxCol = 0; envIdxCol < NB_ZONES / 3; envIdxCol++) {
                    surfaces[envIdxCol * 3 + 2 - envIdxLigne] = surfacesTmp[envIdxLigne * 3 + envIdxCol];
                }
            }

        break;
        }

        return *this;
    }

    void Tuile::affiche(ostream& f, bool isinline) const {
        string str;

        for(size_t decorsIdx = 0; decorsIdx < Tuile::NB_ZONES; decorsIdx++) {
            if(surfaces[decorsIdx] == nullptr) {
                throw TuileException("Tuile non definie !");
            }
            str += (surfaces[decorsIdx])->toChar();
        }

        if(!isinline) {
            f << str.substr(0, 3) << "\n"
              << str.substr(3, 3) << "\n"
              << str.substr(6, 3) << "\n";
        } else {
            f << str;
        }
    }

    string Tuile::toString(bool isinline) const {
        stringstream stream;
        affiche(stream, isinline);

        return stream.str();
    }
}
