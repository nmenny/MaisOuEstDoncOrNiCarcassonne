/*! \file InterfaceConsole.h
    \version 0.1
*/

#ifndef __INTERFACECONSOLE_H__
#define __INTERFACECONSOLE_H__

#include <string>
#include <iostream>

#include "Coordonnee.h"
#include "Joueurs.h"
#include "Plateau.h"
#include "Tuile.h"
#include "types.h"
#include "CarcassonneException.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class InterfaceConsole
        \brief Interface console pour l'application
    */
    class InterfaceConsole {

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
        void afficheEmplacementsJouables(const Coordonnees& c);

        /*! \brief Affiche les donnees liees a un joueur
            \param[in] j Le joueur a afficher
        */
        void afficheJoueur(const Joueur& j) {
            streamOut << "\n-- C'est au tour du joueur " << (j.getNumero() + 1) << " de jouer...\n";
        }

        /*! \brief Affiche a l'utilisateur la Tuile courante
            \param[in] t La tuile a afficher
            \param[in] nbTuileRest Le nombre de Tuiles restantes dans la pioche
        */
        void afficheTuileCourante(const Tuile& t, size_t nbTuileRest) {
            streamOut << "Il reste " << nbTuileRest << " Tuiles\n";
            streamOut << "Voici la tuile a jouer ce tour la :\n";

            t.affiche(streamOut);
        }

        /*! \brief Affiche le plateau a l'utilisateur
            \param[in] p Le plateau a afficher
        */
        void affichePlateau(const Plateau& p) {
            streamOut << "-- Etat du plateau actuel --\n";

            p.affiche(streamOut);
        }

        /*! \brief Affiche un message signalant la fin de la partie */
        void afficheFinPartie() {
            streamOut << "\n\n **** Fin de la partie ****\n\n";
        }

        /*! \brief Affiche le gagnant
            \param[in] idxJoueur Indice du joueur gagnant
        */
        void afficheGagnant(const int idxJoueur) {
            streamOut << "\n*** Felication au joueur " << (idxJoueur+1) << "!!! \n";
        }

        /*!
            \brief Affiche un message d'erreur
            \param[in] err Le type d'erreur
            \param[in] msg Le message d'erreur
                <optionnel>
        */
        void afficheMessageErreur(const InterfaceError& err, const std::string& msg = "");

        /*! \brief Affiche le score
            \param[in] j Les joueurs participant a la partie
        */
        void afficheScore(const Joueurs& j);

        /*! \brief Demande a l'utilisateur l'action qu'il souhaite realiser
            \return Une chaine de caracteres reprensantant l'action a effectuer, peut etre soit :
                - un nombre : indice de la position ou poser la Tuile
                - COMMANDE_ROTATION_DROITE / COMMANDE_ROTATION_GAUCHE : demande de faire une rotation de la Tuile a droite / gauche
                - COMMANDE_REPIOCHER : demande de repiocher une nouvelle Tuile
        */
        std::string demanderAction();


        /*! \brief Demande a l'utilisateur s'il souhaite attribuer des points aux joueurs
            \param[in,out] j Les joueurs participant a la partie
        */
        void demanderPointsAAttribuer(Joueurs& j);

        /*! \brief Demande a l'utilisateur s'il souhaite poser un meeple sur la tuile qui vient d'être posee sur le plateau et
                sur quel environnement il veut le poser
            \param[in] c Les coordonnees que le jeu propose pour poser les Meeples (Coordonees par rapport a la tuile)
            \return L'indice dans les coordonnees ou le joueur veut poser le meeple, ou -1 s'il ne souhaite pas en poser
        */
        int demanderPoserMeeples(const Coordonnees& c);

    };

}

#endif // __INTERFACECONSOLE_H__
