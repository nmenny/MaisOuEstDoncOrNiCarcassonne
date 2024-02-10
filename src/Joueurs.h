/*! \file Joueurs.h
    \version 0.1

    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef __JOUEURS_H__
#define __JOUEURS_H__

#include "Joueur.h"

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Joueurs
        \brief Gere la memoire des tous les Joueurs presents dans le jeu
    */
	class Joueurs {
    public:

        static const int NB_JOUEUR_MAXI = 4; /*!< Nombre maximum de joueurs */

    private:

        /*! \struct Handler
            \brief Encapsule le Singleton de Joueurs
        */
		struct Handler {
			Joueurs* instance; /*!< Instance de Joueurs (Singleton) */

            /*! \brief Cree une nouvelle instance du Singleton
                \param[in] Pointeur sur l'objet Joueurs Singleton
            */
			Handler(Joueurs* j) { instance = j; }

            /*! \brief Detruit le Singleton a la fin de l'application */
			~Handler() { delete instance; }
		};

		static Handler handler; /*!< Instance Singleton statique de Joueurs */

		Joueur** listeJoueurs = nullptr; /*!< Liste des joueurs presents dans la partie */

		int nbJoueur = 0; /*!< Nombre de joueurs dans la partie */

        /*! \brief Constructeur de la classe */
		Joueurs();

        /*! \brief Destructeur de la classe */
		~Joueurs() {
            delete[] listeJoueurs;
        }

	public:

        /*! \brief Recupere l'instance du Singleton */
		static Joueurs* getInstance() {
            if(handler.instance == nullptr) {
                handler.instance = new Joueurs();
            }
            return handler.instance;
        }

        /*! \brief Libere l'instance du Singleton */
		static void libererInstance()  {
            delete handler.instance;
            handler.instance = nullptr;
        }

        /*! \brief Recupere tous les Joueurs
            \return Pointeur sur tous les joueurs
        */
		Joueur** getJoueurs() const {
            return listeJoueurs;
        }

        /*! \brief Recupere le nombre de joueurs presents dans la partie
            \return Le nombre de joueurs presents dans la partie
        */
        size_t getNbJoueurs() const {
            return nbJoueur;
        }

        /*! \brief Ajoute un nouveau Joueur si possible */
		void ajouterJoueur();

        /*! \brief Recupere un certain Joueur
            \param[in] idxJoueur Indice du joueur a recuperer
            \return Pointeur sur le joueur correspondant, ou nullptr si ce joueur n'existe pas
        */
		Joueur* getJoueur(int idxJoueur) const;

	};

}

#endif

