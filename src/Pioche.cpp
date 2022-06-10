#include <fstream>

#include "Utils.h"
#include "CarcassonneException.h"
#include "Pioche.h"

namespace Carcassonne {

    static const int NB_CHAMPS = 2;

    using namespace std;

    const string Pioche::TUILES_NOM_FICHIER = "data/allTuiles.csv";

	void Pioche::recupereToutesLesTuiles() {
	    // Ouvre le fichier contenant les tuiles
		ifstream stream(Pioche::TUILES_NOM_FICHIER);

        if(!stream.is_open()) {
            throw PiocheException("N'a pas pu ouvrir le fichier " +Pioche::TUILES_NOM_FICHIER);
        }

        string line;
        stream >> line; // skip la premier ligne
        vector<string> champs;
        size_t nbTuile = 1;

        // Parcours chaque ligne du fichier
        while(stream >> line) {

            // Recupere les champs de la ligne
            champs = splitString(line, ';');

            // Verifie que la ligne contient bien au moins deux champs (l'identifiant de Tuile et les structures presentes dessus)
            if(champs.size() < NB_CHAMPS) {
                throw PiocheException("Format de la " +to_string(nbTuile) +"eme tuile dans le fichier incorrect !");
            }

            // Cree une nouvelle Tuile a partir des champs recuperes
            pioche.push_back(new Tuile(champs[0], champs[1]));
            nbTuile++;
        }
	}

}
