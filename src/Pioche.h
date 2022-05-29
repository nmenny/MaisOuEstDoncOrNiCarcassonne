#ifndef __PIOCHE_H__
#define __PIOCHE_H__

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Tuile.h"

namespace Carcassonne {

	class Pioche {

	private:

		static const std::string TUILES_NOM_FICHIER;

		vector<Tuile*> pioche;

		vector<Tuile*> piochees;

	public:

		Pioche() {
		    srand(time(NULL)); // Seed aleatoire
            recupereToutesLesTuiles();
		}

		Pioche(const Pioche& p)=delete;

		Pioche& operator=(const Pioche& p)=delete;

		~Pioche() {
			for(Tuile* t : pioche) {
				delete t;
			}
			for(Tuile* t : piochees) {
				delete t;
			}
		}

		size_t getTaillePioche() const {
            return pioche.size();
		}

		const Tuile* piocher() {

		    if(getTaillePioche() == 0) {
                return nullptr;
		    }

            size_t tuilePiocheIdx = rand() % getTaillePioche();

            auto itTuile = find(pioche.begin(), pioche.end(), pioche[tuilePiocheIdx]);

            piochees.push_back(pioche[tuilePiocheIdx]);

            pioche.erase(itTuile);

            return piochees.back();

		}

	private:

		void recupereToutesLesTuiles();

	};

}


#endif
