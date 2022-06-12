#include "InterfaceConsole.h"

namespace Carcassonne {

    void InterfaceConsole::afficheEmplacementsJouables(const Coordonnees& c) {
        streamOut << "\nVoici les coups jouables:\n";
        streamOut << "idxCoup => (x ; y)\n";
        // Parcours tous les emplacements jouables
        for(size_t emplacementIdx = 0; emplacementIdx < c.size(); emplacementIdx++) {
            // Affiche chaque action possible
            streamOut << emplacementIdx << " => ";
            c[emplacementIdx].affiche(streamOut);
        }
    }

    void InterfaceConsole::afficheMessageErreur(const InterfaceError& err, const std::string& msg) {
        switch(err) {
        case InterfaceError::indiceIncorrect:
            streamOut << "L'indice donne n'est pas correct ! " << msg << "\n";
            break;
        default:
            streamOut << "Erreur generale : " << msg << "\n";
        }
    }

    void InterfaceConsole::afficheScore(const Joueurs& j) {
        streamOut << "| Joueurs | Points |\n";
        // Parcours l'ensemble des joueurs
        for(int idxJoueur = 0; idxJoueur < j.getNbJoueurs(); idxJoueur++) {
            streamOut << "|    " << idxJoueur << "    |";
            // Calcul la longueur (en nombre de caracteres) du score
            int lgScore = to_string(j.getJoueur(idxJoueur)->getScore()).size();

            // Affiche suffisament d'espace pour preserver le formattage
            for(; lgScore < 8; lgScore++) {
                streamOut << " ";
            }

            // Affiche le score
            streamOut << j.getJoueur(idxJoueur)->getScore() << "|\n";
        }
    }

    std::string InterfaceConsole::demanderAction() {
       streamOut << "\nQue souhaitez-vous faire ?\n";

       std::string saisie;

        streamIn >> saisie;

        return saisie;
    }

    void InterfaceConsole::demanderPointsAAttribuer(Joueurs& j) {
        streamOut << "\nY'a-t'il encore des points a attribuer ?(Y/N)\n";

        char c;

        streamIn >> c;

        if(c == 'Y' || c == 'y') {
            int pts;
            // Parcours tous les joueurs
            for(int idxJoueur = 0; idxJoueur < j.getNbJoueurs(); idxJoueur++) {
                // Demande, pour chaque joueur, la valeur d'increment du score
                streamOut << "Points pour le joueur " << (idxJoueur + 1) << ":\n";
                streamIn >> pts;
                j.getJoueur(idxJoueur)->setScore(pts);
            }
        }
    }

    int InterfaceConsole::demanderPoserMeeples(const Coordonnees& c) {
        return -1;
    }

}
