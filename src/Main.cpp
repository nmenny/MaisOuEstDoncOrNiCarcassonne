#include <iostream>

#include "Personnages.h"
#include "Pioche.h"
#include "Tuile.h"

int main(int argc, char* argv[]) {

    using namespace Carcassonne;

    Pioche p;

    const Tuile* t;

    t = p.piocher();

    t->affiche(std::cout);

    std::cout << t->toString(true) << std::endl;

	return EXIT_SUCCESS;
}
