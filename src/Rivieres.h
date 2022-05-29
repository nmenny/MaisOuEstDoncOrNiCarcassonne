#ifndef __RIVIERES_H__
#define __RIVIERES_H__

#include "Riviere.h"

namespace Carcassonne {
    class Rivieres {
    private :

        struct Handler {
            Rivieres* instance;
            Handler(Rivieres* ptr) { instance = ptr; }
            ~Handler() { delete instance; }
        };

        static Handler handler;

        list<Riviere*> listeRivieres;


        Rivieres()=default;

        ~Rivieres(){
            for(Riviere* riviere : listeRivieres)
                delete riviere;
        }

    public :

        static Rivieres* getInstance() {
            if(handler.instance == nullptr) {
                handler.instance = new Rivieres();
            }
            return handler.instance;
        }

        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

        Riviere* creerRiviere(Tuile* premiereTuile) {
            Riviere* newRiviere=new Riviere(premiereTuile);
            listeRivieres.push_back(newRiviere);
            return newRiviere;
        }
        Riviere* fusionnerRivieres(Riviere* riviereOriginale, Riviere* riviereAAjouter) {
            list<Tuile*> tuilesAChanger=riviereAAjouter->getTuiles();
            for(Tuile* tuile : tuilesAChanger){
                riviereOriginale->ajouterTuile(tuile);
            }

            listeRivieres.remove(riviereAAjouter);
            delete riviereAAjouter;
            return riviereOriginale;
        }
    };
}

#endif
