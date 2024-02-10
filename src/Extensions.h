/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <string>
#include <set>
#include <vector>

namespace Carcassonne {

    using namespace std;

    /*! \enum extensions
        \brief Les differentes extensions du jeu
    */
    enum class extensions {
        Base,
        Paysans,
        Abbe,
        Riviere,
        Auberge
    };

    std::vector<std::string> getMeeples(std::vector<extensions> ext);

    std::string toString(extensions);

}


#endif // EXTENSIONS_H
