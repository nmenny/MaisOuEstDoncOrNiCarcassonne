#ifndef __ENVIRONNEMENT_H__
#define __ENVIRONNEMENT_H__

#include "Tuile.h"
#include <list>

namespace Carcassonne {

    class Environnement {
    protected :
        list<Tuile*> listeTuiles;
    public :
        Environnement(Tuile* premiereTuile){
            listeTuiles.push_back(premiereTuile);
        }
        virtual ~Environnement()=default;
        virtual void ajouterTuile(Tuile* tuile) = 0;
        virtual const char& toChar() const = 0;
        int getTaille(){return listeTuiles.size();}
        list<Tuile*> getTuiles(){return listeTuiles;}
    };

}

#endif
