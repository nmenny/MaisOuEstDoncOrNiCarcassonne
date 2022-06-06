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

        static const int NB_LIGNES_MAX = 5; /*!< Nombre de lignes du plateau au maximum */
        static const int NB_COLONNES_MAX = 5; /*!< Nombre de colonnes du plateau au maximum */

	private:

        Pioche pioche; /*!< La pioche */

        Tuile* tuileCourante = nullptr; /*!< Tuile qui doit etre jouee */

        array<array<const Tuile*, NB_COLONNES_MAX>, NB_LIGNES_MAX> plateau; /*!< Tableaux representant le plateau */

	public:

        /*!
            \brief Constructeur de la classe

            Pose automatiquement une tuile au centre du plateau
        */
        Plateau() {
            initPlateau();
            tuileCourante = pioche.piocher();
            poserTuile(Coordonnee(NB_COLONNES_MAX / 2, NB_LIGNES_MAX / 2));
        };

        /*! \brief Destructeur de la classe */
        ~Plateau()=default;

        /*!
            \brief Recupere la pioche
            \return La pioche
        */
        const Pioche& getPioche() const {
            return pioche;
        }

        /*!
            \brief Recupere la tuile a poser
            \return Pointeur sur la tuile a poser
        */
        Tuile* getTuile() const {
            return tuileCourante;
        }

        /*!
            \brief Indique s'il est possible de jouer (s'il reste des Tuiles dans la pioche)
            \return <tt>true</tt> Si l'on peut poser une Tuile, <tt>false</tt> sinon
        */
        bool peutJouerDesTuiles() const { return tuileCourante != nullptr; }

        /*!
            \brief Affiche le plateau dans un stream
            \param[in,out] f Stream dans lequel est affiche le plateau
        */
        void affiche(ostream& f) const;

        /*!
            \brief Recupere les emplacements ou l'on peut jouer la tuile courante
            \return Liste des coordonnees ou une Tuile peut etre posee
        */
        Coordonnees getEmplacementsOuPeutPoser() const;

        /*!
            \brief Pose la tuile courante a des coordonnees specifiques
            \param[in] c Coordonnee ou la Tuile va etre posee
            \return Pointeur sur la tuile posee
        */
        const Tuile* poserTuile(const Coordonnee& c);

    private:

        /*!
            \brief Initialise le plateau avec des Tuiles vides
        */
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
