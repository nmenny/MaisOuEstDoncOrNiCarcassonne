/*! \file Pioche.h
    \version 0.1
*/

#ifndef __PIOCHE_H__
#define __PIOCHE_H__

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Tuile.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Pioche
        \brief Represente la pioche
    */
	class Pioche {

	private:

		static const std::string TUILES_NOM_FICHIER; /*!< Nom du fichier contenant la definition des tuiles */

		vector<Tuile*> pioche; /*!< La liste des Tuiles en pioche */

		vector<Tuile*> piochees; /*!< La liste des Tuiles deja piochees */

	public:

        /*!
            \brief Constructeur de la classe

            Recupere toutes les Tuiles en memoire
        */
		Pioche() {
		    srand(time(NULL)); // Seed aleatoire
            recupereToutesLesTuiles();
		}

		Pioche(const Pioche& p)=delete;

		Pioche& operator=(const Pioche& p)=delete;

        /*! \brief Destructeur de la classe */
		~Pioche() {
			for(Tuile* t : pioche) {
				delete t;
			}
			for(Tuile* t : piochees) {
				delete t;
			}
		}

        /*!
            \brief Donne le nombre de Tuiles dans la pioche
            \return Le nombre de Tuiles dans la pioche
        */
		size_t getTaillePioche() const {
            return pioche.size();
		}

        /*!
            \brief Pioche une Tuile
            \return Pointeur sur la Tuile piochee, ou nullptr s'il n'y a plus de Tuile a piocher
        */
		Tuile* piocher() {
		    if(getTaillePioche() == 0) {
                return nullptr;
		    }

            // Pioche une Tuile aleatoirement
            size_t tuilePiocheIdx = rand() % getTaillePioche();

            auto itTuile = find(pioche.begin(), pioche.end(), pioche[tuilePiocheIdx]);

            // Ajoute la Tuile choisie a la pile des Tuiles piochees
            piochees.push_back(pioche[tuilePiocheIdx]);

            // Enleve la Tuile choisie de la pioche
            pioche.erase(itTuile);

            return piochees.back();

		}

        /*!
            \brief Repioche une Tuile
            \return Pointeur sur la Tuile piochee, ou nullptr s'il n'y a plus de Tuile a piocher
        */
		Tuile* repiocher() {
		    // Si la pioche n'a plus de Tuile, on renvoie la derniere Tuile piochee
		    if(getTaillePioche() == 0) {
                return piochees.back();
		    }

            Tuile* dernierePiochee = piochees.back();
            piochees.pop_back();

            Tuile* nouvellePiochee = piocher();

            pioche.push_back(dernierePiochee);

            return nouvellePiochee;
		}

	private:

        /*!
            \brief Recupere toutes les tuiles en memoire qui sont dans le fichier TUILES_NOM_FICHIER
        */
		void recupereToutesLesTuiles();

	};

}


#endif
