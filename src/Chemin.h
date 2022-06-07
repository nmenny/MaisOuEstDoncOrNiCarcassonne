/*! \file Chemin.h
    \version 0.1
*/

#ifndef __CHEMIN_H__
#define __CHEMIN_H__

#include "Environnement.h"

using namespace std;

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Chemin
        \brief Represente le concept general de Chemin

        Un Chemin est un element d'environnement particulier qui traverse les differentes tuiles et
         peut connecter des Batiments ou Surfaces entre-eux
    */
    class Chemin : public Environnement {
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant un Chemin
        */
        Chemin(Tuile* premiereTuile) : Environnement(premiereTuile) {}

        /*! \brief Destructeur de la classe */
        ~Chemin()=default;

    };
}

#endif
