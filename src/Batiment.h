#ifndef __BATIMENT_H__
#define __BATIMENT_H__

#include "Tuile.h"
#include <list>

using namespace std;

namespace Carcassonne {

    class Tuile;

    class Batiment {
    protected :
        list<Tuile*> listeTuiles;
    public :
        Batiment(Tuile* premiereTuile){
            listeTuiles.push_back(premiereTuile);
        }
        virtual ~Batiment()=default;
        virtual void ajouterTuile(Tuile* tuile) = 0;
        int getTaille(){return listeTuiles.size();}
        list<Tuile*> getTuiles(){return listeTuiles;}
    };
}

#endif
