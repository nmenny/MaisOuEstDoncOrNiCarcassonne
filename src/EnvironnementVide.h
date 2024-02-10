/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef ENVIRONNEMENTVIDE_H
#define ENVIRONNEMENTVIDE_H

#define UNUSED(x) (void)x

#include "Environnement.h"
#include "Symbols.h"

namespace Carcassonne {

    class EnvironnementVide : public Environnement {

    public:

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant un coin
        */
        EnvironnementVide(Tuile* premiereTuile) : Environnement(premiereTuile) {}

        /*! \brief Destructeur de la classe */
        ~EnvironnementVide()=default;

        /*! \brief Renvoie le caractere representant un type d'environnement
            \return Le caractere representant l'environnement
        */
        const char& toChar() const {
            return C_COIN;
        }

        /*!
           \brief Connecte l'environnement courant a un autre
           \param[in] env L'environnement que l'on connecte
           \warning env peut etre desalloue a la fin de l'appel a la methode
           \return L'element courant apres connection
           \note Aucune connection n'est faite
       */
        virtual Environnement* connect(Environnement* env) {
            UNUSED(env);
            return this;
        }

        bool peutPoserMeeple() const override {
            return false;
        }

    };

}

#endif // ENVIRONNEMENTVIDE_H
