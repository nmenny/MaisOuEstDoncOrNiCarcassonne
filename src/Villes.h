#ifndef __VILLES_H__
#define __VILLES_H__

#include "Ville.h"

namespace Carcassonne {
    class Villes {
    private :

        struct Handler {
            Villes* instance;
            Handler(Villes* ptr) { instance = ptr; }
            ~Handler() { delete instance; }
        };

        Villes()=default;

        ~Villes(){
            for(Ville* ville : listeVilles)
                delete ville;
        }

        static Handler handler;

        list<Ville*> listeVilles;
    public :

        static Villes* getInstance() {
            if(handler.instance == nullptr) {
                handler.instance = new Villes();
            }
            return handler.instance;
        }

        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

        Ville* creerVille(Tuile* premiereTuile) {
            Ville* newVille=new Ville(premiereTuile);
            listeVilles.push_back(newVille);
            return newVille;
        }
        Ville* fusionnerVilles(Ville* villeOriginale, Ville* villeAAjouter) {
            list<Tuile*> tuilesAChanger=villeAAjouter->getTuiles();
            for(Tuile* tuile : tuilesAChanger){
                villeOriginale->ajouterTuile(tuile);
            }
            //Suppression de villeAAjouter
            listeVilles.remove(villeAAjouter);
            delete villeAAjouter;
            return villeOriginale;
        }
    };
}

#endif
