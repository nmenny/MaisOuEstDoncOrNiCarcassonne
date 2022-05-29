#include <iostream>
#include <fstream>

#include "Pioche.h"

namespace Carcassonne {

    using namespace std;

    const string Pioche::TUILES_NOM_FICHIER = "../data/allTuiles.csv";

	void Pioche::recupereToutesLesTuiles() {
		ifstream stream(Pioche::TUILES_NOM_FICHIER);
	}

}
