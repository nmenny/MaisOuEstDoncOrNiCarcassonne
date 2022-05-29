#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include <list>
#include <string>

using namespace std;


namespace Carcassonne {

	class Abbe;
	class GdMeeple;
	class BasicMeeple;

	class Joueur {

		static const int NB_MEEPLE_DEFAUT = 10;

		int score = 0;
		const int num;
		Abbe* abbe = nullptr;
		GdMeeple* grandMeeple = nullptr;
		list<BasicMeeple*> listeBasicMeeples;

	public:

		Joueur(int num);

		~Joueur();

		int getScore() const;

		int getNumero() const;

		void incrementScore(int incr);

		// Prend un meeple du joueur

		BasicMeeple* prendreMeeple();

		GdMeeple* prendreGrandMeeple();

		Abbe* prendreAbbe();

		// Restitue un meeple au joueur

		void rendreMeeple(BasicMeeple* meeple);

		void rendreGrandMeeple(GdMeeple* gdMeeple);

		void rendreAbbe(Abbe* abbeP);

	};

}

#endif
