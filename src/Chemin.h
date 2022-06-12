/*! \file Chemin.h
    \version 0.1
*/

#ifndef __CHEMIN_H__
#define __CHEMIN_H__

#include "Environnement.h"
#include "GestionnaireMemoireEnvironnement.h"
#include "Symbols.h"

using namespace std;

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Chemin
        \brief Represente le concept general de Chemin

        Un Chemin est un element d'environnement particulier qui traverse les differentes tuiles et
         peut connecter des Batiments ou Surfaces entre-eux
    */
    class Chemin : public Environnement {
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant un Chemin
        */
        Chemin(Tuile* premiereTuile) : Environnement(premiereTuile) {}

        /*! \brief Destructeur de la classe */
        ~Chemin()=default;

    };


    /*! \class Riviere
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

        bool peutPoserMeeple() const override {
            return false;
        }
    };


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
