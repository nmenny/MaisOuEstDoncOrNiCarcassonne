/*! \file Jeu.h
    \version 0.1
*/


#ifndef __JEU_H__
#define __JEU_H__

#include <vector>

#include "Coordonnee.h"
#include "Interface.h"

#include <iostream>

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Jeu
        \brief Represente une partie de Carcassonne
    */
    class Jeu {

    private:

        Plateau plateau; /*!< Le plateau de jeu */

        Joueurs* joueurs; /*!< Les joueurs presents dans la partie */

        Joueur* joueurCourant; /*!< Le joueur dont c'est le tour */

        Coordonnees emplacementJouables; /*!< Liste des emplacements jouables a l'instant t */

        Interface& interface; /*!< Interface utilisateur */

    public:

        /*! \brief Constructeur de Jeu
            \param[in] L'interface utilisateur utilisee
            \param[in] Le nombre de joueurs dans la partie
                <defaut: 2>
        */
        Jeu(Interface& i, int joueur = 2) : interface(i) {
            int tmp = joueur;
            joueurs = Joueurs::getInstance();
            joueurCourant = joueurs->getJoueur(0);

            // Ajoute des joueurs
            try {
                while(tmp > 2) {
                    joueurs->ajouterJoueur();
                    tmp--;
                }
            } catch(JoueurException& e) {}
        }

        /*! \brief Destructeur de Jeu */
        ~Jeu();

        /*! \brief Gere le deroulement d'une partie */
        void partie();

    private:

        /*!
            \brief Place une certaine Tuile sur le plateau
            \param[in] emplIdx Indice de l'emplacement (des coordonnees) ou la Tuile doit etre placee
        */
        void placerTuile(int emplIdx) {
            plateau.poserTuile(emplacementJouables[emplIdx]);
            joueurCourant->incrementScore(1);
        }

        /*! \brief Passe au joueur suivant */
        void nextJoueur() {
            joueurCourant = joueurs->getJoueur((joueurCourant->getNumero() + 1) % joueurs->getNbJoueurs());
        }

        /*! \brief Recupere les emplacements ou la tuile courante peut etre posee */
        void recupEmplacementsJouables() {
            emplacementJouables = plateau.getEmplacementsOuPeutPoser();
        }

        /*! \brief Recupere l'indice du joueur gagnant */
        int getJoueurGagnant() const {
            int idxJoueurScoreMax = -1, scoreMax = -1;
            // Parcours tous les joueurs
            for(int idxJoueur = 0; idxJoueur < joueurs->getNbJoueurs(); idxJoueur++) {
                // Si le score du joueur courant est meilleur, c'est ce dernier qui est le meilleur joueur
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
