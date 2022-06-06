/*! \file InterfaceConsole.h
    \version 0.1
*/

#ifndef __INTERFACECONSOLE_H__
#define __INTERFACECONSOLE_H__

#include <string>
#include <iostream>

#include "Interface.h"
#include "CarcassonneException.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class InterfaceConsole
        \brief Interface console pour l'application
    */
    class InterfaceConsole : public Interface {

        std::ostream& streamOut; /*!< stream de sortie */
        std::istream& streamIn; /*!< stream d'entree */

    public:

        /*! \brief Constructeur de la classe
            \param[in] st Stream de sortie
                <Default: std::cout>
            \param[in] sti Stream de saisie
                <Default: std::cin>
        */
        InterfaceConsole(std::ostream& st=std::cout, std::istream& sti=std::cin) : streamOut(st), streamIn(sti) {};

        /*! \brief Destructeur de la classe */
        ~InterfaceConsole()=default;

        void afficheEmplacementsJouables(const Coordonnees& c) override {
            streamOut << "\nVoici les coups jouables:\n";
            streamOut << "idxCoup => (x ; y)\n";
            // Parcours tous les emplacements jouables
            for(size_t emplacementIdx = 0; emplacementIdx < c.size(); emplacementIdx++) {
                // Affiche chaque action possible
                streamOut << emplacementIdx << " => ";
                c[emplacementIdx].affiche(streamOut);
            }
        }

        void afficheJoueur(const Joueur& j) override {
            streamOut << "\n-- C'est au tour du joueur " << (j.getNumero() + 1) << " de jouer...\n";
        }

        void afficheTuileCourante(const Tuile& t) override {
            streamOut << "Voici la tuile a jouer ce tour la :\n";

            t.affiche(streamOut);
        }

        void affichePlateau(const Plateau& p) override {
            streamOut << "-- Etat du plateau actuel --\n";

            p.affiche(streamOut);
        }

        void afficheFinPartie() override {
            streamOut << "\n\n **** Fin de la partie ****\n\n";
        }

        void afficheGagnant(const int idxJoueur) override {
            streamOut << "\n*** Felication au joueur " << (idxJoueur+1) << "!!! \n";
        }


        void afficheScore(const Joueurs& j) override {
            streamOut << "| Joueurs | Points |\n";
            // Parcours l'ensemble des joueurs
            for(int idxJoueur = 0; idxJoueur < j.getNbJoueurs(); idxJoueur++) {
                streamOut << "|    " << idxJoueur << "    |";
                // Calcul la longueur (en nombre de caracteres) du score
                int lgScore = to_string(j.getJoueur(idxJoueur)->getScore()).size();

                // Affiche suffisament d'espace pour preserver le formattage
                for(; lgScore < 8; lgScore++) {
                    streamOut << " ";
                }

                // Affiche le score
                streamOut << j.getJoueur(idxJoueur)->getScore() << "|\n";
            }
        }

        size_t demanderOuPoser() override {
           streamOut << "\nOu souhaitez-vous poser la tuile ?\n";

           size_t saisie = 0;

           try {
                streamIn >> saisie;
           } catch(...) {
                streamOut << "La valeur rentree n'est pas correcte, recommencez... (on attend l'indice du coup que vous jouez)\n";
                throw InterfaceException("Valeur saisie incorrecte !");
           }

            return saisie;
        }


        void demanderPointsAAttribuer(Joueurs& j) override {
            streamOut << "\nY'a-t'il encore des points a attribuer ?(Y/N)\n";

            char c;

            streamIn >> c;

            if(c == 'Y' || c == 'y') {
                int pts;
                // Parcours tous les joueurs
                for(int idxJoueur = 0; idxJoueur < j.getNbJoueurs(); idxJoueur++) {
                    // Demande, pour chaque joueur, la valeur d'increment du score
                    streamOut << "Points pour le joueur " << (idxJoueur + 1) << ":\n";
                    streamIn >> pts;
                    j.getJoueur(idxJoueur)->incrementScore(pts);
                }
            }
        }

    };

}

#endif // __INTERFACECONSOLE_H__
