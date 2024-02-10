/*! \file Environnement.h
    \version 0.1

    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef __ENVIRONNEMENT_H__
#define __ENVIRONNEMENT_H__

#include <list>

#include "Personnages.h"
#include "CarcassonneException.h"


/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    class Tuile;

    /*! \class Environnement
        \brief Represente le concept general des elements pouvant se trouver sur une Tuile
    */
    class Environnement {
    protected :
        list<const Tuile*> listeTuiles; /*!< Liste contenant toutes les tuiles contenant un même environnement */
        Meeple* meeple = nullptr; /*!< Liste contenant les meeples presents dans un environnement */
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
        int getNbTuiles() const { return listeTuiles.size(); }

        /*! \brief Renvoie le nombre de Tuiles regroupant ce même element d'environnement
            \return Le nombre de Tuiles regroupant ce même element d'environnement
        */
        int getNbMeeples() const {
            if(meeple != nullptr) {
                return 1;
            } else {
                return 0;
            }
        }

        Meeple* getMeeple() const {
            return meeple;
        }

        /*! \brief Renvoie la liste des Tuiles regroupant ce même element d'environnement
            \return Le liste des Tuiles regroupant ce même element d'environnement
        */
        list<const Tuile*> getTuiles() const { return listeTuiles; }

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
            if(meeple == nullptr) {
                m->misEnJeu();
                meeple = m;
            }
        }

        /*! \brief Retire un Meeple de cet environnement
            \return Le meeple retire
        */
        virtual Meeple* retirerMeeple() {
            if(meeple == nullptr) {
                throw TuileException("Erreur, il n'y a pas de meeple sur cet environnement !");
            }

            Meeple* m = meeple;
            meeple = nullptr;

            return m;
        }

        /*! \brief Renvoie le caractere representant un type d'environnement
            \return Le caractere representant l'environnement
        */
        virtual const char& toChar() const = 0;

        /*! \brief Permet de rajouter une variante d'un certain environnement par exemple
         *  \param[in] option Option pour avoir une variante d'un certain environnement tres proche d'un autre
            \return Le caractere representant l'environnement
        */
        virtual void setOption(int option) { return; }


        virtual bool peutPoserMeeple() const {
            return true;
        }

        virtual bool checkMeepleConstraint(const Environnement* env) const {
            return true;
        }

        /*! \brief Inidique si deux environnements sont similaires
         *  \param[in] env L'environnement a comparer
            \return <tt>true</tt> Si les enrivonnements sont similaires, <tt>false</tt> sinon
        */
        virtual bool sontSimilaires(const Environnement* env) const {
            return toChar() == env->toChar();
        }

         /*!
            \brief Connecte l'environnement courant a un autre
            \param[in] env L'environnement que l'on connecte
            \warning env peut etre desalloue a la fin de l'appel a la methode
            \return L'element courant apres connection
        */
        virtual Environnement* connect(Environnement* env)=0;

        /*!
            \brief Indique si l'environnement courant peut etre adjacent a un autre
            \param[in] envAdj Environnement adjacent dont on veut verifier la possibilite
            \return <tt>true</tt> si l'environnement courant peut etre adjacent a envAdj, <tt>false</tt> sinon
            \note Par defaut, seul des environnements identiques peuvent etre adjacents
        */
        virtual bool peutEtreAdjacentA(const Environnement* envAdj) {
            return sontSimilaires(envAdj);
        }
    };

}

#endif
