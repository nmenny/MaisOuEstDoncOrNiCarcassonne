#ifndef __CHEMIN_H__
#define __CHEMIN_H__

#include "Environnement.h"

using namespace std;

namespace Carcassonne {

    class Chemin : public Environnement {
    public :
        Chemin(Tuile* premiereTuile) : Environnement(premiereTuile) {}
        ~Chemin()=default;
    };
}

#endif
