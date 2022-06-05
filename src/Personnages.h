#ifndef __PERSONNAGES_H__
#define __PERSONNAGES_H__

#include "Joueur.h"

namespace Carcassonne {

    class Meeple {
    private:
        bool enJeu;
        Joueur * joueur;

    public:
        Meeple(Joueur * j): enJeu(false), joueur(j){}

        virtual ~Meeple()=default;

        Joueur* getProprietaire() const {
            return joueur;
        }

        bool getEtat() const {
            return enJeu;
        }

        void misEnJeu() {
            enJeu = true;
        }

        void recuperer() {
            enJeu = false;
        }
    };


    class BasicMeeple : public Meeple{
    public:
        BasicMeeple(Joueur* j): Meeple(j){}
    };


    class GdMeeple : public Meeple{
    public:
        GdMeeple(Joueur* j): Meeple(j){}
    };


    class Abbe : public Meeple{
    public:
        Abbe(Joueur* j): Meeple(j) {}
    };
}

#endif
