#ifndef __VILLE_H__
#define __VILLE_H__

#include "Symbols.h"
#include "Surface.h"

namespace Carcassonne {
    class Ville : public Surface {
    private :

    public :
        Ville(Tuile* premiereTuile):Surface(premiereTuile){}

        void ajouterTuile(Tuile* tuile) override {
            listeTuiles.push_back(tuile);
        }

        const char& toChar() const override {
            return C_VILLE;
        }
    };
}

#endif
