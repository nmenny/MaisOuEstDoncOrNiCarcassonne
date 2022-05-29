#ifndef __JARDIN_H__
#define __JARDIN_H__

#include "Symbols.h"
#include "Batiment.h"

namespace Carcassonne {
    class Jardin : public Batiment {
    private :

    public :
        Jardin(Tuile* premiereTuile):Batiment(premiereTuile){}

         void ajouterTuile(Tuile* tuile) override {
            listeTuiles.push_back(tuile);
        }

        const char& toChar() const override {
            return C_JARDIN;
        }
    };
}

#endif // __JARDIN_H__
