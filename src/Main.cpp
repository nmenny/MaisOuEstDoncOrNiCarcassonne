#define UNUSED(x) (void)x

#include <QApplication>
#include <QHBoxLayout>
#include <iostream>

#include "Jeu.h"
#include "InterfaceConsole.h"
#include "InterfaceJeu.h"
#include "types.h"


int main(int argc, char* argv[]) {

    using namespace Carcassonne;

    InterfaceConsole interfaceC;

    Jeu j(interfaceC, 2);

    //j.partie();

    QApplication app(argc, argv);

    InterfaceJeu* interfaceJ = new InterfaceJeu(4);
    interfaceJ->show();

    return app.exec();
}
