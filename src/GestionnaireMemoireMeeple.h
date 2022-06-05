#ifndef __GESTIONNAIREMEMOIREMEEPLE_H__
#define __GESTIONNAIREMEMOIREMEEPLE_H__

#include <vector>

#include "Personnages.h"

namespace Carcassonne {

    using namespace std;

    template<class T>
    class GestionnaireMemoireMeeple {
    protected :

        struct Handler {
            GestionnaireMemoireMeeple<T>* instance;
            Handler(GestionnaireMemoireMeeple<T>* ptr) { instance = ptr; }
            ~Handler() { delete instance; }
        };

        GestionnaireMemoireMeeple()=default;

        virtual ~GestionnaireMemoireMeeple(){
            for(T* meeple : listeMeeples)
                delete meeple;
        }

        GestionnaireMemoireMeeple<T>& operator=(const GestionnaireMemoireMeeple<T>&)=delete;

        static Handler handler;

        vector<T*> listeMeeples;
    public :

        static GestionnaireMemoireMeeple<T>* getInstance() {
            if(handler.instance == nullptr) {
                handler.instance = new GestionnaireMemoireMeeple<T>();
            }
            return handler.instance;
        }

        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

        virtual size_t getNbEnv() const { return listeMeeples.size(); }

        virtual T* ajoutMeeple(Joueur* j) {
            listeMeeples.push_back(new T(j));
            return listeMeeples[listeMeeples.size()-1];
        }

    };

    template<class T>
    typename GestionnaireMemoireMeeple<T>::Handler GestionnaireMemoireMeeple<T>::handler(nullptr);


    /*!
        \brief Gere la memoire des tous les Meeples Basiques du jeu
    */
    using BasicMeeples = GestionnaireMemoireEnvironnement<BasicMeeple>;

    /*!
        \brief Gere la memoire des tous les Grand Meeples du jeu
    */
    using GdMeeples = GestionnaireMemoireEnvironnement<GdMeeple>;

    /*!
        \brief Gere la memoire des tous les abbes du jeu
    */
    using Abbes = GestionnaireMemoireEnvironnement<Abbe>;

}

#endif // __GESTIONNAIREMEMOIREMEEPLE_H__
