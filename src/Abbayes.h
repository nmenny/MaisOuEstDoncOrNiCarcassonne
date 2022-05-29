#ifndef __ABBAYES_H__
#define __ABBAYES_H__

#include "Abbaye.h"


namespace Carcassonne {
    class Abbayes {
    private:

        struct Handler {
            Abbayes* instance;
            Handler(Abbayes* ptr) { instance = ptr; }
            ~Handler() { delete instance; }
        };

        static Handler handler;

        list<Abbaye*> listeAbbaye;

        Abbayes()=default;

        ~Abbayes(){
            for(Abbaye* abbaye : listeAbbaye)
                delete abbaye;
        }

    public:

        static Abbayes* getInstance() {
            if(handler.instance == nullptr) {
                handler.instance = new Abbayes();
            }

            return handler.instance;
        }

        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

        Abbaye* creerAbbaye(Tuile* premiereTuile) {
            Abbaye* newAbbaye=new Abbaye(premiereTuile);
            listeAbbaye.push_back(newAbbaye);
            return newAbbaye;
        }
    };
}

#endif
