/*! \file Pre.h
    \version 0.1
*/

#ifndef __PRE_H_
#define __PRE_H_

#include "Symbols.h"
#include "Surface.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Pre
        \brief Represente un Pre
    */
    class Pre : public Surface {
    private :
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant un Pre
        */
        Pre(Tuile* premiereTuile):Surface(premiereTuile){}

        /*! \brief Destructeur de la classe */
        ~Pre()=default;

        /*! \brief Donne le caractere representant un Pre
            \return Le caractere correspodant a un Pre
        */
        const char& toChar() const override {
            return C_PRES;
        }
    };
}

#endif
