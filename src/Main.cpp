#include <iostream>

#include "Personnages.h"
#include "Pioche.h"
#include "Tuile.h"
#include "Jeu.h"
#include "Interface.h"

int main(int argc, char* argv[]) {

    using namespace Carcassonne;

    InterfaceConsole interfaceC;

    Jeu j(interfaceC, 2);

    j.partie();

	return EXIT_SUCCESS;
}
