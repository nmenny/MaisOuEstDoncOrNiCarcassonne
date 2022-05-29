#ifndef __JEU_H__
#define __JEU_H__

#include <vector>

#include "Coordonnee.h"

#include "Joueurs.h"
#include "Villes.h"
#include "Pres.h"
#include "Abbayes.h"
#include "Jardins.h"
#include "Rivieres.h"
#include "Routes.h"
#include "Plateau.h"

#include <iostream>

namespace Carcassonne {

    class Jeu {

    private:

        Plateau plateau;

        Joueurs* joueurs;

        Joueur* joueurCourant;

        vector<Coordonnee> emplacementJouables;

    public:

        Jeu(int joueur = 2) {
            int tmp = joueur;
            joueurs = Joueurs::getInstance();
            joueurCourant = joueurs->getJoueur(0);

            try {
                while(tmp > 2) {
                    joueurs->ajouterJoueur();
                    tmp--;
                }
            } catch(JoueurException& e) {}
        }

        ~Jeu() {
            Joueurs::libererInstance();
            Abbayes::libererInstance();
            Jardins::libererInstance();
            Pres::libererInstance();
            Rivieres::libererInstance();
            Routes::libererInstance();
            Villes::libererInstance();
        }

        void partie();

    private:

        void nextJoueur() {
            joueurCourant = joueurs->getJoueur((joueurCourant->getNumero() + 1) % joueurs->getNbJoueurs());
        }

        void recupEmplacementsJouables() {
            emplacementJouables.clear();
            emplacementJouables = plateau.getEmplacementsOuPeutPoser();
        }

        void afficheEmplacementsJouables(std::ostream& f) const;

        void afficheScore(std::ostream& f) const;

        int getJoueurGagnant() const {
            int idxJoueurScoreMax = -1, scoreMax = -1;
            for(int idxJoueur = 0; idxJoueur < joueurs->getNbJoueurs(); idxJoueur++) {
                if(joueurs->getJoueur(idxJoueur)->getScore() > scoreMax) {
                    scoreMax = joueurs->getJoueur(idxJoueur)->getScore();
                    idxJoueurScoreMax = idxJoueur;
                }
            }
            return idxJoueurScoreMax;
        }

    };

}

#endif
