#ifndef __RIVIERE_H__
#define __RIVIERE_H__

#include "Chemin.h"

namespace Carcassonne {
    class Riviere : public Chemin {
    private :
    public :
        Riviere(Tuile* premiereTuile):Chemin(premiereTuile){}
        virtual void ajouterTuile(Tuile* tuile){
            listeTuiles.push_back(tuile);
        }
    };
}

#endif