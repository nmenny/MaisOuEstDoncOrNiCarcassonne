/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#include <string>
#include <vector>
#include <algorithm>

#include "Environnement.h"
#include "Plateau.h"

namespace Carcassonne {

	void Plateau::affiche(ostream& f) const {

        vector<string> ligne;

        // Parcours chaque ligne du plateau
        for(auto line : plateau) {
            ligne.clear();
            // Parcours chaque colonne de la ligne
            for(auto column : line) {
                // Si la colonne est vide, on met un espacement
                if(column == nullptr) {
                    ligne.push_back(Tuile::TUILE_VIDE_STR);
                } else {
                    // Sinon, on converti la Tuile en chaine de caracteres
                    ligne.push_back(column->toString(true));
                }
            }

            size_t idxLine = 0;
            // On affiche sur NB_ENV_LIGNE lignes les tuiles
            for(; idxLine < Tuile::NB_ZONES; idxLine += Tuile::NB_ENV_COL) {
                for(string tuileStr : ligne) {
                    f << tuileStr.substr(idxLine, Tuile::NB_ENV_COL);
                }
                f << "\n";
            }

        }

	}

    Coordonnees Plateau::getEmplacementsOuPeutPoser() {
        Coordonnees coordsOk;

        for(const Coordonnee c : emplacementsVidesJouables) {

            bool verifCoord = true;
            array<Environnement*, Tuile::NB_ZONES_BORDURE> envACmp, envCmp;

            // En haut
            if(c.getY() - 1 >= 0 && plateau[c.getY() - 1][c.getX()] != nullptr) {
                envACmp = tuileCourante->getEnvironnementsDansUneZone(zoneTuile::nord);
                envCmp = plateau[c.getY() - 1][c.getX()]->getEnvironnementsDansUneZone(zoneTuile::sud);
                verifCoord &= envACmp[0]->peutEtreAdjacentA(envCmp[0]) &&
                envACmp[1]->peutEtreAdjacentA(envCmp[1]) &&
                envACmp[2]->peutEtreAdjacentA(envCmp[2]);
            }

            // En bas
            if(c.getY() + 1 < NB_LIGNES_MAX && plateau[c.getY() + 1][c.getX()] != nullptr) {
                envACmp = tuileCourante->getEnvironnementsDansUneZone(zoneTuile::sud);
                envCmp = plateau[c.getY() + 1][c.getX()]->getEnvironnementsDansUneZone(zoneTuile::nord);
                verifCoord &= envACmp[0]->peutEtreAdjacentA(envCmp[0]) &&
                envACmp[1]->peutEtreAdjacentA(envCmp[1]) &&
                envACmp[2]->peutEtreAdjacentA(envCmp[2]);
            }

            // a gauche
            if(c.getX() - 1 >= 0 && plateau[c.getY()][c.getX()-1] != nullptr) {
                envACmp = tuileCourante->getEnvironnementsDansUneZone(zoneTuile::ouest);
                envCmp = plateau[c.getY()][c.getX()-1]->getEnvironnementsDansUneZone(zoneTuile::est);
                verifCoord &= envACmp[0]->peutEtreAdjacentA(envCmp[0]) &&
                envACmp[1]->peutEtreAdjacentA(envCmp[1]) &&
                envACmp[2]->peutEtreAdjacentA(envCmp[2]);
            }

            // a droite
            if(c.getX() + 1 < NB_COLONNES_MAX && plateau[c.getY()][c.getX()+1] != nullptr) {
                envACmp = tuileCourante->getEnvironnementsDansUneZone(zoneTuile::est);
                envCmp = plateau[c.getY()][c.getX()+1]->getEnvironnementsDansUneZone(zoneTuile::ouest);
                verifCoord &= envACmp[0]->peutEtreAdjacentA(envCmp[0]) &&
                envACmp[1]->peutEtreAdjacentA(envCmp[1]) &&
                envACmp[2]->peutEtreAdjacentA(envCmp[2]);
            }

            if(verifCoord) {
                coordsOk.push_back(c);
            }

        }

        return coordsOk;
	}

    Coordonnees Plateau::getEmplacementOuPeutPoserMeeple(const Coordonnee& coordTuile) const {
        Coordonnees coordsOk;
        if(coordTuile.getX() < 0 || coordTuile.getX() >= static_cast<int>(NB_COLONNES_MAX) || coordTuile.getY() < 0 || coordTuile.getY() >= static_cast<int>(NB_LIGNES_MAX)) {
            throw PlateauException("Erreur, essaie d'acceder a une Tuile hors du plateau !");
        }
        if(plateau[coordTuile.getY()][coordTuile.getX()] == nullptr) {
            throw PlateauException("Erreur, essaie d'acceder a un emplacement sans tuile !");
        }
        Coordonnees cPosables = plateau[coordTuile.getY()][coordTuile.getX()]->recupEmplacementsOuMeeplesPosables();

        return cPosables;
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

        return tuileCourante;

	}

    const Meeple* Plateau::poserMeeple(Meeple* m, Environnement* env) {
        if(tuileCourante->peutPoserMeepleDessus(env) && m != nullptr) {
            tuileCourante->poserMeeple(*env, *m);
        }
        return m;
    }
}
