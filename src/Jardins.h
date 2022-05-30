/*! \file Jardins.h
    \version 0.1
*/

#ifndef __JARDINS_H__
#define __JARDINS_H__

#include "Jardin.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Jardins
        \brief Gere la memoire des tous les Jardins presents dans le jeu
    */
    class Jardins {
    private:

        /*! \struct Handler
            \brief Encapsule le Singleton de Abbayes
        */
        struct Handler {
            Jardins* instance; /*!< Instance de Jardins (Singleton) */

            /*! \brief Cree une nouvelle instance du Singleton
                \param[in] Pointeur sur l'objet Jardins Singleton
            */
            Handler(Jardins* ptr) { instance = ptr; }

            /*! \brief Detruit le Singleton a la fin de l'application */
            ~Handler() { delete instance; }
        };

        static Handler handler; /*!< Instance Singleton statique de Abbayes */

        list<Jardin*> listeJardin; /*!< Liste des Jardins presents dans la partie */

        /*! \brief Constructeur de la classe */
        Jardins()=default;

        /*! \brief Destructeur de la classe */
        ~Jardins(){
            for(Jardin* jardin : listeJardin)
                delete jardin;
        }

    public:

        /*! \brief Recupere l'instance du Singleton */
        static Jardins* getInstance() {
            // Si le Singleton n'a pas ete defini avant, on cree une nouvelle instance
            if(handler.instance == nullptr) {
                handler.instance = new Jardins();
            }

            return handler.instance;
        }

        /*! \brief Libere l'instance du Singleton */
        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

        /*! \brief Cree un nouveau Jardin
            \param[in] premiereTuile Tuile sur laquelle se trouve un Jardin
            \return Le Jardin cree
        */
        Jardin* creerJardin(Tuile* premiereTuile) {
            Jardin* newJardin=new Jardin(premiereTuile);
            listeJardin.push_back(newJardin);
            return newJardin;
        }
    };
}

#endif
