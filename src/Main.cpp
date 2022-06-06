#include <iostream>

#include "GestionnaireMemoireMeeple.h"
#include "GestionnaireMemoireEnvironnement.h"
#include "Jeu.h"
#include "InterfaceConsole.h"

int main(int argc, char* argv[]) {

    using namespace Carcassonne;

    InterfaceConsole interfaceC;

    Jeu j(interfaceC, 2);

    j.partie();

	return EXIT_SUCCESS;
}
