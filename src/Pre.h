#ifndef __PRE_H_
#define __PRE_H_

#include "Symbols.h"
#include "Surface.h"

namespace Carcassonne {
    class Pre : public Surface {
    private :
    public :
        Pre(Tuile* premiereTuile):Surface(premiereTuile){}

        void ajouterTuile(Tuile* tuile) override {
            listeTuiles.push_back(tuile);
        }

        const char& toChar() const override {
            return C_PRES;
        }
    };
}

#endif
