#ifndef __PRES_H__
#define __PRES_H__

#include "Pre.h"

namespace Carcassonne {
    class Pres {
    private:

        struct Handler { 
            Pres* instance;
            Handler(Pres* ptr) { instance = ptr; }
            ~Handler() { delete instance; }
        };

        static Handler handler;

        list<Pre*> listePres;



        Pres()=default;

        ~Pres(){
            for(Pre* pre : listePres)
                delete pre;
        }
        
    public:

        static Pres* getInstance() {
            if(handler.instance == nullptr) {
                handler.instance = new Pres();
            }

            return handler.instance;
        }

        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }
        
        Pre* creerPre(Tuile* premiereTuile) {
            Pre* newPre=new Pre(premiereTuile);
            listePres.push_back(newPre);
            return newPre;
        }


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