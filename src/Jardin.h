#ifndef __JARDIN_H__
#define __JARDIN_H__

#include "Batiment.h"

namespace Carcassonne {
    class Jardin : public Batiment {
    private :

    public :
        Jardin(Tuile* premiereTuile):Batiment(premiereTuile){}
        virtual void ajouterTuile(Tuile* tuile){
            listeTuiles.push_back(tuile);
        }
    };
}

#endif // __JARDIN_H__
