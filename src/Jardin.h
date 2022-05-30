/*! \file Jardin.h
    \version 0.1
*/

#ifndef __JARDIN_H__
#define __JARDIN_H__

#include "Symbols.h"
#include "Batiment.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Jardin
        \brief Represente un Jardin
    */
    class Jardin : public Batiment {
    private :

    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant un Jardin
        */
        Jardin(Tuile* premiereTuile):Batiment(premiereTuile){}

        /*! \brief Ajoute une nouvelle Tuile possedant un Jardin
            \param[in] tuile La tuile possedant un Jardin
        */
        void ajouterTuile(Tuile* tuile) override {
            listeTuiles.push_back(tuile);
        }

        /*! \brief Donne le caractere representant un Jardin
            \return Le caractere correspodant a un Jardin
        */
        const char& toChar() const override {
            return C_JARDIN;
        }
    };
}

#endif // __JARDIN_H__
