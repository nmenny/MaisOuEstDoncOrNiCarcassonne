/*! \file Ville.h
    \version 0.1
*/

#ifndef __VILLE_H__
#define __VILLE_H__

#include "Symbols.h"
#include "Surface.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Ville
        \brief Represente une Ville
    */
    class Ville : public Surface {
    private :
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant une Ville
        */
        Ville(Tuile* premiereTuile):Surface(premiereTuile){}

        /*! \brief Ajoute une nouvelle Tuile possedant une Ville
            \param[in] tuile La tuile possedant une Ville
        */
        void ajouterTuile(Tuile* tuile) override {
            listeTuiles.push_back(tuile);
        }

        /*! \brief Donne le caractere representant une Ville
            \return Le caractere correspodant a une Ville
        */
        const char& toChar() const override {
            return C_VILLE;
        }
    };
}

#endif
