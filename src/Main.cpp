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


    std::cout << Pres::getInstance()->getNbEnvEnMemoire() << "\n";
    std::cout << Villes::getInstance()->getNbEnvEnMemoire() << "\n";
    std::cout << Routes::getInstance()->getNbEnvEnMemoire() << "\n";
    std::cout << Rivieres::getInstance()->getNbEnvEnMemoire() << "\n";
    std::cout << Abbayes::getInstance()->getNbEnvEnMemoire() << "\n";
    std::cout << Jardins::getInstance()->getNbEnvEnMemoire() << "\n";


	return EXIT_SUCCESS;
}
