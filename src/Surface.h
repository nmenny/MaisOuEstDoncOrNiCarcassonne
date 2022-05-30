/*! \file Surface.h
    \version 0.1
*/

#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "Environnement.h"

using namespace std;

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Surface
        \brief Represente le concept general de Surface

        Une Surface est un element d'environnement particulier qui peut s'ettendre sur plusieurs Tuiles
    */
    class Surface : public Environnement {
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant une Surface
        */
        Surface(Tuile* premiereTuile) : Environnement(premiereTuile) {}

        /*! \brief Destructeur de la classe */
        ~Surface()=default;
    };
}

#endif
