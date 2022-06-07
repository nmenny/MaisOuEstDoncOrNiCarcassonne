#include <string>
#include <vector>
#include <algorithm>

#include "Environnement.h"
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

	Coordonnees Plateau::getEmplacementsOuPeutPoser() {
        Coordonnees coordsOk;

        for(Coordonnee c : emplacementsVidesJouables) {

            bool verifCoord = true;
            array<Environnement*, 3> envACmp, envCmp;

            // En haut
            if(c.getY() - 1 >= 0 && plateau[c.getY() - 1][c.getX()] != nullptr) {
                envACmp = tuileCourante->getEnvironnementsDansUneZone(direction::nord);
                envCmp = plateau[c.getY() - 1][c.getX()]->getEnvironnementsDansUneZone(direction::sud);
                verifCoord &= (envACmp[0]->toChar() == envCmp[0]->toChar()) &&
                (envACmp[1]->toChar() == envCmp[1]->toChar()) &&
                (envACmp[2]->toChar() == envCmp[2]->toChar());
            }

            // En bas
            if(c.getY() + 1 < NB_LIGNES_MAX && plateau[c.getY() + 1][c.getX()] != nullptr) {
                envACmp = tuileCourante->getEnvironnementsDansUneZone(direction::sud);
                envCmp = plateau[c.getY() + 1][c.getX()]->getEnvironnementsDansUneZone(direction::nord);
                verifCoord &= (envACmp[0]->toChar() == envCmp[0]->toChar()) &&
                (envACmp[1]->toChar() == envCmp[1]->toChar()) &&
                (envACmp[2]->toChar() == envCmp[2]->toChar());
            }

            // a gauche
            if(c.getX() - 1 >= 0 && plateau[c.getY()][c.getX()-1] != nullptr) {
                envACmp = tuileCourante->getEnvironnementsDansUneZone(direction::ouest);
                envCmp = plateau[c.getY()][c.getX()-1]->getEnvironnementsDansUneZone(direction::est);
                verifCoord &= (envACmp[0]->toChar() == envCmp[0]->toChar()) &&
                (envACmp[1]->toChar() == envCmp[1]->toChar()) &&
                (envACmp[2]->toChar() == envCmp[2]->toChar());
            }

            // a droite
            if(c.getX() + 1 < NB_COLONNES_MAX && plateau[c.getY()][c.getX()+1] != nullptr) {
                envACmp = tuileCourante->getEnvironnementsDansUneZone(direction::est);
                envCmp = plateau[c.getY()][c.getX()+1]->getEnvironnementsDansUneZone(direction::ouest);
                verifCoord &= (envACmp[0]->toChar() == envCmp[0]->toChar()) &&
                (envACmp[1]->toChar() == envCmp[1]->toChar()) &&
                (envACmp[2]->toChar() == envCmp[2]->toChar());
            }

            if(verifCoord) {
                coordsOk.push_back(c);
            }

        }

        return coordsOk;
	}

	void Plateau::getEmplacementsVidesAutourDeTuile(int x, int y) {
        // Si l'element courant est une tuile, on peut verifier que l'on peut poser autour d'elle
        if(plateau[y][x] != nullptr) {

            // Placer en haut / bas
            for(int offsetY = -1; offsetY < 2; offsetY += 2) {
                Coordonnee c(x, y + offsetY);
                if(c.getY() >= 0 && // Coordonnes avec l'offset dans les clous
                   c.getY() < NB_LIGNES_MAX &&
                   plateau[c.getY()][x] == nullptr && // Case a check n'a pas de Tuile
                   find(emplacementsVidesJouables.begin(), emplacementsVidesJouables.end(), c) == emplacementsVidesJouables.end()) // Les coordonnees ne sont pas deja renseignees
                {
                    emplacementsVidesJouables.push_back(c);
                }
            }

            // Placer a droite / gauche
            for(int offsetX = -1; offsetX < 2; offsetX += 2) {
                Coordonnee c(x + offsetX, y);
                if(c.getX() >= 0 && // Coordonnes avec l'offset dans les clous
                   c.getX() < NB_COLONNES_MAX &&
                   plateau[y][c.getX()] == nullptr && // Case a check n'a pas de Tuile
                   find(emplacementsVidesJouables.begin(), emplacementsVidesJouables.end(), c) == emplacementsVidesJouables.end()) // Les coordonnees ne sont pas deja renseignees
                {
                    emplacementsVidesJouables.push_back(c);
                }
            }
        }
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

        // On ajoute simplement dedans
        plateau[c.getY()][c.getX()] = tuileCourante;

        // L'emplacement ou la tuile a ete posee n'est plus vide
        emplacementsVidesJouables.remove(c);

        // recupere les emplacements vides autour de la tuile posee
        getEmplacementsVidesAutourDeTuile(c.getX(), c.getY());

        // On pioche la suivante
        tuileCourante = pioche.piocher();

        return plateau[c.getY()][c.getX()];

	}
}
