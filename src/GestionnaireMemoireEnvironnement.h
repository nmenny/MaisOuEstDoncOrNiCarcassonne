/*! \file GestionnaireMemoireEnvironnement.h
    \version 0.1

    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef __GESTIONNAIREMEMOIREENVIRONNEMENT_H__
#define __GESTIONNAIREMEMOIREENVIRONNEMENT_H__

#include <iostream>
#include <list>

#include "Tuile.h"
#include "CarcassonneException.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    using namespace std;

    /*! \class GestionnaireMemoireEnvironnement
        \brief Represente le concept general de Gestionnaire memoire des environnements
        \tparam T Type de l'environnement que doit gerer le Gestionnaire memoire
    */
    template<class T>
    class GestionnaireMemoireEnvironnement {

    protected :

        /*! \struct Handler
            \brief Encapsule le Singleton de Gestionnaire memoire
        */
        struct Handler {
            GestionnaireMemoireEnvironnement<T>* instance;
            Handler(GestionnaireMemoireEnvironnement<T>* ptr) { instance = ptr; }
            ~Handler() { delete instance; }
        };

        GestionnaireMemoireEnvironnement()=default;

        virtual ~GestionnaireMemoireEnvironnement(){
            for(T* env : listeEnv)
                delete env;
        }

        GestionnaireMemoireEnvironnement<T>& operator=(const GestionnaireMemoireEnvironnement<T>&)=delete;

        static Handler handler; /*!< Instance Singleton statique de Gestionnaire memoire */

        list<T*> listeEnv; /*!< Liste des environnements geres pas le Gestionnaire */

    public :

        /*!
            \brief Recupere l'instance du Singleton
            \return L'unique instance du Gestionnaire Memoire
        */
        static GestionnaireMemoireEnvironnement<T>* getInstance() {
            if(handler.instance == nullptr) {
                handler.instance = new GestionnaireMemoireEnvironnement<T>();
            }
            return handler.instance;
        }

        /*! \brief Libere l'instance du Singleton */
        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

        /*!
            \brief Donne le nombre d'environnements geres par le gestionnaire
            \return Le nombre d'environnements geres par le gestionnaire
        */
        virtual size_t getNbEnvEnMemoire() const { return listeEnv.size(); }

        /*!
            \brief Cree un nouvel environnement
            \param[in] premiereTuile La premiere Tuile sur laquelle est present ce nouvel environnement
            \return L'environnement cree
        */
        virtual T* creer(Tuile* premiereTuile) {
            T* newEnv = newEnv=new T(premiereTuile);

            listeEnv.push_back(newEnv);
            return newEnv;
        }

        /*!
            \brief Fusionne deux environnements
            \param[in,out] envOriginal Le premier environnement a fusionner, sera modifie
            \param[in,out] envAFusionner Le deuxieme environnement a fusionner, sera distancie a la fin de l'appel
            \return L'environnement fusionne
        */
        virtual T* fusionner(T* envOriginal, T* envAFusionner) {
            if(envAFusionner == nullptr || envOriginal == nullptr) {
                throw MemoireException("Erreur, essaie de fusionner des Tuiles incompatibles / indefinies !");
            }

            if(envOriginal == envAFusionner) {
                return envOriginal;
            }

            list<const Tuile*> tuilesAChanger=envAFusionner->getTuiles();
            for(const Tuile* tuile : tuilesAChanger){
                envOriginal->ajouterTuile(tuile);
            }
            //Suppression de envAFusionner
            listeEnv.remove(envAFusionner);
            delete envAFusionner;
            return envOriginal;
        }

    };

    template<class T>
    typename GestionnaireMemoireEnvironnement<T>::Handler GestionnaireMemoireEnvironnement<T>::handler(nullptr);
}

#endif // __GESTIONNAIREMEMOIREENVIRONNEMENT_H__
