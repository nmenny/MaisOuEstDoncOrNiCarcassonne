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
