#include <iostream>
#include <fstream>
#include <vector>

#include "CarcassonneException.h"
#include "Pioche.h"

namespace Carcassonne {

    using namespace std;

    const string Pioche::TUILES_NOM_FICHIER = "data/allTuiles.csv";

	void Pioche::recupereToutesLesTuiles() {
		ifstream stream(Pioche::TUILES_NOM_FICHIER);

        if(!stream.is_open()) {
            throw PiocheException("N'a pas pu ouvrir le fichier " +Pioche::TUILES_NOM_FICHIER);
        }

        string line, champ, tmp;
        stream >> line;
        vector<string> champs;
        size_t idxSep;
        while(stream >> line) {

            champs.clear();

            tmp = line;

            idxSep = string::npos;

            while((idxSep = tmp.find(";")) != string::npos)
            {
                champ = tmp.substr(0, idxSep);
                champs.push_back(champ);
                tmp = tmp.substr(idxSep+1);
            }

            pioche.push_back(new Tuile(champs[0], champs[1]));
        }
	}

}
