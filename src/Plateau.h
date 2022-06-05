/*! \file Plateau.h
    \version 0.1
*/

#ifndef __PLATEAU_H__
#define __PLATEAU_H__

#include <iostream>
#include <array>

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

    public:

        static const int NB_LIGNES_MAX = 5;
        static const int NB_COLONNES_MAX = 5;

	private:

        Pioche pioche; /*!< La pioche */

        Tuile* tuileCourante = nullptr; /*!< Tuile qui doit etre jouee */

        array<array<const Tuile*, NB_COLONNES_MAX>, NB_LIGNES_MAX> plateau; /*!< Vecteurs representant le plateau */

        int nbLignes = 0; /*!< Nb de lignes du plateau */
        int nbColonnes = 0; /*!< Nb de colonnes du plateau */

	public:

        Plateau() {
            initPlateau();
            tuileCourante = pioche.piocher();
            poserTuile(Coordonnee(NB_COLONNES_MAX / 2, NB_LIGNES_MAX / 2));
        };

        ~Plateau()=default;

        const Pioche& getPioche() const {
            return pioche;
        }

        Tuile* getTuile() const {
            return tuileCourante;
        }

        bool isEmpty() const { return tuileCourante == nullptr; }

        void affiche(ostream& f) const;

        Coordonnees getEmplacementsOuPeutPoser() const;

        const Tuile* poserTuile(const Coordonnee& c);

    private:

        void initPlateau() {
            for(size_t idxLigne = 0; idxLigne < NB_LIGNES_MAX; idxLigne++) {
                for(size_t idxCol = 0; idxCol < NB_COLONNES_MAX; idxCol++) {
                    plateau[idxLigne][idxCol] = nullptr;
                }
            }
        }

	};

}

#endif
