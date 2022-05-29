#ifndef __COORDONNEE_H__
#define __COORDONNEE_H__

#include <iostream>

namespace Carcassonne {

    class Coordonnee {
    private:

        int x = 0;
        int y = 0;

    public:

        Coordonnee()=default;

        Coordonnee(int theX, int theY) : x(theX), y(theY) {}

        int getX() const { return x; }

        int getY() const { return y; }

        bool operator==(const Coordonnee& c2) const {
            return (c2.x == x) && (c2.y == y);
        }

        void affiche(std::ostream& f) const {
            f << "(" << x << " ; " << y << ")\n";
        }

    };

}

#endif
