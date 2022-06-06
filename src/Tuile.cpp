#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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


    void Tuile::fusionnerEnvironnementsInternes() {

        vector<Environnement*> envUniques;

        int y = 0;
        int x = 0;

        while(y < NB_ZONES / 3) {
            x = 0;
            while(x < NB_ZONES / 3) {
                vector<Environnement*>::iterator it;
                if((it = find(envUniques.begin(), envUniques.end(), surfaces[y * 3 + x]))  == envUniques.end() ) {
                    Environnement* env = surfaces[y * 3 + x];
                    const char envSymbole = env->toChar();

                    int offsetX = -x;
                    int offsetY = -y;

                    while(offsetY <= -y + 2) {

                        while(offsetX <= -x + 2) {

                            if(offsetX == 0 && offsetY == 0) {
                                offsetX++;
                                continue;
                            }

                            if(surfaces[(y + offsetY)*3 + x+offsetX]->toChar() == envSymbole) {

                                if(
                                   (((y + offsetY-1) >= 0) && surfaces[(y + offsetY-1)*3 + x+offsetX] == env) || // Check en haut
                                   (((y + offsetY+1) < 3) && surfaces[(y + offsetY+1)*3 + x+offsetX] == env) || // Check en bas
                                   ((x+offsetX-1 >= 0) && surfaces[(y + offsetY)*3 + x+offsetX-1] == env) || // Check a gauche
                                   ((x+offsetX+1 < 3) && surfaces[(y + offsetY)*3 + x+offsetX+1] == env) // Check a droite
                                  ) {
                                    switch(envSymbole) {
                                    case C_PRES:
                                        Pres::getInstance()->fusionner(dynamic_cast<Pre*>(env), dynamic_cast<Pre*>(surfaces[(y + offsetY)*3 + x+offsetX]));
                                        break;
                                    case C_VILLE:
                                        Villes::getInstance()->fusionner(dynamic_cast<Ville*>(env), dynamic_cast<Ville*>(surfaces[(y + offsetY)*3 + x+offsetX]));
                                        break;
                                    case C_ABBAYE:
                                        Abbayes::getInstance()->fusionner(dynamic_cast<Abbaye*>(env), dynamic_cast<Abbaye*>(surfaces[(y + offsetY)*3 + x+offsetX]));
                                        break;
                                    case C_JARDIN:
                                        Jardins::getInstance()->fusionner(dynamic_cast<Jardin*>(env), dynamic_cast<Jardin*>(surfaces[(y + offsetY)*3 + x+offsetX]));
                                        break;
                                    case C_ROUTE:
                                        Routes::getInstance()->fusionner(dynamic_cast<Route*>(env), dynamic_cast<Route*>(surfaces[(y + offsetY)*3 + x+offsetX]));
                                        break;
                                    case C_RIVIERE:
                                        Rivieres::getInstance()->fusionner(dynamic_cast<Riviere*>(env), dynamic_cast<Riviere*>(surfaces[(y + offsetY)*3 + x+offsetX]));
                                        break;
                                    default:
                                        throw TuileException("Un tel element de decors n'existe pas !");
                                    }

                                    surfaces[(y + offsetY)*3 + x+offsetX] = env;
                                }

                            }
                            offsetX++;
                        }
                        offsetY++;
                    }

                    envUniques.push_back(env);
                }
                x++;
            }
            y++;
        }


    }

}
