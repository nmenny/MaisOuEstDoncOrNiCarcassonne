/*! \file Batiment.h
    \version 0.1
*/

#ifndef __BATIMENT_H__
#define __BATIMENT_H__

#include "Environnement.h"

using namespace std;

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Batiment
        \brief Represente le concept general de Batiment

        Un Batiment est un element d'environnement qui ne se trouve qu'a un seul emplacement sur la Tuile
    */
    class Batiment : public Environnement {
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant un Batiment
        */
        Batiment(Tuile* premiereTuile) : Environnement(premiereTuile) {}

        /*! \brief Destructeur de la classe */
        ~Batiment()=default;
    };
}

#endif
