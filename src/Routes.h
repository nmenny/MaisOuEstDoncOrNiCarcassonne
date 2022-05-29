#ifndef __ROUTES_H__
#define __ROUTES_H__

#include "Route.h"

namespace Carcassonne {
    class Routes {
    private :

        struct Handler {
            Routes* instance;
            Handler(Routes* ptr) { instance = ptr; }
            ~Handler() { delete instance; }
        };

        Routes()=default;

        ~Routes(){
            for(Route* route : listeRoutes)
                delete route;
        }

        static Handler handler;

        list<Route*> listeRoutes;
    public :

        static Routes* getInstance() {
            if(handler.instance == nullptr) {
                handler.instance = new Routes();
            }
            return handler.instance;
        }

        static void libererInstance() {
            delete handler.instance;
            handler.instance = nullptr;
        }

        Route* creerRoute(Tuile* premiereTuile) {
            Route* newRoute=new Route(premiereTuile);
            listeRoutes.push_back(newRoute);
            return newRoute;
        }
        Route* fusionnerRoutes(Route* routeOriginale, Route* routeAAjouter) {
            list<Tuile*> tuilesAChanger=routeAAjouter->getTuiles();
            int nbTuilesAChanger=routeAAjouter->getTaille();
            for(Tuile* tuile : tuilesAChanger){
                routeOriginale->ajouterTuile(tuile);
            }

            listeRoutes.remove(routeAAjouter);
            delete routeAAjouter;
            return routeOriginale;
        }
    };
}


#endif
