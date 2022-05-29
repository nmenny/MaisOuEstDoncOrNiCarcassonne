#ifndef __ABBAYE_H__
#define __ABBAYE_H__

#include "Batiment.h"

namespace Carcassonne {
    class Abbaye : public Batiment {
    private :

    public :
        Abbaye(Tuile* premiereTuile):Batiment(premiereTuile){}
        virtual void ajouterTuile(Tuile* tuile){
            listeTuiles.push_back(tuile);
        }
    };
}

#endif // __ABBAYE_H__
