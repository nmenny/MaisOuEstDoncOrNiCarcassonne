/*! \file Abbayes.h
    \version 0.1
*/

#ifndef __ABBAYES_H__
#define __ABBAYES_H__

#include "Abbaye.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Abbayes
        \brief Gere la memoire des toutes les abbayes presentes dans le jeu
    */
    class Abbayes {
    private:

        /*! \struct Handler
            \brief Encapsule le Singleton de Abbayes
        */
        struct Handler {
            Abbayes* instance; /*!< Instance de Abbayes (Singleton) */

            /*! \brief Cree une nouvelle instance du Singleton
                \param[in] Pointeur sur l'objet Abbayes Singleton
            */
            Handler(Abbayes* ptr) { instance = ptr; }

            /*! \brief Detruit le Singleton a la fin de l'application */
            ~Handler() { delete instance; }
        };

        static Handler handler; /*!< Instance Singleton statique de Abbayes */

        list<Abbaye*> listeAbbaye; /*!< Liste des Abbaye presentes dans la partie */

        /*! \brief Constructeur de la classe */
        Abbayes()=default;

        /*! \brief Destructeur de la classe */
        ~Abbayes(){
            for(Abbaye* abbaye : listeAbbaye)
                delete abbaye;
        }

    public:

        /*! \brief Recupere l'instance du Singleton */
        static Abbayes* getInstance() {
            // Si le Singleton n'a pas ete defini avant, on cree une nouvelle instance
            if(handler.instance == nullptr) {
                handler.instance = new Abbayes();
            }

            return handler.instance;
        }

        /*! \brief Libere l'instance du Singleton */
        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

        /*! \brief Cree une nouvelle Abbaye
            \param[in] premiereTuile Tuile sur laquelle se trouve une Abbaye
            \return L'abbaye creee
        */
        Abbaye* creerAbbaye(Tuile* premiereTuile) {
            Abbaye* newAbbaye=new Abbaye(premiereTuile);
            listeAbbaye.push_back(newAbbaye);
            return newAbbaye;
        }
    };
}

#endif
