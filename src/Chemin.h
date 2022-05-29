#ifndef __CHEMIN_H__
#define __CHEMIN_H__

#include "Tuile.h"
#include <list>

using namespace std;

namespace Carcassonne {

    class Tuile;

    class Chemin {
    protected :
        list<Tuile*> listeTuiles;
    public :
        Chemin(Tuile* premiereTuile){
            listeTuiles.push_back(premiereTuile);
        }
        ~Chemin(){}
        virtual void ajouterTuile(Tuile* tuile) = 0;
        int getTaille(){return listeTuiles.size();}
        list<Tuile*> getTuiles(){return listeTuiles;}
    };
}

#endif