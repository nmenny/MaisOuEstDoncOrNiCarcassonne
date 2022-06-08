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

        /*! \brief Affiche a l'utilisateur les emplacements ou il peut poser une Tuile
            \param[in] c La liste des coordonnees ou des Tuiles peuvent etre posees
        */
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

        /*! \brief Affiche les donnees liees a un joueur
            \param[in] j Le joueur a afficher
        */
        void afficheJoueur(const Joueur& j) override {
            streamOut << "\n-- C'est au tour du joueur " << (j.getNumero() + 1) << " de jouer...\n";
        }

        /*! \brief Affiche a l'utilisateur la Tuile courante
            \param[in] t La tuile a afficher
        */
        void afficheTuileCourante(const Tuile& t) override {
            streamOut << "Voici la tuile a jouer ce tour la :\n";

            t.affiche(streamOut);
        }

        /*! \brief Affiche le plateau a l'utilisateur
            \param[in] p Le plateau a afficher
        */
        void affichePlateau(const Plateau& p) override {
            streamOut << "-- Etat du plateau actuel --\n";

            p.affiche(streamOut);
        }

        /*! \brief Affiche un message signalant la fin de la partie */
        void afficheFinPartie() override {
            streamOut << "\n\n **** Fin de la partie ****\n\n";
        }

        /*! \brief Affiche le gagnant
            \param[in] idxJoueur Indice du joueur gagnant
        */
        void afficheGagnant(const int idxJoueur) override {
            streamOut << "\n*** Felication au joueur " << (idxJoueur+1) << "!!! \n";
        }

        /*!
            \brief Affiche un message d'erreur
            \param[in] err Le type d'erreur
            \param[in] msg Le message d'erreur
                <optionnel>
        */
        void afficheMessageErreur(const InterfaceError& err, const std::string& msg = "") {
            switch(err) {
            case InterfaceError::indiceIncorrect:
                streamOut << "L'indice donne n'est pas correct ! " << msg << "\n";
                break;
            default:
                streamOut << "Erreur generale : " << msg << "\n";
            }
        }

        /*! \brief Affiche le score
            \param[in] j Les joueurs participant a la partie
        */
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

        /*! \brief Demande a l'utilisateur l'action qu'il souhaite realiser
            \return Une chaine de caracteres reprensantant l'action a effectuer, peut etre soit :
                - un nombre : indice de la position ou poser la Tuile
                - "d" / "g" : demande de faire une rotation de la Tuile a droite / gauche
                - "r" : demande de repiocher une nouvelle Tuile
        */
        std::string demanderAction() override {
           streamOut << "\nQue souhaitez-vous faire ?\n";

           std::string saisie;

            streamIn >> saisie;

            return saisie;
        }


        /*! \brief Demande a l'utilisateur s'il souhaite attribuer des points aux joueurs
            \param[in,out] j Les joueurs participant a la partie
        */
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
