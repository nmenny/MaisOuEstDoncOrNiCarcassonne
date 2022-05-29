#include "Joueurs.h"

namespace Carcassonne {

	Joueurs::Handler Joueurs::handler(nullptr);

	Joueurs* Joueurs::getInstance() {
		if(handler.instance == nullptr) {
			handler.instance = new Joueurs();
		}
		return handler.instance;
	}

	void Joueurs::libererInstance() {
		delete handler.instance;
		handler.instance = nullptr;
	}

	Joueurs::Joueurs() {
		listeJoueurs = new Joueur*[Joueurs::NB_JOUEUR_MAXI];
		for(int idxJoueur; idxJoueur < Joueurs::NB_JOUEUR_MAXI; idxJoueur++) {
			listeJoueurs[idxJoueur] = nullptr;
		}

		ajouterJoueur();
		ajouterJoueur();
	}

	Joueurs::~Joueurs() {
		delete[] listeJoueurs;
	}

	void Joueurs::ajouterJoueur() {

		if(nbJoueur >= Joueurs::NB_JOUEUR_MAXI) {
			throw JoueurException("Ne peut plus avoir plus de joueurs");
		}

		listeJoueurs[nbJoueur] = new Joueur();

		nbJoueur++;
	}

	Joueur* Joueurs::getJoueur(int idxJoueur) const {
		if((idxJoueur < 0) || (idxJoueur >= Joueurs::NB_JOUEUR_MAXI)) {
			throw JoueurException("Indice incorrect !");
		}

		return listeJoueurs[idxJoueur];
	}

	Joueur** Joueurs::getJoueurs() const {
		return listeJoueurs;
	}

	int Joueurs::getNbJoueurs() const {
		return nbJoueur;
	}
}