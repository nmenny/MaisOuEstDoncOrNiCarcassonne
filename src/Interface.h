/*! \file Interface.h
    \version 0.1
*/

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

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
            \return L'indice de l'action a effectuer
        */
        virtual size_t demanderOuPoser()=0;

        /*! \brief Demande a l'utilisateur s'il souhaite attribuer des points aux joueurs
            \param[in,out] j Les joueurs participant a la partie
        */
        virtual void demanderPointsAAttribuer(Joueurs& j)=0;

    };

}

#endif // __INTERFACE_H__
