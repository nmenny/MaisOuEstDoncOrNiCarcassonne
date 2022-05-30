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

	// TODO : Corriger la fonction
    // Recupere tous les endroits ou l'on peut poser une Tuile
	Coordonnees Plateau::getEmplacementsOuPeutPoser() const {

        Coordonnees vectC;

        int x = 0;
        int y = 0;

        // Parcours toutes les lignes du plateau
        for(auto line : plateau) {
            x = 0;
            // Parcours toutes les colonnes de la ligne
            for(auto column : line) {

                // Si la colonne en question est une Tuile,
                if(column != nullptr) {

                    // placer en haut
                    if( (find(vectC.begin(), vectC.end(), Coordonnee(x,y-1)) == vectC.end()) && ((y == 0) || (plateau[x][y-1] == nullptr))) {
                        vectC.push_back(Coordonnee(x,y-1));
                    }

                    // placer a droite
                    if( (find(vectC.begin(), vectC.end(), Coordonnee(x+1,y)) == vectC.end()) && ((x >= nbColonnes-1) || (plateau[x+1][y] == nullptr))) {
                        vectC.push_back(Coordonnee(x+1,y));
                    }

                    // placer en bas
                    if( (find(vectC.begin(), vectC.end(), Coordonnee(x,y+1)) == vectC.end()) && ((y >= nbLignes-1) || (plateau[x][y+1] == nullptr))) {
                        vectC.push_back(Coordonnee(x,y+1));
                    }

                    // placer a gauche
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
	    // Verifie que l'on est bien dans les clous (autorise des coordonnees de (-1, -1) pour indiquer que l'on pose
        //  a gauche (hors du plateau) jusqu'à (nbColonnes, nbLignes) pour indiquer que l'on poser a droite
        if(c.getX() < -1 || c.getX() > nbColonnes || c.getY() < -1 || c.getY() > nbLignes) {
            throw PlateauException("Ne peut pas poser une tuile a ces coordonnees !");
        }

        // Si on est sur le plateau, on ajoute simplement dedans
        if(c.getX() >= 0 && c.getX() < nbColonnes && c.getY() >= 0 && c.getY() < nbLignes && plateau[c.getX()][c.getY()] == nullptr) {
            plateau[c.getY()][c.getX()] = tuileCourante;
        } else { // Sinon, il faut agrandir le plateau

            // Si l'on veut ajouter sur la gauche du plateau
            if(c.getX() < 0) {

                // Parcours toutes les lignes et ajoute un element en tete pour chaque
                for(int lineIdx = 0; lineIdx < nbLignes; lineIdx++) {
                    plateau[lineIdx].insert(plateau[lineIdx].begin(), nullptr);
                }

                nbColonnes++;

                // Ajoute la tuile au plateau
                plateau[c.getY()][c.getX()+1] = tuileCourante;

            } else if(c.getX() >= nbColonnes) { // Sinon, si on veut ajouter à droite du plateau

                // Parcours toutes les lignes et ajoute un element en queue pour chaque
                for(int lineIdx = 0; lineIdx < nbLignes; lineIdx++) {
                    plateau[lineIdx].push_back(nullptr);
                }

                nbColonnes++;

                // Ajoute la tuile au plateau
                plateau[c.getY()][c.getX()] = tuileCourante;

            } else if(c.getY() < 0) { // Sinon, si l'on veut ajouter en haut du plateau

                // On insere une nouvelle ligne en haut
                plateau.insert(plateau.begin(), vector<const Tuile*>());

                // On parcours cette nouvelle ligne afin de la remplir de valeurs nulles
                for(int colIdx = 0; colIdx < nbColonnes; colIdx++) {
                    plateau[0].push_back(nullptr);
                }

                nbLignes++;

                // Ajoute la tuile au plateau
                plateau[c.getY()+1][c.getX()] = tuileCourante;
            } else { // Sinon, on veut donc ajouter en bas du plateau

                // On insere une nouvelle ligne en bas
                plateau.push_back(vector<const Tuile*>());

                // On parcours cette nouvelle ligne afin de la remplir de valeurs nulles
                for(int colIdx = 0; colIdx < nbColonnes; colIdx++) {
                    plateau[nbColonnes].push_back(nullptr);
                }

                nbLignes++;

                // Ajoute la tuile au plateau
                plateau[c.getY()][c.getX()] = tuileCourante;
            }
        }

        // On garde en memoire la tuile posee
        const Tuile* tuilePosee = tuileCourante;

        // On pioche la suivante
        tuileCourante = pioche.piocher();

        return tuilePosee;

	}
}
