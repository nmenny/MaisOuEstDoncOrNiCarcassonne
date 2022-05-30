#include <iostream>
#include <fstream>
#include <vector>

#include "CarcassonneException.h"
#include "Pioche.h"

namespace Carcassonne {

    using namespace std;

    const string Pioche::TUILES_NOM_FICHIER = "data/allTuiles.csv";

	void Pioche::recupereToutesLesTuiles() {
	    // Ouvre le fichier contenant les tuiles
		ifstream stream(Pioche::TUILES_NOM_FICHIER);

        if(!stream.is_open()) {
            throw PiocheException("N'a pas pu ouvrir le fichier " +Pioche::TUILES_NOM_FICHIER);
        }

        string line, champ, tmp;
        stream >> line; // skip la premier ligne
        vector<string> champs;
        size_t idxSep;

        // Parcours chaque ligne du fichier
        while(stream >> line) {

            champs.clear();

            tmp = line;

            idxSep = string::npos;

            // Recupere chaque champ de la ligne
            while((idxSep = tmp.find(";")) != string::npos)
            {
                champ = tmp.substr(0, idxSep);
                champs.push_back(champ);
                tmp = tmp.substr(idxSep+1);
            }

            // Cree une nouvelle Tuile a partir des champs recuperes
            pioche.push_back(new Tuile(champs[0], champs[1]));
        }
	}

}
