/*! \file Riviere.h
    \version 0.1
*/

#ifndef __RIVIERE_H__
#define __RIVIERE_H__

#include "Symbols.h"
#include "Chemin.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Pre
        \brief Represente une Riviere
    */
    class Riviere : public Chemin {
    private :
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant une Riviere
        */
        Riviere(Tuile* premiereTuile):Chemin(premiereTuile){}

        /*! \brief Destructeur de la classe */
        ~Riviere()=default;

        /*! \brief Donne le caractere representant une Riviere
            \return Le caractere correspodant a une Riviere
        */
        const char& toChar() const override {
            return C_RIVIERE;
        }

        /*!
            \brief Connecte la riviere courante a une autre
            \param[in] env L'environnement que l'on connecte
            \warning env peut etre desalloue a la fin de l'appel a la methode
            \return L'element courant apres connection
        */
        Riviere* connect(Environnement* env) override {
            if(env == this) {
                return this;
            }

            return GestionnaireMemoireEnvironnement<Riviere>::getInstance()->fusionner(this, dynamic_cast<Riviere*>(env));
        }
    };
}

#endif
