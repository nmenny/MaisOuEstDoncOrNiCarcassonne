#include "Joueur.h"

class Carcassonne::Joueur;

namespace Carcassonne {

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

		const Joueur** getJoueurs() const;

		int getNbJoueurs() const;

	};

}



