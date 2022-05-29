#include "Personnages.h"
#include "Joueur.h"

namespace Carcassonne {

	Joueur::Joueur() : listeBasicMeeples(Joueur::NB_MEEPLE_DEFAUT, nullptr) {}

	Joueur::~Joueur() {}

	int Joueur::getScore() const {
		return score;
	}

	void Joueur::incrementScore() {
		score++;
	}

	// Prend un meeple du joueur

	BasicMeeple* Joueur::prendreMeeple() {
		if(listeBasicMeeples.size() == 0) {
			throw JoueurException("Plus de Meeple recuperable !");
		}

		BasicMeeple* meeple = listeBasicMeeples.front();
		listeBasicMeeples.pop_front();
		return meeple;
	}

	GdMeeple* Joueur::prendreGrandMeeple() {
		if(grandMeeple == nullptr) {
			throw JoueurException("Pas de grand meeple a disposition !");
		}

		GdMeeple* gdMeeple = grandMeeple;
		grandMeeple = nullptr;
		return gdMeeple;
	}

	Abbe* Joueur::prendreAbbe() {
		if(abbe == nullptr) {
			throw JoueurException("Pas d'abbe a disposition !");
		}

		Abbe* saveAbbe = abbe;
		abbe = nullptr;
		return saveAbbe;
	}

	// Restitue un meeple au joueur

	void Joueur::rendreMeeple(BasicMeeple* meeple) {
		listeBasicMeeples.push_back(meeple);
	}

	void Joueur::rendreGrandMeeple(GdMeeple* gdMeeple) {
		if(grandMeeple != nullptr) {
			throw JoueurException("Ce joueur possede deja un grand meeple !");
		}

		grandMeeple = gdMeeple;
	}

	void Joueur::rendreAbbe(Abbe* abbeP) {
		if(abbe != nullptr) {
			throw JoueurException("Ce joueur possede deja un abbe !");
		}

		abbe = abbeP;
	}

}