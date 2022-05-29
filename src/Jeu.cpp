#include <string>
#include <iostream>

#include "Tuile.h"
#include "Jeu.h"

namespace Carcassonne {

    using namespace std;

    void Jeu::partie() {

        int saisie = 0;

        while(!plateau.isEmpty())
        {

            cout << "-- Etat du plateau actuel --\n";

            plateau.affiche(cout);

            cout << "\n-- C'est au tour du joueur " << (joueurCourant->getNumero() + 1) << " de jouer...\n";


            cout << "Voici la tuile a jouer ce tour la :\n";

            plateau.getTuile()->affiche(cout);

            cout << "\nEt voici les endroit ou vous pouvez la poser :\n";

            recupEmplacementsJouables();
            afficheEmplacementsJouables(cout);

            cout << "\nOu souhaitez-vous poser la tuile ?\n";
            /*
            int saisie = -1;

            while(true) {
               try {
                    cin >> saisie;
               } catch(...) {}

               if(saisie >= 0 && saisie < emplacementJouables.size()) {
                  break;
               }

               cout << "La valeur rentree n'est pas correcte, recommencez... (on attend l'indice du coup que vous jouez)\n";

            }

            //cout << saisie << "\n";

            */

            const Tuile* tuileJouee = plateau.poserTuile(emplacementJouables[saisie]);

            //cout << plateau.getPioche().getTaillePioche() << "\n";

            joueurCourant->incrementScore(1);

            nextJoueur();

            saisie += 2;
        }

        cout << "\n\n **** Fin de la partie ****\n\n";

        cout << "-- Etat du plateau final --\n";

        plateau.affiche(cout);

        cout << "\n-- Voici le score actuel --\n";

        afficheScore(cout);


        cout << "\nY'a-t'il encore des points a attribuer ?(Y/N)\n";

        char c;
        /*
        cin >> c;


        if(c == 'Y' || c == 'y') {
            int pts;
            for(int idxJoueur = 0; idxJoueur < joueurs->getNbJoueurs(); idxJoueur++) {
                cout << "Points pour le joueur " << (idxJoueur + 1) << ":\n";
                cin >> pts;
                joueurs->getJoueur(idxJoueur)->incrementScore(pts);
            }
        }

        */

        cout << "\n-- Voici le score final --\n";

        afficheScore(cout);

        cout << "\n*** Felication au joueur " << (getJoueurGagnant()+1) << "!!! \n";

    }

    void Jeu::afficheEmplacementsJouables(ostream& f) const {
        f << "idxCoup => (x ; y)\n";
        for(size_t emplacementIdx = 0; emplacementIdx < emplacementJouables.size(); emplacementIdx++) {
            f << emplacementIdx << " => ";
            emplacementJouables[emplacementIdx].affiche(f);
        }
    }

    void Jeu::afficheScore(std::ostream& f) const {
        f << "| Joueurs | Points |\n";
        for(int idxJoueur = 0; idxJoueur < joueurs->getNbJoueurs(); idxJoueur++) {
            f << "|    " << idxJoueur << "    |";
            int lgScore = to_string(joueurs->getJoueur(idxJoueur)->getScore()).size();

            for(; lgScore < 8; lgScore++) {
                f << " ";
            }

            f << joueurs->getJoueur(idxJoueur)->getScore() << "|\n";
        }
    }

}
