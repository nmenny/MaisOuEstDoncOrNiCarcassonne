#ifndef __VILLE_H__
#define __VILLE_H__

#include "Surface.h"

namespace Carcassonne {
    class Ville : public Surface {
    private :

    public :
        Ville(Tuile* premiereTuile):Surface(premiereTuile){}
        virtual void ajouterTuile(Tuile* tuile){
            listeTuiles.push_back(tuile);
        }
    };
}

#endif
