/*! \file Joueur.h
    \version 0.1
*/

#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include <list>
#include <string>

using namespace std;

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

	class Abbe;
	class GdMeeple;
	class BasicMeeple;

    /*! \class Joueur
        \brief Represente un joueur
    */
	class Joueur {

		static const int NB_MEEPLE_DEFAUT = 10; /*!< Nombre de Meeples par defaut */

		int score = 0; /*!< Score du joueur */
		const int num; /*!< Numero du joueur */
		Abbe* abbe = nullptr; /*!< Abbe dont le joueur est en possession */
		GdMeeple* grandMeeple = nullptr; /*!< GrandMeeple dont le joueur est en possession */
		list<BasicMeeple*> listeBasicMeeples; /*!< Liste de tous les Meeples que possede le Joueur */

	public:

        /*! \brief Constructeur de la classe
            \param num Indice du joueur
        */
		Joueur(int num);

        /*! \brief Destructeur de la classe */
		~Joueur();

        /*! \brief Donne le score du joueur
            \return Le score du joueur
        */
		int getScore() const;

        /*! \brief Donne le numero du joueur
            \return Le numero du joueur
        */
		int getNumero() const;

        /*! \brief Increment le score d'une certaine valeur
            \param[in] incr Le valeur d'increment du score
        */
		void incrementScore(int incr);

		// Prend un meeple du joueur

        /*! \brief Prend un Meeple
            \return Un Meeple, ou nullptr s'il n'y en a plus
        */
		BasicMeeple* prendreMeeple();

        /*! \brief Prend un Grand Meeple
            \return Un Grand Meeple, ou nullptr s'il n'y en a plus
        */
		GdMeeple* prendreGrandMeeple();

        /*! \brief Prend un Abbe
            \return Un Abbe, ou nullptr s'il n'y en a plus
        */
		Abbe* prendreAbbe();

		// Restitue un meeple au joueur

        /*! \brief Rend un Meeple a un joueur
            \param[in] meeple Meeple � rendre
        */
		void rendreMeeple(BasicMeeple* meeple);

        /*! \brief Rend un Grand Meeple a un joueur
            \param[in] gdMeeple Grand Meeple � rendre
        */
		void rendreGrandMeeple(GdMeeple* gdMeeple);

        /*! \brief Rend un Abbe a un joueur
            \param[in] abbeP Abbe � rendre
        */
		void rendreAbbe(Abbe* abbeP);

	};

}

#endif
