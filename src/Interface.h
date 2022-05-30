/*! \file Interface.h
    \version 0.1
*/

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <string>
#include <iostream>
#include <vector>

#include "Plateau.h"
#include "Joueur.h"
#include "Joueurs.h"
#include "Tuile.h"
#include "Coordonnee.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Interface
        \brief Classe Interface reprensentant une Interface Utilisateur
    */
    class Interface {
    public:

        /*! \brief Constructeur de la classe */
        Interface()=default;

        /*! \brief Destructeur de la classe */
        virtual ~Interface()=default;

        // Affichages

        /*! \brief Affiche a l'utilisateur les emplacements ou il peut poser une Tuile
            \param[in] c La liste des coordonnees ou des Tuiles peuvent etre posees
        */
        virtual void afficheEmplacementsJouables(const Coordonnees& c)=0;

        /*! \brief Affiche le score
            \param[in] j Les joueurs participant a la partie
        */
        virtual void afficheScore(const Joueurs& j)=0;

        /*! \brief Affiche les donnees liees a un joueur
            \param[in] j Le joueur a afficher
        */
        virtual void afficheJoueur(const Joueur& j)=0;

        /*! \brief Affiche a l'utilisateur la Tuile courante
            \param[in] t La tuile a afficher
        */
        virtual void afficheTuileCourante(const Tuile& t)=0;

        /*! \brief Affiche le plateau a l'utilisateur
            \param[in] p Le plateau a afficher
        */
        virtual void affichePlateau(const Plateau& p)=0;

        /*! \brief Affiche un message signalant la fin de la partie */
        virtual void afficheFinPartie()=0;

        /*! \brief Affiche le gagnant
            \param[in] idxJoueur Indice du joueur gagnant
        */
        virtual void afficheGagnant(const int idxJoueur)=0;

        // Acquisitions

        /*! \brief Demande a l'utilisateur ou il souhaite poser une Tuile
            \param[in] c La liste des coordonnees ou des Tuiles peuvent etre posees
            \return L'indice de l'action a effectuer
        */
        virtual int demanderOuPoser(const Coordonnees& c)=0;

        /*! \brief Demande a l'utilisateur s'il souhaite attribuer des points aux joueurs
            \param[in,out] j Les joueurs participant a la partie
        */
        virtual void demanderPointsAAttribuer(Joueurs& j)=0;

    };


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

        int demanderOuPoser(const Coordonnees& c) override {
            streamOut << "\nOu souhaitez-vous poser la tuile ?\n";

            int saisie = -1;

            // Tant que l'utilisateur ne rentre pas une action viable, il doit refaire la saisie
            while(true) {
               try {
                    streamIn >> saisie;
               } catch(...) {}

               if(saisie >= 0 && saisie < c.size()) {
                  break;
               }

               streamOut << "La valeur rentree n'est pas correcte, recommencez... (on attend l'indice du coup que vous jouez)\n";

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

#endif // __INTERFACE_H__
