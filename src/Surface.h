/*! \file Surface.h
    \version 0.1

    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "Batiment.h"
#include "Environnement.h"
#include "GestionnaireMemoireEnvironnement.h"
#include "Symbols.h"

using namespace std;

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Surface
        \brief Represente le concept general de Surface

        Une Surface est un element d'environnement particulier qui peut s'ettendre sur plusieurs Tuiles
    */
    class Surface : public Environnement {
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant une Surface
        */
        Surface(Tuile* premiereTuile) : Environnement(premiereTuile) {}

        /*! \brief Destructeur de la classe */
        ~Surface()=default;
    };


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
            if(tmp != nullptr) {
                return true;
            }
            return toChar() == envAdj->toChar();
        }

        virtual bool checkMeepleConstraint(const Environnement* env) const {
            const Pre* preVoisin = dynamic_cast<const Pre*>(env);
            if(preVoisin != nullptr) {
                return preVoisin->getNbMeeples() == 0;
            }
            return true;
        }
    };


    /*! \class Ville
        \brief Represente une Ville
    */
    class Ville : public Surface {
    private :
        bool aBouclier = false;
        bool aCathedrale = false;
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant une Ville
            \param[in] bouclier Indique la nouvelle ville comporte un bouclier ou non
                <Optionnel; Defaut = false>
        */
        Ville(Tuile* premiereTuile) : Surface(premiereTuile) {}

        /*! \brief Destructeur de la classe */
        ~Ville()=default;

        /*! \brief Donne le caractere representant une Ville
            \return Le caractere correspodant a une Ville
        */
        const char& toChar() const override {
            return C_VILLE;
        }

        /*! \brief Permet de rajouter une variante d'un certain environnement par exemple
         *  \param[in] option Option pour avoir une variante d'un certain environnement tres proche d'un autre
            \return Le caractere representant l'environnement
        */
        void setOption(int option) override {
            switch(option) {
            case static_cast<int>(idTypesVilles::AVEC_BOUCLIER):
                aBouclier = true;
            case static_cast<int>(idTypesVilles::AVEC_CATHEDRALE):
                aCathedrale = true;
                break;
            case static_cast<int>(idTypesVilles::CLASSIQUE):
            default:
                return;
            }
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
            Ville* ptV = dynamic_cast<Ville*>(env);
            if(ptV == nullptr) {
                throw MemoireException("L'environnement que l'on souhaite connecter a une ville n'est pas une ville !");
            }
            if(ptV->aBouclier) {
                aBouclier = true;
            }
            if(ptV->aCathedrale) {
                aCathedrale = true;
            }

            return GestionnaireMemoireEnvironnement<Ville>::getInstance()->fusionner(this, dynamic_cast<Ville*>(env));
        }
    };
}

#endif
