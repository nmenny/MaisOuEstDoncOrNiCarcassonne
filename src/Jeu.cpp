#include <string>
#include <iostream>

#include "Tuile.h"
#include "Jeu.h"

namespace Carcassonne {

    using namespace std;

    void Jeu::partie() {

        /*
        while(!plateau.isEmpty())
        {
            interface.affichePlateau(plateau);

            interface.afficheJoueur(*joueurCourant);

            interface.afficheTuileCourante(*plateau.getTuile());

            recupEmplacementsJouables();

            interface.afficheEmplacementsJouables(emplacementJouables);


            int saisie = -1;

            saisie = interface.demanderOuPoser(emplacementJouables);


            const Tuile* tuileJouee = plateau.poserTuile(emplacementJouables[saisie]);

            joueurCourant->incrementScore(1);

            nextJoueur();
        }

        interface.afficheFinPartie();

        interface.affichePlateau(plateau);

        interface.afficheScore(*joueurs);

        interface.demanderPointsAAttribuer(*joueurs);

        interface.afficheScore(*joueurs);

        interface.afficheGagnant(getJoueurGagnant());

        */

        plateau.getTuile()->affiche(std::cout);

        plateau.getTuile()->rotation(directionRotation::droite);

        cout << "\n rot droite \n";

        plateau.getTuile()->affiche(std::cout);

        plateau.getTuile()->rotation(directionRotation::gauche);

        cout << "\n rot gauche \n";

        plateau.getTuile()->affiche(std::cout);

        plateau.getTuile()->rotation(directionRotation::gauche);

        cout << "\n rot gauche \n";

        plateau.getTuile()->affiche(std::cout);

    }

}
