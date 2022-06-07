/*! \file Environnement.h
    \version 0.1
*/

#ifndef __ENVIRONNEMENT_H__
#define __ENVIRONNEMENT_H__

#include <list>

#include "Tuile.h"
#include "Personnages.h"
#include "CarcassonneException.h"


/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Environnement
        \brief Represente le concept general des elements pouvant se trouver sur une Tuile
    */
    class Environnement {
    protected :
        list<const Tuile*> listeTuiles; /*!< Liste contenant toutes les tuiles contenant un même environnement */
        list<Meeple*> listeMeeples; /*!< Liste contenant les meeples presents dans un environnement */
    public :

        /*! \brief Constructeur de la classe
            \param[in] premiereTuile Tuile contenant une structure
        */
        Environnement(const Tuile* premiereTuile){
            listeTuiles.push_back(premiereTuile);
        }
        /*! \brief Destructeur de la classe */
        virtual ~Environnement()=default;

        /*! \brief Renvoie le nombre de Meeples presents sur cet environnement
            \return Le nombre de Meeples presents sur cet environnement
        */
        int getNbTuiles(){ return listeTuiles.size(); }

        /*! \brief Renvoie le nombre de Tuiles regroupant ce même element d'environnement
            \return Le nombre de Tuiles regroupant ce même element d'environnement
        */
        int getNbMeeples(){ return listeMeeples.size(); }

        /*! \brief Renvoie la liste des Tuiles regroupant ce même element d'environnement
            \return Le liste des Tuiles regroupant ce même element d'environnement
        */
        list<const Tuile*> getTuiles(){ return listeTuiles; }

        /*! \brief Connecte une tuile a un environnement
            \param[in] tuile Tuile a connecter a l'environnement courant
        */
        virtual void ajouterTuile(const Tuile* tuile) {
            listeTuiles.push_back(tuile);
        }

        /*! \brief Pose un meeple sur un environnement
            \param[in,out] m Le meeple a poser
        */
        virtual void poserMeeple(Meeple* m) {
            m->misEnJeu();
            listeMeeples.push_back(m);
        }

        /*! \brief Retire un Meeple de cet environnement
            \return Le meeple retire
        */
        virtual Meeple* retirerMeeple() {
            if(listeMeeples.size() == 0) {
                throw TuileException("Erreur, il n'y a pas de meeple sur cet environnement !");
            }

            Meeple* m = listeMeeples.front();
            listeMeeples.pop_front();

            return m;
        }

        /*! \brief Renvoie le caractere representant un type d'environnement
            \return Le caractere representant l'environnement
        */
        virtual const char& toChar() const = 0;
    };

}

#endif
