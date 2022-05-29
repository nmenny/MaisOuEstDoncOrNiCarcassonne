#ifndef __BATIMENT_H__
#define __BATIMENT_H__

#include "Environnement.h"

using namespace std;

namespace Carcassonne {

    class Batiment : public Environnement {
    public :
        Batiment(Tuile* premiereTuile) : Environnement(premiereTuile) {}
        ~Batiment()=default;
    };
}

#endif
