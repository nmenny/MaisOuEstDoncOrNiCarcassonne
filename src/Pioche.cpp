#include <fstream>

#include "Utils.h"
#include "CarcassonneException.h"
#include "Pioche.h"
#include <algorithm>

namespace Carcassonne {

    static const int NB_CHAMPS = 2;

    using namespace std;

    const string Pioche::TUILES_NOM_FICHIER = "data/tuiles.csv";

    void Pioche::recupereToutesLesTuiles(std::vector<extensions> extensionListe) {
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
            Tuile *t = new Tuile(champs[0], champs[1]);
            if(t->getID().getExtension() == extensions::Base) {
                pioche.push_back(t);
            } else if(std::find(extensionListe.begin(), extensionListe.end(), t->getID().getExtension()) != extensionListe.end()) {
                if(t->getID().getExtension() == extensions::Riviere) {
                    piocheRiviere.push_back(t);
                } else {
                    pioche.push_back(t);
                }
            } else {
                delete t;
            }

            nbTuile++;
        }
	}


    Tuile* Pioche::piocher() {
        static bool premPiocheRiv = true;
        static bool premPiocheBase = true;

        if(getTaillePioche() == 0) {
            return nullptr;
        }

        if(piocheRiviere.size() > 0) {

            if(premPiocheRiv) {
                premPiocheRiv = false;
                Tuile *t = getTuileDebRiviere();
                auto itTuile = find(piocheRiviere.begin(), piocheRiviere.end(), t);
                piochees.push_back(t);
                piocheRiviere.erase(itTuile);
                return piochees.back();
            }

            return piocherDansPile(piocheRiviere);

        } else {

            if(premPiocheBase) {
                premPiocheBase = false;
                Tuile *t = getTuileDeb();
                auto itTuile = find(pioche.begin(), pioche.end(), t);
                piochees.push_back(t);
                pioche.erase(itTuile);
                return piochees.back();
            }

            return piocherDansPile(pioche);
        }
    }

    Tuile* Pioche::piocherDansPile(vector<Tuile*>& p) {
        size_t tuilePiocheIdx = 0;
        do {
            // Pioche une Tuile aleatoirement
            tuilePiocheIdx = rand() % p.size();
        } while(p[tuilePiocheIdx]->getID().getSpecificite() == specificiteTuile::Fin && p.size() > 1);

        auto itTuile = find(p.begin(), p.end(), p[tuilePiocheIdx]);

        // Ajoute la Tuile choisie a la pile des Tuiles piochees
        piochees.push_back(p[tuilePiocheIdx]);

        // Enleve la Tuile choisie de la pioche
        p.erase(itTuile);

        return piochees.back();
    }

}
