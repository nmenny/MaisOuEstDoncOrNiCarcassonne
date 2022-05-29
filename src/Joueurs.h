#ifndef __JOUEURS_H__
#define __JOUEURS_H__

#include "Joueur.h"

namespace Carcassonne {

	class Joueur;

	class Joueurs {

		struct Handler {
			Joueurs* instance;
			Handler(Joueurs* j) { instance = j; }
			~Handler() { delete instance; }
		};

		static const int NB_JOUEUR_MAXI = 4;

		static Handler handler;

		Joueur** listeJoueurs = nullptr;

		int nbJoueur = 0;

		Joueurs();

		~Joueurs();

	public:

		static Joueurs* getInstance();

		static void libererInstance();

		void ajouterJoueur();

		Joueur* getJoueur(int idxJoueur) const;

		Joueur** getJoueurs() const;

		int getNbJoueurs() const;

	};

}

#endif

