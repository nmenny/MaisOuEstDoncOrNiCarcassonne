#include "Joueurs.h"
#include "CarcassonneException.h"

namespace Carcassonne {

	Joueurs::Handler Joueurs::handler(nullptr);

	Joueurs::Joueurs() {
		listeJoueurs = new Joueur*[Joueurs::NB_JOUEUR_MAXI];
		for(int idxJoueur = 0; idxJoueur < Joueurs::NB_JOUEUR_MAXI; idxJoueur++) {
			listeJoueurs[idxJoueur] = nullptr;
		}

		ajouterJoueur();
		ajouterJoueur();
	}

	void Joueurs::ajouterJoueur() {

		if(nbJoueur >= Joueurs::NB_JOUEUR_MAXI) {
			throw JoueurException("Ne peut plus avoir plus de joueurs");
		}

		listeJoueurs[nbJoueur] = new Joueur(nbJoueur);

		nbJoueur++;
	}

	Joueur* Joueurs::getJoueur(int idxJoueur) const {
		if((idxJoueur < 0) || (idxJoueur >= Joueurs::NB_JOUEUR_MAXI)) {
			throw JoueurException("Indice incorrect !");
		}

		return listeJoueurs[idxJoueur];
	}
}
