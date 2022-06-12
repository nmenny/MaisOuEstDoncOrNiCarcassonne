/*! \file Plateau.h
    \version 0.1
*/

#ifndef __PLATEAU_H__
#define __PLATEAU_H__

#include <iostream>
#include <array>
#include <vector>

#include "Extensions.h"
#include "Personnages.h"
#include "Coordonnee.h"
#include "Pioche.h"
#include "CarcassonneException.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    class JeuConsole;

    using namespace std;

    /*! \class Plateau
        \brief Plateau sur lequel les Tuiles sont disposees
    */
	class Plateau {

    public:

        static const int NB_LIGNES_MAX = 30; /*!< Nombre de lignes du plateau au maximum */
        static const int NB_COLONNES_MAX = 30; /*!< Nombre de colonnes du plateau au maximum */

	private:

        Pioche pioche; /*!< La pioche */

        Tuile* tuileCourante = nullptr; /*!< Tuile qui doit etre jouee */

        array<array<const Tuile*, NB_COLONNES_MAX>, NB_LIGNES_MAX> plateau; /*!< Tableaux representant le plateau */

        Coordonnees emplacementsVidesJouables; /*!< Liste des coordonnees des emplacements vides jouables */

        friend class JeuConsole;

        std::vector<extensions> ext;

	public:

        /*!
            \brief Constructeur de la classe

            Pose automatiquement une tuile au centre du plateau
        */
        Plateau(std::vector<extensions> extensionListe) : pioche(extensionListe), ext(extensionListe) {
            initPlateau();
            nextTuile();
            poserTuile(Coordonnee(NB_COLONNES_MAX / 2, NB_LIGNES_MAX / 2));
            nextTuile();
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
        const Tuile* getTuile() const {
            return tuileCourante;
        }

        void nextTuile() {
            tuileCourante = pioche.piocher();
        }

        void tournerTuileDroite() {
            if(tuileCourante == nullptr) {
                throw TuileException("Ne peut pas faire tourner une tuile vide !!");
            }
            tuileCourante->rotation(directionRotation::droite);
        }

        void tournerTuileGauche() {
            if(tuileCourante == nullptr) {
                throw TuileException("Ne peut pas faire tourner une tuile vide !!");
            }
            tuileCourante->rotation(directionRotation::gauche);
        }

        /*!
            \brief Recupere une ligne entiere du plateau
            \param[in] y Numero de ligne a recuperer (0 : haut du plateau)
            \return Reference sur la ligne du plateau
        */
        const array<const Tuile*, NB_COLONNES_MAX>& getLigneDeTuiles(size_t y) const {
            if(y >= NB_LIGNES_MAX) {
                throw PlateauException("Erreur, tente de recuperer une ligne qui est hors du plateau !");
            }
            return plateau[y];
        }

        /*!
            \brief Remet la Tuile courante dans la pioche
        */
        void remettreTuile() {
            tuileCourante = pioche.repiocher();
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
        Coordonnees getEmplacementsOuPeutPoser();

        Coordonnees getEmplacementOuPeutPoserMeeple(const Coordonnee& coordTuile) const;

        /*!
            \brief Pose la tuile courante a des coordonnees specifiques
            \param[in] c Coordonnee ou la Tuile va etre posee
            \return Pointeur sur la tuile posee
        */
        const Tuile* poserTuile(const Coordonnee& c);

        const Meeple* poserMeeple(Meeple* m, Environnement* env);

    private:


        /*!
            \brief Recupere la tuile a poser
            \return Pointeur sur la tuile a poser
        */
        Tuile* p_getTuile() const {
            return tuileCourante;
        }

        /*!
            \brief Calcule les emplacements vides autour d'une Tuile placee a des coordonnes donnees
            \param[in] x Composante en x de la Tuile
            \param[in] y Composante en y de la Tuile
        */
        void getEmplacementsVidesAutourDeTuile(int x, int y);

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
