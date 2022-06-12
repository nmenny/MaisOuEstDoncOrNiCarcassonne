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
