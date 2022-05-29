#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "Chemin.h"

namespace Carcassonne {
    class Route : public Chemin {
    private :
    public :
        Route(Tuile* premiereTuile):Chemin(premiereTuile){}
        virtual void ajouterTuile(Tuile* tuile){
            listeTuiles.push_back(tuile);
        }
    };
}

#endif