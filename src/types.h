/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef TYPES_H
#define TYPES_H

#include <string>

namespace Carcassonne {

    static const std::string COMMANDE_ROTATION_DROITE = "d";
    static const std::string COMMANDE_ROTATION_GAUCHE = "g";
    static const std::string COMMANDE_REPIOCHER = "r";

    enum class InterfaceError {indiceIncorrect};

}

#endif // TYPES_H
