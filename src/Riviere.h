#ifndef __RIVIERE_H__
#define __RIVIERE_H__

#include "Symbols.h"
#include "Chemin.h"

namespace Carcassonne {
    class Riviere : public Chemin {
    private :
    public :
        Riviere(Tuile* premiereTuile):Chemin(premiereTuile){}

        void ajouterTuile(Tuile* tuile) override {
            listeTuiles.push_back(tuile);
        }

        const char& toChar() const override {
            return C_RIVIERE;
        }
    };
}

#endif
