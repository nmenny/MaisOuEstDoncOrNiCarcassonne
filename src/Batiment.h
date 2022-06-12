/*! \file Batiment.h
    \version 0.1
*/

#ifndef __BATIMENT_H__
#define __BATIMENT_H__

#define UNUSED(x) (void)x

#include "Symbols.h"
#include "Environnement.h"

using namespace std;

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Batiment
        \brief Represente le concept general de Batiment

        Un Batiment est un element d'environnement qui ne se trouve qu'a un seul emplacement sur la Tuile
    */
    class Batiment : public Environnement {
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant un Batiment
        */
        Batiment(Tuile* premiereTuile) : Environnement(premiereTuile) {}

        /*! \brief Destructeur de la classe */
        ~Batiment()=default;

        /*!
            \brief Connecte le batiment courant a un autre
            \param[in] env L'environnement que l'on connecte
            \warning env peut etre desalloue a la fin de l'appel a la methode
            \return L'element courant apres connection
            \note Un batiment ne peut pas etre connecte a un autre
        */
        Batiment* connect(Environnement* env) override {
            UNUSED(env);
            return this;
        }

        /*!
            \brief Indique si le batiment courant peut etre adjacent a un autre
            \param[in] envAdj Environnement adjacent dont on veut verifier la possibilite
            \return <tt>true</tt> si le batiment courant peut etre adjacent a envAdj, <tt>false</tt> sinon
            \note Un batiment peut etre adjacent a n'importe quel autre environnement
        */
        bool peutEtreAdjacentA(const Environnement* envAdj) override {
            UNUSED(envAdj);
            return true;
        }
    };


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

        /*! \brief Destructeur de la classe */
        ~Jardin()=default;

        /*! \brief Donne le caractere representant un Jardin
            \return Le caractere correspodant a un Jardin
        */
        const char& toChar() const override {
            return C_JARDIN;
        }
    };


    /*! \class Auberge
        \brief Represente une Auberge
    */
    class Auberge : public Batiment {
    private :

    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant une Auberge
        */
        Auberge(Tuile* premiereTuile):Batiment(premiereTuile){}

        /*! \brief Destructeur de la classe */
        ~Auberge()=default;

        /*! \brief Donne le caractere representant une Auberge
            \return Le caractere correspodant a une Auberge
        */
        const char& toChar() const override {
            return C_AUBERGE;
        }
    };

}

#endif
