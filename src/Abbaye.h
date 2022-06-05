/*! \file Abbaye.h
    \version 0.1
*/

#ifndef __ABBAYE_H__
#define __ABBAYE_H__

#include "Symbols.h"
#include "Batiment.h"


/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Abbaye
        \brief Represente une Abbaye
    */
    class Abbaye : public Batiment {
    private :
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant une Abbaye
        */
        Abbaye(Tuile* premiereTuile):Batiment(premiereTuile){}

        /*! \brief Destructeur de la classe */
        ~Abbaye()=default;

        /*! \brief Donne le caractere representant une Abbaye
            \return Le caractere correspodant a une Abbaye
        */
        const char& toChar() const override {
            return C_ABBAYE;
        }
    };
}

#endif // __ABBAYE_H__
