#include <string>
#include <algorithm>

#include "Plateau.h"

namespace Carcassonne {

    const string chaineCaseVide = "         ";


	void Plateau::affiche(ostream& f) const {

        vector<string> ligne;

        for(auto line : plateau) {
            ligne.clear();
            for(auto column : line) {
                if(column == nullptr) {
                    ligne.push_back(chaineCaseVide);
                } else {
                    ligne.push_back(column->toString(true));
                }
            }

            size_t idxLine = 0;
            for(; idxLine < Tuile::NB_ZONES; idxLine += 3) {
                for(string col : ligne) {
                    f << col.substr(idxLine, 3);
                }
                f << "\n";
            }

        }

	}

	vector<Coordonnee> Plateau::getEmplacementsOuPeutPoser() const {

        vector<Coordonnee> vectC;

        int x = 0;
        int y = 0;
        for(auto line : plateau) {
            x = 0;
            for(auto column : line) {
                if(column != nullptr) {

                    // en haut
                    if( (find(vectC.begin(), vectC.end(), Coordonnee(x,y-1)) == vectC.end()) && ((y == 0) || (plateau[x][y-1] == nullptr))) {
                        vectC.push_back(Coordonnee(x,y-1));
                    }

                    // a droite
                    if( (find(vectC.begin(), vectC.end(), Coordonnee(x+1,y)) == vectC.end()) && ((x >= nbColonnes-1) || (plateau[x+1][y] == nullptr))) {
                        vectC.push_back(Coordonnee(x+1,y));
                    }

                    // en bas
                    if( (find(vectC.begin(), vectC.end(), Coordonnee(x,y+1)) == vectC.end()) && ((y >= nbLignes-1) || (plateau[x][y+1] == nullptr))) {
                        vectC.push_back(Coordonnee(x,y+1));
                    }

                    // a gauche
                    if( (find(vectC.begin(), vectC.end(), Coordonnee(x-1,y)) == vectC.end()) && ((x == 0) || (plateau[x-1][y] == nullptr))) {
                        vectC.push_back(Coordonnee(x-1,y));
                    }
                }
                x++;
            }
            y++;
        }

        return vectC;

	}

	const Tuile* Plateau::poserTuile(const Coordonnee& c) {
        if(c.getX() < -1 || c.getX() > nbColonnes || c.getY() < -1 || c.getY() > nbLignes) {
            throw PlateauException("Ne peut pas poser une tuile a ces coordonnees !");
        }

        if(c.getX() >= 0 && c.getX() < nbColonnes && c.getY() >= 0 && c.getY() < nbLignes && plateau[c.getX()][c.getY()] == nullptr) {
            plateau[c.getX()][c.getY()] = tuileCourante;
        } else {
            if(c.getX() < 0) {

                for(int lineIdx = 0; lineIdx < nbLignes; lineIdx++) {
                    plateau[lineIdx].insert(plateau[lineIdx].begin(), nullptr);
                }

                nbColonnes++;

                plateau[c.getY()][c.getX()+1] = tuileCourante;

            } else if(c.getX() >= nbColonnes) {

                for(int lineIdx = 0; lineIdx < nbLignes; lineIdx++) {
                    plateau[lineIdx].push_back(nullptr);
                }

                nbColonnes++;

                plateau[c.getY()][c.getX()] = tuileCourante;

            } else if(c.getY() < 0) {

                plateau.insert(plateau.begin(), vector<const Tuile*>());

                for(int colIdx = 0; colIdx < nbColonnes; colIdx++) {
                    plateau[0].push_back(nullptr);
                }

                nbLignes++;

                plateau[c.getY()+1][c.getX()] = tuileCourante;
            } else {

                plateau.push_back(vector<const Tuile*>());

                for(int colIdx = 0; colIdx < nbColonnes; colIdx++) {
                    plateau[nbColonnes].push_back(nullptr);
                }

                nbLignes++;

                plateau[c.getY()][c.getX()] = tuileCourante;
            }
        }

        const Tuile* tmp = tuileCourante;

        tuileCourante = pioche.piocher();

        return tmp;

	}
}
