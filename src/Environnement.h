/*! \file Environnement.h
    \version 0.1
*/

#ifndef __ENVIRONNEMENT_H__
#define __ENVIRONNEMENT_H__

#include <list>

#include "Tuile.h"
#include "Personnages.h"


/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Environnement
        \brief Represente le concept general des elements pouvant se trouver sur une Tuile
    */
    class Environnement {
    protected :
        list<Tuile*> listeTuiles; /*!< Liste contenant toutes les tuiles contenant un même environnement */
        list<Meeple*> listeMeeples; /*!< Liste contenant les meeples presents dans un environnement */
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant une structure
        */
        Environnement(Tuile* premiereTuile){
            listeTuiles.push_back(premiereTuile);
        }
        /*! \brief Destructeur de la classe */
        virtual ~Environnement()=default;

        /*! \brief Connecte une tuile a un environnement
            \param[in] tuile Tuile a connecter a l'environnement courant
        */
        virtual void ajouterTuile(Tuile* tuile) = 0;

        /*! \brief Renvoie le caractere representant un type d'environnement
            \return Le caractere representant l'environnement
        */
        virtual const char& toChar() const = 0;

        /*! \brief Renvoie le nombre de Tuiles regroupant ce même element d'environnement
            \return Le nombre de Tuiles regroupant ce même element d'environnement
        */
        int getTaille(){return listeTuiles.size();}

        /*! \brief Renvoie la liste des Tuiles regroupant ce même element d'environnement
            \return Le liste des Tuiles regroupant ce même element d'environnement
        */
        list<Tuile*> getTuiles(){return listeTuiles;}
    };

}

#endif
