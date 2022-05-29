#include <string>
#include <iostream>
#include <sstream>

#include "Tuile.h"
#include "Symbols.h"
#include "CarcassonneException.h"

#include "Villes.h"
#include "Pres.h"
#include "Abbayes.h"
#include "Jardins.h"
#include "Rivieres.h"
#include "Routes.h"

#include "Surface.h"
#include "Chemin.h"
#include "Batiment.h"


namespace Carcassonne {
    Tuile::Tuile(std::string& id, std::string& zonesSurfaces) : ID(id) {

        size_t arrayIdx = 0;
        for(char buildingChar : zonesSurfaces) {
            switch(buildingChar) {
            case C_PRES:
                surfaces[arrayIdx] = Pres::getInstance()->creerPre(this);break;
            case C_VILLE:
                surfaces[arrayIdx] = Villes::getInstance()->creerVille(this);break;
            case C_ABBAYE:
                surfaces[arrayIdx] = Abbayes::getInstance()->creerAbbaye(this);break;
            case C_JARDIN:
                surfaces[arrayIdx] = Jardins::getInstance()->creerJardin(this);break;
            case C_ROUTE:
                surfaces[arrayIdx] = Routes::getInstance()->creerRoute(this);break;
            case C_RIVIERE:
                surfaces[arrayIdx] = Rivieres::getInstance()->creerRiviere(this);break;
            default:
                throw TuileException("Un tel element de decors n'existe pas !");
            }
            arrayIdx++;
        }

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
