/*! \file EnvironnementFactory.h
    \version 0.1
*/

#ifndef __ENVIRONNEMENTFACTORY_H__
#define __ENVIRONNEMENTFACTORY_H__

#include "Symbols.h"
#include "types.h"
#include "Tuile.h"
#include "Environnement.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class EnvironnementFactory
        \brief Usine pour construire des nouveaux environnements
        \note Quand on ajoute un nouvel environnement, on doit ajouter un champ dans la methode
    */
    class EnvironnementFactory {
    public:

        /*!
            \brief Cree un nouvel environnement
            \param[in,out] t Tuile a laquelle l'environnement doit etre ajoutee
            \param[in] c Caractere symbolisant l'environnement
            \return Un pointeur sur le nouvel environnement cree
        */
        static Environnement* createNouvEnvironnement(Tuile* t, const char& c) {
            // Selon le caractere, une structure differente est allouee
            switch(c) {
            case C_PRES:
                return Pres::getInstance()->creer(t);break;
            case C_VILLE:
                return Villes::getInstance()->creer(t);break;
            case C_ABBAYE:
                return Abbayes::getInstance()->creer(t);break;
            case C_JARDIN:
                return Jardins::getInstance()->creer(t);break;
            case C_ROUTE:
                return Routes::getInstance()->creer(t);break;
            case C_RIVIERE:
                return Rivieres::getInstance()->creer(t);break;
            default:
                return nullptr;
            }
        }
    };

}

#endif // __ENVIRONNEMENTFACTORY_H__
