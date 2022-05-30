/*! \file Plateau.h
    \version 0.1
*/

// TODO : Regler gros soucis dans getEmplacementsOuPeutPoser() !!!!!
// TODO : Pousser les tests de poserTuile()

#ifndef __PLATEAU_H__
#define __PLATEAU_H__

#include <iostream>
#include <vector>

#include "Coordonnee.h"
#include "Pioche.h"
#include "CarcassonneException.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    using namespace std;

    /*! \class Plateau
        \brief Plateau sur lequel les Tuiles sont disposees
    */
	class Plateau {

	private:

        Pioche pioche; /*!< La pioche */

        const Tuile* tuileCourante = nullptr; /*!< Tuile qui doit etre jouee */

        vector<vector<const Tuile*>> plateau; /*!< Vecteurs representant le plateau */

        int nbLignes = 0; /*!< Nb de lignes du plateau */
        int nbColonnes = 0; /*!< Nb de colonnes du plateau */

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

        Coordonnees getEmplacementsOuPeutPoser() const;

        const Tuile* poserTuile(const Coordonnee& c);

    private:

	};

}

#endif
