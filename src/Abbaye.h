#ifndef __ABBAYE_H__
#define __ABBAYE_H__

#include "Symbols.h"
#include "Batiment.h"

namespace Carcassonne {
    class Abbaye : public Batiment {
    private :

    public :
        Abbaye(Tuile* premiereTuile):Batiment(premiereTuile){}

        void ajouterTuile(Tuile* tuile) override{
            listeTuiles.push_back(tuile);
        }

        const char& toChar() const override {
            return C_ABBAYE;
        }
    };
}

#endif // __ABBAYE_H__
