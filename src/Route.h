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

        /*!
            \brief Connecte la route courante a une autre
            \param[in] env L'environnement que l'on connecte
            \warning env peut etre desalloue a la fin de l'appel a la methode
            \return L'element courant apres connection
        */
        Route* connect(Environnement* env) override {
            if(env == this) {
                return this;
            }

            return GestionnaireMemoireEnvironnement<Route>::getInstance()->fusionner(this, dynamic_cast<Route*>(env));
        }
    };
}

#endif
