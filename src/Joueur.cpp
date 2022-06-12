#include "Joueur.h"
#include "CarcassonneException.h"
#include "GestionnairesMemoire.h"

namespace Carcassonne {

     Joueur::Joueur(int num): num(num), listeBasicMeeples(Joueur::NB_MEEPLE_DEFAUT, nullptr) {
         // Initialise tous les meeples du joueur
        for(size_t meepleIdx = 0; meepleIdx < NB_MEEPLE_DEFAUT; meepleIdx++) {
            listeBasicMeeples[meepleIdx] = BasicMeeples::getInstance()->ajoutMeeple(this);
        }

        abbe = Abbes::getInstance()->ajoutMeeple(this);

        grandMeeple = GdMeeples::getInstance()->ajoutMeeple(this);

    }

	// Prend un meeple du joueur

	BasicMeeple* Joueur::prendreMeeple() {
	    // Verifie que le joueur possede bien au moins un Meeple
		if(listeBasicMeeples.size() == 0) {
			throw JoueurException("Plus de Meeple recuperable !");
		}

		BasicMeeple* meeple = listeBasicMeeples.back();
		listeBasicMeeples.pop_back();
		return meeple;
	}

	GdMeeple* Joueur::prendreGrandMeeple() {
	    // Verifie que le joueur possede bien un Grand Meeple
		if(grandMeeple == nullptr) {
			throw JoueurException("Pas de grand meeple a disposition !");
		}

		GdMeeple* gdMeeple = grandMeeple;
		grandMeeple = nullptr;
		return gdMeeple;
	}

	Abbe* Joueur::prendreAbbe() {
	    // Verifie que le joueur possede bien un Abbe
		if(abbe == nullptr) {
			throw JoueurException("Pas d'abbe a disposition !");
		}

		Abbe* saveAbbe = abbe;
		abbe = nullptr;
		return saveAbbe;
	}

	// Restitue un meeple au joueur

	void Joueur::rendreMeeple(BasicMeeple* meeple) {
	    // Verifie que ce joueur est bien le proprietaire de ce meeple
        if(meeple->getProprietaire() != this) {
            throw JoueurException("Ce joueur n'est pas le proprietaire de ce BasicMeeple !");
        }
		listeBasicMeeples.push_back(meeple);
	}

	void Joueur::rendreGrandMeeple(GdMeeple* gdMeeple) {
	    // Verifie que ce joueur est bien le proprietaire de ce grand meeple
	    if(gdMeeple->getProprietaire() != this) {
            throw JoueurException("Ce joueur n'est pas le proprietaire de ce GrandMeeple !");
        }
        // Verifie que le joueur actuel ne possede pas deja un grand meeple
		if(grandMeeple != nullptr) {
			throw JoueurException("Ce joueur possede deja un grand meeple !");
		}

		grandMeeple = gdMeeple;
	}

	void Joueur::rendreAbbe(Abbe* abbeP) {
	    // Verifie que ce joueur est bien le proprietaire de cet abbe
	    if(abbeP->getProprietaire() != this) {
            throw JoueurException("Ce joueur n'est pas le proprietaire de cet Abbe !");
        }
        // Verifie que le joueur actuel ne possede pas deja un abbe
		if(abbe != nullptr) {
			throw JoueurException("Ce joueur possede deja un abbe !");
		}

		abbe = abbeP;
	}

}
