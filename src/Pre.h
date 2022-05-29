#ifndef __PRE_H_
#define __PRE_H_

#include "Surface.h"

namespace Carcassonne {
    class Pre : public Surface {
    private :
    public :
        Pre(Tuile* premiereTuile):Surface(premiereTuile){}
        virtual void ajouterTuile(Tuile* tuile){
            listeTuiles.push_back(tuile);
        }
    };
}

#endif