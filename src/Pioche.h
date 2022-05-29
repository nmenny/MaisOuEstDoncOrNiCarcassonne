#ifndef __PIOCHE_H__
#define __PIOCHE_H__

#include <list>
#include <string>
#include "Tuile.h"

namespace Carcassonne {

	class Pioche {

	private:

		static const std::string TUILES_NOM_FICHIER;

		list<Tuile*> pioche;

		list<Tuile*> piochees;

	public:

		Pioche()=default;

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

	private:

		void recupereToutesLesTuiles();

	};

}


#endif
