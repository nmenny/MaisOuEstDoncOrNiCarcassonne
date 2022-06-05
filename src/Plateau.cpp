#include <string>
#include <algorithm>

#include "Plateau.h"

namespace Carcassonne {

    const string chaineCaseVide = "         ";

	void Plateau::affiche(ostream& f) const {

        vector<string> ligne;

        // Parcours chaque ligne du plateau
        for(auto line : plateau) {
            ligne.clear();
            // Parcours chaque colonne de la ligne
            for(auto column : line) {
                // Si la colonne est vide, on met un espacement
                if(column == nullptr) {
                    ligne.push_back(chaineCaseVide);
                } else {
                    // Sinon, on converti la Tuile en chaine de caracteres
                    ligne.push_back(column->toString(true));
                }
            }

            size_t idxLine = 0;
            // On affiche sur 3 lignes les tuiles
            for(; idxLine < Tuile::NB_ZONES; idxLine += 3) {
                for(string col : ligne) {
                    f << col.substr(idxLine, 3);
                }
                f << "\n";
            }

        }

	}

	Coordonnees Plateau::getEmplacementsOuPeutPoser() const {
        Coordonnees vectC;

        for(size_t y = 0; y < NB_LIGNES_MAX; y++) {
            for(size_t x = 0; x < NB_COLONNES_MAX; x++) {
                // Si l'element courant est une tuile, on peut verifier que l'on peut poser autour d'elle
                if(plateau[y][x] != nullptr) {

                    // Placer en haut / bas
                    for(int offsetY = -1; offsetY < 2; offsetY += 2) {
                        Coordonnee c(x, y + offsetY);
                        if(c.getY() >= 0 && // Coordonnes avec l'offset dans les clous
                           c.getY() < NB_LIGNES_MAX &&
                           plateau[c.getY()][x] == nullptr && // Case a check n'a pas de Tuile
                           find(vectC.begin(), vectC.end(), c) == vectC.end()) // Les coordonnees ne sont pas deja renseignees
                        {
                            vectC.push_back(c);
                        }
                    }

                    // Placer a droite / gauche
                    for(int offsetX = -1; offsetX < 2; offsetX += 2) {
                        Coordonnee c(x + offsetX, y);
                        if(c.getX() >= 0 && // Coordonnes avec l'offset dans les clous
                           c.getX() < NB_COLONNES_MAX &&
                           plateau[y][c.getX()] == nullptr && // Case a check n'a pas de Tuile
                           find(vectC.begin(), vectC.end(), c) == vectC.end()) // Les coordonnees ne sont pas deja renseignees
                        {
                            vectC.push_back(c);
                        }
                    }

                }
            }
        }

        return vectC;

	}

	const Tuile* Plateau::poserTuile(const Coordonnee& c) {
	    // Verifie que l'on est bien dans les clous
        if(c.getX() < 0 || c.getX() >= NB_COLONNES_MAX || c.getY() < 0 || c.getY() >= NB_LIGNES_MAX) {
            throw PlateauException("Coordonnees hors du plateau !");
        }

        // Verfie que l'on ne place pas une tuile par dessus une autre
        if(plateau[c.getY()][c.getX()] != nullptr) {
            throw PlateauException("Ne peut pas placer une Tuile par dessus une autre !");
        }

        // Si on est sur le plateau, on ajoute simplement dedans
        plateau[c.getY()][c.getX()] = tuileCourante;

        // On garde en memoire la tuile posee
        const Tuile* tuilePosee = tuileCourante;

        // On pioche la suivante
        tuileCourante = pioche.piocher();

        return tuilePosee;

	}
}
