/*! \file Route.h
    \version 0.1
*/

#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "Symbols.h"
#include "Chemin.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Route
        \brief Represente une Route
    */
    class Route : public Chemin {
    private :
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant une Route
        */
        Route(Tuile* premiereTuile):Chemin(premiereTuile){}

        /*! \brief Destructeur de la classe */
        ~Route()=default;

        /*! \brief Donne le caractere representant une Route
            \return Le caractere correspodant a une Route
        */
        const char& toChar() const override {
            return C_ROUTE;
        }
    };
}

#endif
