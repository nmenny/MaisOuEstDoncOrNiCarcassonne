#ifndef __PLATEAU_H__
#define __PLATEAU_H__

#include <iostream>
#include <vector>

#include "Coordonnee.h"
#include "Pioche.h"
#include "CarcassonneException.h"

namespace Carcassonne {

    using namespace std;

	class Plateau {

	private:

        Pioche pioche;

        const Tuile* tuileCourante = nullptr;

        vector<vector<const Tuile*>> plateau;

        int nbLignes = 0;
        int nbColonnes = 0;

	public:

        Plateau() {
            tuileCourante = pioche.piocher();
            vector<const Tuile*> v;
            v.push_back(tuileCourante);
            plateau.push_back(v);
            nbLignes++;
            nbColonnes++;
            tuileCourante = pioche.piocher();
        };

        ~Plateau()=default;

        const Pioche& getPioche() const {
            return pioche;
        }

        const Tuile* getTuile() const {
            return tuileCourante;
        }

        bool isEmpty() const { return tuileCourante == nullptr; }

        void affiche(ostream& f) const;

        vector<Coordonnee> getEmplacementsOuPeutPoser() const;

        const Tuile* poserTuile(const Coordonnee& c);

    private:



	};

}

#endif
