/*! \file Pres.h
    \version 0.1
*/

#ifndef __PRES_H__
#define __PRES_H__

#include "Pre.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Pres
        \brief Gere la memoire des tous les Pres presents dans le jeu
    */
    class Pres {
    private:

        /*! \struct Handler
            \brief Encapsule le Singleton de Abbayes
        */
        struct Handler {
            Pres* instance; /*!< Instance de Pres (Singleton) */

            /*! \brief Cree une nouvelle instance du Singleton
                \param[in] Pointeur sur l'objet Pres Singleton
            */
            Handler(Pres* ptr) { instance = ptr; }

            /*! \brief Detruit le Singleton a la fin de l'application */
            ~Handler() { delete instance; }
        };

        static Handler handler; /*!< Instance Singleton statique de Abbayes */

        list<Pre*> listePres; /*!< Liste des Pres presents dans la partie */

        /*! \brief Constructeur de la classe */
        Pres()=default;

        /*! \brief Destructeur de la classe */
        ~Pres(){
            for(Pre* pre : listePres)
                delete pre;
        }

    public:

        /*! \brief Recupere l'instance du Singleton */
        static Pres* getInstance() {
            // Si le Singleton n'a pas ete defini avant, on cree une nouvelle instance
            if(handler.instance == nullptr) {
                handler.instance = new Pres();
            }

            return handler.instance;
        }

        /*! \brief Libere l'instance du Singleton */
        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

         /*! \brief Cree un nouveau Pre
            \param[in] premiereTuile Tuile sur laquelle se trouve un Pre
            \return Le Pre cree
        */
        Pre* creerPre(Tuile* premiereTuile) {
            Pre* newPre=new Pre(premiereTuile);
            listePres.push_back(newPre);
            return newPre;
        }

         /*! \brief Fusionne deux pres
            \param[in,out] preOriginale Pre que l'on fusionne
            \param[in,out] preAAjouter Pre a fusionner
            \return Le Pre fusionne
        */
        Pre* fusionnerPres(Pre* preOriginale, Pre* preAAjouter) {
            list<Tuile*> tuilesAChanger=preAAjouter->getTuiles();
            for(Tuile* tuile : tuilesAChanger){
                preOriginale->ajouterTuile(tuile);
            }

            listePres.remove(preAAjouter);
            delete preAAjouter;
            return preOriginale;
        }
    };
}

#endif
