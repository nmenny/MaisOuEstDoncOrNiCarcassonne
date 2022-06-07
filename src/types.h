/*! \file types.h
    \version 0.1
    \brief Tous les types de gestion de memoire
    \note Quand on ajoute un nouveau Meeple ou un nouvel environnement, il faut ajouter un type
*/

#ifndef __TYPES_H__
#define __TYPES_H__

#include "GestionnaireMemoireMeeple.h"
#include "Personnages.h"

#include "GestionnaireMemoireEnvironnement.h"
#include "Pre.h"
#include "Ville.h"
#include "Route.h"
#include "Riviere.h"
#include "Abbaye.h"
#include "Jardin.h"


/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*!
        \brief Gere la memoire des tous les Pres presents dans le jeu
    */
    using Pres = GestionnaireMemoireEnvironnement<Pre>;

    /*!
        \brief Gere la memoire des toutes les villes presentes dans le jeu
    */
    using Villes = GestionnaireMemoireEnvironnement<Ville>;

    /*!
        \brief Gere la memoire des toutes les Abbayes presentes dans le jeu
    */
    using Abbayes = GestionnaireMemoireEnvironnement<Abbaye>;

    /*!
        \brief Gere la memoire des tous les jardins presents dans le jeu
    */
    using Jardins = GestionnaireMemoireEnvironnement<Jardin>;

    /*!
        \brief Gere la memoire des toutes les rivieres presentes dans le jeu
    */
    using Rivieres = GestionnaireMemoireEnvironnement<Riviere>;

    /*!
        \brief Gere la memoire des toutes les routes presentes dans le jeu
    */
    using Routes = GestionnaireMemoireEnvironnement<Route>;



    /*!
        \brief Gere la memoire des tous les Meeples Basiques du jeu
    */
    using BasicMeeples = GestionnaireMemoireMeeple<BasicMeeple>;

    /*!
        \brief Gere la memoire des tous les Grand Meeples du jeu
    */
    using GdMeeples = GestionnaireMemoireMeeple<GdMeeple>;

    /*!
        \brief Gere la memoire des tous les abbes du jeu
    */
    using Abbes = GestionnaireMemoireMeeple<Abbe>;

}

#endif // __TYPES_H__
