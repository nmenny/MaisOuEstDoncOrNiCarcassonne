#define UNUSED(x) (void)x

#include <string>
#include <vector>
#include <QApplication>
#include <QHBoxLayout>
#include <iostream>

#include "Jeu.h"
#include "Extensions.h"
#include "InterfaceConsole.h"
#include "InterfaceJeu.h"
#include "GestionnairesMemoire.h"
#include "InterfaceAccueil.h"


int main(int argc, char* argv[]) {
    using namespace Carcassonne;

    // Utilisation de l'interface graphique (par defaut)

    QApplication app(argc, argv);

    InterfaceAccueil fenetre;
    fenetre.show();

    return app.exec();

}
