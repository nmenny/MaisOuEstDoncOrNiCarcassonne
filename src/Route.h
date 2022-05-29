#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "Symbols.h"
#include "Chemin.h"

namespace Carcassonne {
    class Route : public Chemin {
    private :
    public :
        Route(Tuile* premiereTuile):Chemin(premiereTuile){}

        void ajouterTuile(Tuile* tuile) override {
            listeTuiles.push_back(tuile);
        }

        const char& toChar() const override {
            return C_ROUTE;
        }
    };
}

#endif
