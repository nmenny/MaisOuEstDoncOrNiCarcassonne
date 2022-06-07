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

        /*! \brief Destructeur de la classe */
        ~Ville()=default;

        /*! \brief Donne le caractere representant une Ville
            \return Le caractere correspodant a une Ville
        */
        const char& toChar() const override {
            return C_VILLE;
        }

        /*!
            \brief Connecte la ville courante a une autre
            \param[in] env L'environnement que l'on connecte
            \warning env peut etre desalloue a la fin de l'appel a la methode
            \return L'element courant apres connection
        */
        Ville* connect(Environnement* env) override {
            if(env == this) {
                return this;
            }

            return GestionnaireMemoireEnvironnement<Ville>::getInstance()->fusionner(this, dynamic_cast<Ville*>(env));
        }
    };
}

#endif
