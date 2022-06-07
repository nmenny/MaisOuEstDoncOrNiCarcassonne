#include <string>
#include <iostream>

#include "Joueurs.h"
#include "types.h"

#include "Tuile.h"
#include "Jeu.h"

namespace Carcassonne {

    using namespace std;

    Jeu::~Jeu() {
        // Libere toutes les instances des gestionnaires de memoire
        Joueurs::libererInstance();
        Abbayes::libererInstance();
        Jardins::libererInstance();
        Pres::libererInstance();
        Rivieres::libererInstance();
        Routes::libererInstance();
        Villes::libererInstance();
        BasicMeeples::libererInstance();
        GdMeeples::libererInstance();
        Abbes::libererInstance();
    }

    void Jeu::partie() {

        // Tant qu'il reste des Tuiles a jouer
        while(plateau.peutJouerDesTuiles())
        {
            interface.affichePlateau(plateau);

            interface.afficheJoueur(*joueurCourant);

            // TODO : Piocher tant que l'on n'a pas une tuile posable

            interface.afficheTuileCourante(*plateau.getTuile());

            recupEmplacementsJouables();

            interface.afficheEmplacementsJouables(emplacementJouables);

            size_t saisie = -1;

            // Tant que l'utilisateur ne rentre pas une action viable, il doit refaire la saisie
            while(true) {
               try {
                    saisie = interface.demanderOuPoser();
               } catch(...) {}

               if(saisie < emplacementJouables.size()) {
                  break;
               }
            }

            placerTuile(saisie);

            nextJoueur();
        }

        // Fin de partie

        interface.afficheFinPartie();

        interface.affichePlateau(plateau);

        interface.afficheScore(*joueurs);

        interface.demanderPointsAAttribuer(*joueurs);

        interface.afficheScore(*joueurs);

        interface.afficheGagnant(getJoueurGagnant());

    }

}
