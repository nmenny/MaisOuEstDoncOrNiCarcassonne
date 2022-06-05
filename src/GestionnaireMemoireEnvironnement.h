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

namespace Carcassonne {

    using namespace std;

    template<class T>
    class GestionnaireMemoireEnvironnement {

    protected :

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

        static Handler handler;

        list<T*> listeEnv;
    public :

        static GestionnaireMemoireEnvironnement<T>* getInstance() {
            if(handler.instance == nullptr) {
                handler.instance = new GestionnaireMemoireEnvironnement<T>();
            }
            return handler.instance;
        }

        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

        virtual size_t getNbEnvEnMemoire() const { return listeEnv.size(); }

        virtual T* creer(Tuile* premiereTuile) {
            T* newEnv=new T(premiereTuile);
            listeEnv.push_back(newEnv);
            return newEnv;
        }

        virtual T* fusionner(T* envOriginal, T* envAFusionner) {
            list<Tuile*> tuilesAChanger=envAFusionner->getTuiles();
            for(Tuile* tuile : tuilesAChanger){
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
