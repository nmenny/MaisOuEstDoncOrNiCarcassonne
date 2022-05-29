#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "Environnement.h"

using namespace std;

namespace Carcassonne {

    class Surface : public Environnement {
    public :
        Surface(Tuile* premiereTuile) : Environnement(premiereTuile) {}
        ~Surface()=default;
    };
}

#endif
