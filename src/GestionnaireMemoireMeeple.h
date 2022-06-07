/*! \file GestionnaireMemoireMeeple.h
    \version 0.1
*/

#ifndef __GESTIONNAIREMEMOIREMEEPLE_H__
#define __GESTIONNAIREMEMOIREMEEPLE_H__

#include <vector>
#include "Joueur.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    using namespace std;

    /*! \class GestionnaireMemoireMeeple
        \brief Represente le concept general de Gestionnaire memoire des Meeples
        \tparam T Type de Meeple que doit gérer le Gestionnaire mémoire
    */
    template<class T>
    class GestionnaireMemoireMeeple {
    protected :

        /*! \struct Handler
            \brief Encapsule le Singleton de Gestionnaire memoire
        */
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

        static Handler handler; /*!< Instance Singleton statique de Gestionnaire memoire */

        vector<T*> listeMeeples; /*!< Liste des Meeples geres pas le Gestionnaire */
    public :

        /*!
            \brief Recupere l'instance du Singleton
            \return L'unique instance du Gestionnaire Memoire
        */
        static GestionnaireMemoireMeeple<T>* getInstance() {
            if(handler.instance == nullptr) {
                handler.instance = new GestionnaireMemoireMeeple<T>();
            }
            return handler.instance;
        }

        /*! \brief Libere l'instance du Singleton */
        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

        /*!
            \brief Donne le nombre de Meeples geres par le gestionnaire
            \return Le nombre de Meeples geres par le gestionnaire
        */
        virtual size_t getNbMeeplesEnMemoire() const { return listeMeeples.size(); }

        /*!
            \brief Cree un nouveau Meeple et le donne a un Joueur
            \param[in] j Le joueur proprietaire du nouveau Meeple
            \return Le nouveau Meeple
        */
        virtual T* ajoutMeeple(Joueur* j) {
            listeMeeples.push_back(new T(j));
            return listeMeeples[listeMeeples.size()-1];
        }

    };

    template<class T>
    typename GestionnaireMemoireMeeple<T>::Handler GestionnaireMemoireMeeple<T>::handler(nullptr);

}

#endif // __GESTIONNAIREMEMOIREMEEPLE_H__
