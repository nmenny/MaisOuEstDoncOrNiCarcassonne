#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include <list>
#include <string>

using namespace std;


namespace Carcassonne {

	class Abbe;
	class GdMeeple;
	class BasicMeeple;

	class JoueurException {
		string info;
	public:
	    JoueurException(const string msg) :info(msg) {}
	    ~JoueurException() {}
	    const char* what() const { return info.c_str(); }
	};

	class Joueur {

		static const int NB_MEEPLE_DEFAUT = 10;

		int score = 0;
		Abbe* abbe = nullptr;
		GdMeeple* grandMeeple = nullptr;
		list<BasicMeeple*> listeBasicMeeples;

	public:

		Joueur();

		~Joueur();

		int getScore() const;

		void incrementScore();

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