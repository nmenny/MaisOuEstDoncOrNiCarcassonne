#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Tuile.h"
#include "Symbols.h"
#include "CarcassonneException.h"
#include "Utils.h"
#include "Coordonnee.h"

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

        fusionnerEnvironnementsInternes();

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


    void Tuile::poserMeeple(const Environnement& env, Meeple& m) {
        // Verifie si la Tuile n'a pas deja un meeple
        if(environnementAvecMeeple != nullptr) {
            throw TuileException("Erreur, cette Tuile possede deja un Meeple !");
        }

        // Recherche l'indice en memoire de l'environnement
        size_t idxEnv = 0;
        while((idxEnv < NB_ZONES) && (surfaces[idxEnv] != &env)) {
            idxEnv++;
        }

        // Verifie si l'environnement ou l'on souhaite poser le Meeple n'appartient pas a cette Tuile
        if(idxEnv >= NB_ZONES) {
            throw TuileException("Erreur, la Tuile ne possede pas cet environnement !");
        }

        // Pose le meeple
        environnementAvecMeeple = surfaces[idxEnv];
        indiceDeEnvAvecMeeple = idxEnv;
        environnementAvecMeeple->poserMeeple(&m);
    }

    Meeple* Tuile::retirerMeeple() {
        // Verifie que la Tuile possede bien un meeple
        if(environnementAvecMeeple == nullptr) {
            throw TuileException("Erreur, cette Tuile ne possede pas de Meeple !");
        }

        // Retire un meeple
        Meeple* meeple = environnementAvecMeeple->retirerMeeple();
        environnementAvecMeeple = nullptr;
        indiceDeEnvAvecMeeple = -1;

        return meeple;
    }

    void Tuile::fusionnerEnvironnementsAdjacents(int x, int y, Environnement* envDiff) {
        Coordonnees* parcours = new Coordonnees();
        parcours->push_back(Coordonnee(x,y));

        surfaces[y * 3 + x] = fusion(envDiff, surfaces[y * 3 + x]);

         // Check en haut
        if(
           ((y - 1) >= 0) &&
           surfaces[(y -1)*3 + x]->toChar() == envDiff->toChar() &&
           (find(parcours->begin(), parcours->end(), Coordonnee(x, y-1)) == parcours->end())
           ) {
            fusionnerEnvironnementsAdjacentsRec(x, y-1, envDiff, parcours);
        }

        // Check en bas
        if(
           ((y + 1) < 3) &&
           surfaces[(y + 1)*3 + x]->toChar() == envDiff->toChar() &&
           (find(parcours->begin(), parcours->end(), Coordonnee(x, y+1)) == parcours->end())
           ) {
            fusionnerEnvironnementsAdjacentsRec(x, y+1, envDiff, parcours);
        }

        // Check a gauche
        if(
           (x - 1 >= 0) &&
           surfaces[y*3 + x-1]->toChar() == envDiff->toChar() &&
           (find(parcours->begin(), parcours->end(), Coordonnee(x-1, y)) == parcours->end())
           ) {
            fusionnerEnvironnementsAdjacentsRec(x-1, y, envDiff, parcours);
        }

        // Check a droite
        if(
           (x + 1 < 3) &&
           surfaces[y*3 + x+1]->toChar() == envDiff->toChar() &&
           (find(parcours->begin(), parcours->end(), Coordonnee(x+1, y)) == parcours->end())
           ) {
            fusionnerEnvironnementsAdjacentsRec(x+1, y, envDiff, parcours);
        }

        delete parcours;
    }

    Environnement* Tuile::fusion(Environnement* evt1, Environnement* evt2) {
        const char envSymbole = evt1->toChar();

        if(envSymbole != evt2->toChar()) {
            return nullptr;
        }

        switch(envSymbole) {
        case C_PRES:
            Pres::getInstance()->fusionner(dynamic_cast<Pre*>(evt1), dynamic_cast<Pre*>(evt2));
            break;
        case C_VILLE:
            Villes::getInstance()->fusionner(dynamic_cast<Ville*>(evt1), dynamic_cast<Ville*>(evt2));
            break;
        case C_ABBAYE:
            Abbayes::getInstance()->fusionner(dynamic_cast<Abbaye*>(evt1), dynamic_cast<Abbaye*>(evt2));
            break;
        case C_JARDIN:
            Jardins::getInstance()->fusionner(dynamic_cast<Jardin*>(evt1), dynamic_cast<Jardin*>(evt2));
            break;
        case C_ROUTE:
            Routes::getInstance()->fusionner(dynamic_cast<Route*>(evt1), dynamic_cast<Route*>(evt2));
            break;
        case C_RIVIERE:
            Rivieres::getInstance()->fusionner(dynamic_cast<Riviere*>(evt1), dynamic_cast<Riviere*>(evt2));
            break;
        default:
            throw TuileException("Un tel element de decors n'existe pas !");
        }

        return evt1;
    }

    void Tuile::fusionnerEnvironnementsAdjacentsRec(int x, int y, Environnement* envDiff, Coordonnees* parcours) {
        if(x < 0 || x >= 3 || y < 0 || y >= 3 || surfaces[y*3+x]->toChar() != envDiff->toChar()) {
            return;
        }

        surfaces[y * 3 + x] = fusion(envDiff, surfaces[y * 3 + x]);
        parcours->push_back(Coordonnee(x,y));

        // Check en haut
        if(
           ((y - 1) >= 0) &&
           surfaces[(y -1)*3 + x]->toChar() == envDiff->toChar() &&
           (find(parcours->begin(), parcours->end(), Coordonnee(x, y-1)) == parcours->end())
           ) {
            fusionnerEnvironnementsAdjacentsRec(x, y-1, envDiff, parcours);
        }

        // Check en bas
        if(
           ((y + 1) < 3) &&
           surfaces[(y + 1)*3 + x]->toChar() == envDiff->toChar() &&
           (find(parcours->begin(), parcours->end(), Coordonnee(x, y+1)) == parcours->end())
           ) {
            fusionnerEnvironnementsAdjacentsRec(x, y+1, envDiff, parcours);
        }

        // Check a gauche
        if(
           (x - 1 >= 0) &&
           surfaces[y*3 + x-1]->toChar() == envDiff->toChar() &&
           (find(parcours->begin(), parcours->end(), Coordonnee(x-1, y)) == parcours->end())
           ) {
            fusionnerEnvironnementsAdjacentsRec(x-1, y, envDiff, parcours);
        }

        // Check a droite
        if(
           (x + 1 < 3) &&
           surfaces[y*3 + x+1]->toChar() == envDiff->toChar() &&
           (find(parcours->begin(), parcours->end(), Coordonnee(x+1, y)) == parcours->end())
           ) {
            fusionnerEnvironnementsAdjacentsRec(x+1, y, envDiff, parcours);
        }

    }

    void Tuile::fusionnerEnvironnementsInternes() {
        // Stocke les environnments de maniere unique
        vector<Environnement*> envUniques;

        int y = 0;
        int x = 0;

        // Parcours tous les environnements de la Tuile
        while(y < static_cast<int>(NB_ZONES) / 3) {
            x = 0;
            while(x < static_cast<int>(NB_ZONES) / 3) {
                vector<Environnement*>::iterator it;
                // Si l'environnement courant n'a pas deja ete fusionne
                if((it = find(envUniques.begin(), envUniques.end(), surfaces[y * 3 + x]))  == envUniques.end() ) {

                    fusionnerEnvironnementsAdjacents(x,y,surfaces[y * 3 + x]);

                    envUniques.push_back(surfaces[y * 3 + x]);
                }
                x++;
            }
            y++;
        }


    }

}
