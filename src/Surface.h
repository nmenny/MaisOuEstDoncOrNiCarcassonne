#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "Tuile.h"
#include <list>

using namespace std;

namespace Carcassonne {
    class Surface {
    protected :
        list<Tuile*> listeTuiles;
    public :
        Surface(Tuile* premiereTuile){
            listeTuiles.push_back(premiereTuile);
        }
        virtual ~Surface()=default;
        virtual void ajouterTuile(Tuile* tuile) = 0;
        int getTaille(){return listeTuiles.size();}
        list<Tuile*>& getTuiles(){return listeTuiles;}
    };
}

#endif