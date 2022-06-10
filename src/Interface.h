/*! \file Interface.h
    \version 0.1
*/

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <string>

#include "Plateau.h"
#include "Joueur.h"
#include "Joueurs.h"
#include "Tuile.h"
#include "Coordonnee.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    enum class InterfaceError {indiceIncorrect};

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

        /*!
            \brief Affiche un message d'erreur
            \param[in] err Le type d'erreur
            \param[in] msg Le message d'erreur
                <optionnel>
        */
        virtual void afficheMessageErreur(const InterfaceError& err, const std::string& msg = "")=0;

        // Acquisitions

        /*! \brief Demande a l'utilisateur l'action qu'il souhaite realiser
            \return Une chaine de caracteres reprensantant l'action a effectuer, peut etre soit :
                - un nombre : indice de la position ou poser la Tuile
                - "d" / "g" : demande de faire une rotation de la Tuile a droite / gauche
                - "r" : demande de repiocher une nouvelle Tuile
        */
        virtual std::string demanderAction()=0;

        /*! \brief Demande a l'utilisateur s'il souhaite attribuer des points aux joueurs
            \param[in,out] j Les joueurs participant a la partie
        */
        virtual void demanderPointsAAttribuer(Joueurs& j)=0;

        /*! \brief Demande a l'utilisateur s'il souhaite poser un meeple sur la tuile qui vient d'être posee sur le plateau et
                sur quel environnement il veut le poser
            \param[in] c Les coordonnees que le jeu propose pour poser les Meeples (Coordonees par rapport a la tuile)
            \return L'indice dans les coordonnees ou le joueur veut poser le meeple, ou -1 s'il ne souhaite pas en poser
        */
        virtual int demanderPoserMeeples(const Coordonnees& c)=0;

    };

}

#endif // __INTERFACE_H__
