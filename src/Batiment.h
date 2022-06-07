/*! \file Batiment.h
    \version 0.1
*/

#ifndef __BATIMENT_H__
#define __BATIMENT_H__

#define UNUSED(x) (void)x

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

        /*!
            \brief Connecte le batiment courant a un autre
            \param[in] env L'environnement que l'on connecte
            \warning env peut etre desalloue a la fin de l'appel a la methode
            \note Un batiment ne peut pas etre connecte a un autre
            \return L'element courant apres connection
        */
        Batiment* connect(Environnement* env) override {
            UNUSED(env);
            return this;
        }
    };
}

#endif
