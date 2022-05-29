#ifndef __JARDINS_H__
#define __JARDINS_H__

#include "Jardin.h"

namespace Carcassonne {
    class Jardins {
    private:

        struct Handler {
            Jardins* instance;
            Handler(Jardins* ptr) { instance = ptr; }
            ~Handler() { delete instance; }
        };

        static Handler handler;

        list<Jardin*> listeJardin;



        Jardins()=default;

        ~Jardins(){
            for(Jardin* jardin : listeJardin)
                delete jardin;
        }

    public:

        static Jardins* getInstance() {
            if(handler.instance == nullptr) {
                handler.instance = new Jardins();
            }

            return handler.instance;
        }

        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

        Jardin* creerJardin(Tuile* premiereTuile) {
            Jardin* newJardin=new Jardin(premiereTuile);
            listeJardin.push_back(newJardin);
            return newJardin;
        }
    };
}

#endif
