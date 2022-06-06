#include <string>
#include <vector>

#include "Utils.h"

namespace Carcassonne {

    vector<string> splitString(const string& chaine, const string& sep) {
        vector<string> champs;
        string champ, tmp;
        size_t idxSep;

        tmp = chaine;

        idxSep = string::npos;

        // Recupere chaque champ de la ligne
        while((idxSep = tmp.find(sep)) != string::npos)
        {
            champ = tmp.substr(0, idxSep);
            champs.push_back(champ);
            tmp = tmp.substr(idxSep+1);
        }

        return champs;
    }

}
