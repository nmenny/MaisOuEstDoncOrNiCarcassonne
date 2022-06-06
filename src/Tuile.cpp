#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "Tuile.h"
#include "Symbols.h"
#include "CarcassonneException.h"
#include "Utils.h"

#include "GestionnaireMemoireEnvironnement.h"

#include "Surface.h"
#include "Chemin.h"
#include "Batiment.h"

using namespace std;


namespace Carcassonne {

    IdentificateurTuile::IdentificateurTuile(const string& str) : idString(str) {
        // split l'identifiant
        vector<string> champs = splitString(str, '_');

        // Verifie que la ligne contient bien au moins deux champs (l'identifiant de l'extension et le numero de Tuile)
        if(champs.size() < 2) {
            throw TuileException("Identificateur de tuile pas dans le bon format !");
        }
        idExtension = champs[0];
        // Essaie de convertir le numero de Tuile en entier
        try {
            nbTuile = stoi(champs[1]);
        } catch(exception& e) {
            throw TuileException("Erreur de conversion de l'identificateur numerique de la Tuile en entier !");
        }
    }

    Tuile::Tuile(string& id, string& zonesSurfaces) : idTuile(id) {

        size_t arrayIdx = 0;

        // Selon le caractere, une structure differente est allouee
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

    Tuile* Tuile::rotation(const directionRotation& dir) {
        array<Environnement*, NB_ZONES> surfacesTmp;

        // Copie des elements d'environnement dans l'orientation actuelle
        for(size_t envIdx = 0; envIdx < NB_ZONES; envIdx++) {
            surfacesTmp[envIdx] = surfaces[envIdx];
        }

        // rotation
        switch(dir) {
        // Rotation a gauche
        case directionRotation::gauche:

            for(size_t envIdxLigne = 0; envIdxLigne < NB_ZONES / 3; envIdxLigne++) {
                for(size_t envIdxCol = 0; envIdxCol < NB_ZONES / 3; envIdxCol++) {
                    surfaces[6 - envIdxCol * 3 + envIdxLigne] = surfacesTmp[envIdxLigne * 3 + envIdxCol];
                }
            }

        break;
        // Rotation a droite
        case directionRotation::droite:

            for(size_t envIdxLigne = 0; envIdxLigne < NB_ZONES / 3; envIdxLigne++) {
                for(size_t envIdxCol = 0; envIdxCol < NB_ZONES / 3; envIdxCol++) {
                    surfaces[envIdxCol * 3 + 2 - envIdxLigne] = surfacesTmp[envIdxLigne * 3 + envIdxCol];
                }
            }

        break;
        }

        return this;
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
