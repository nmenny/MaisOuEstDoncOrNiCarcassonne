/*! \file Pre.h
    \version 0.1
*/

#ifndef __PRE_H_
#define __PRE_H_

#include "GestionnaireMemoireEnvironnement.h"
#include "Symbols.h"
#include "Surface.h"
#include "Batiment.h"

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

        /*!
            \brief Connecte le pre courant a un autre
            \param[in] env L'environnement que l'on connecte
            \warning env peut etre desalloue a la fin de l'appel a la methode
            \return L'element courant apres connection
        */
        Pre* connect(Environnement* env) override {
            if(env == this) {
                return this;
            }

            return GestionnaireMemoireEnvironnement<Pre>::getInstance()->fusionner(this, dynamic_cast<Pre*>(env));
        }


        /*!
            \brief Indique si le pre courant peut etre adjacent a un autre
            \param[in] envAdj Environnement adjacent dont on veut verifier la possibilite
            \return <tt>true</tt> si le batiment courant peut etre adjacent a envAdj, <tt>false</tt> sinon
            \note Un pre peut etre adjacent a un environnement de meme type ou un batiment
        */
        bool peutEtreAdjacentA(const Environnement* envAdj) override {
            const Batiment* tmp = dynamic_cast<const Batiment*>(envAdj);
            if(tmp == nullptr) {
                return toChar() == envAdj->toChar();
            }
            return true;
        }
    };
}

#endif
