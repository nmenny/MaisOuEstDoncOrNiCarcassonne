/*
	Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#include "Joueurs.h"
#include "CarcassonneException.h"

namespace Carcassonne {

	Joueurs::Handler Joueurs::handler(nullptr);

	Joueurs::Joueurs() {
		listeJoueurs = new Joueur*[Joueurs::NB_JOUEUR_MAXI];
		for(int idxJoueur = 0; idxJoueur < Joueurs::NB_JOUEUR_MAXI; idxJoueur++) {
			listeJoueurs[idxJoueur] = nullptr;
		}

        // Ajoute toujours au moins 2 joueurs
		ajouterJoueur();
		ajouterJoueur();
	}

	void Joueurs::ajouterJoueur() {

        // Verifie que l'on ajoute pas plus de NB_JOUEUR_MAXI joueurs
		if(nbJoueur >= Joueurs::NB_JOUEUR_MAXI) {
			throw JoueurException("Ne peut plus avoir plus de joueurs");
		}

		listeJoueurs[nbJoueur] = new Joueur(nbJoueur);

		nbJoueur++;
	}

	Joueur* Joueurs::getJoueur(int idxJoueur) const {
	    // Verifie que le joueur a recuperer a bien ete attribue
		if((idxJoueur < 0) || (idxJoueur >= nbJoueur)) {
			throw JoueurException("Indice incorrect !");
		}

		return listeJoueurs[idxJoueur];
	}
}
