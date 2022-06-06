/*! \file GestionnaireMemoireEnvironnement.h
    \version 0.1
*/

#ifndef __GESTIONNAIREMEMOIREENVIRONNEMENT_H__
#define __GESTIONNAIREMEMOIREENVIRONNEMENT_H__

#include <list>

#include "Tuile.h"
#include "Pre.h"
#include "Ville.h"
#include "Route.h"
#include "Riviere.h"
#include "Abbaye.h"
#include "Jardin.h"

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
            T* newEnv=new T(premiereTuile);
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


    /*!
        \brief Gere la memoire des tous les Pres presents dans le jeu
    */
    using Pres = GestionnaireMemoireEnvironnement<Pre>;

    /*!
        \brief Gere la memoire des toutes les villes presentes dans le jeu
    */
    using Villes = GestionnaireMemoireEnvironnement<Ville>;

    /*!
        \brief Gere la memoire des toutes les Abbayes presentes dans le jeu
    */
    using Abbayes = GestionnaireMemoireEnvironnement<Abbaye>;

    /*!
        \brief Gere la memoire des tous les jardins presents dans le jeu
    */
    using Jardins = GestionnaireMemoireEnvironnement<Jardin>;

    /*!
        \brief Gere la memoire des toutes les rivieres presentes dans le jeu
    */
    using Rivieres = GestionnaireMemoireEnvironnement<Riviere>;

    /*!
        \brief Gere la memoire des toutes les routes presentes dans le jeu
    */
    using Routes = GestionnaireMemoireEnvironnement<Route>;

}

#endif // __GESTIONNAIREMEMOIREENVIRONNEMENT_H__
