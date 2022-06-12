/*! \file Jeu.h
    \version 0.1
*/


#ifndef __JEU_H__
#define __JEU_H__

#include <vector>

#include "Coordonnee.h"
#include "Plateau.h"
#include "InterfaceConsole.h"

#include <iostream>
#include <algorithm>

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Jeu
        \brief Represente une partie generale de Carcassonne
    */
    class Jeu {

    protected:

        Plateau plateau; /*!< Le plateau de jeu */

        Joueurs* joueurs; /*!< Les joueurs presents dans la partie */

        Joueur* joueurCourant; /*!< Le joueur dont c'est le tour */

        Coordonnees emplacementJouables; /*!< Liste des emplacements jouables a l'instant t */

        Coordonnees emplacementsMeeples;

        vector<extensions> ext;

    public:

        /*! \brief Constructeur de Jeu
            \param[in] Le nombre de joueurs dans la partie
                <defaut: 2>
        */
        Jeu(std::vector<extensions> extensionListe, size_t joueur = 2) : plateau(extensionListe), ext(extensionListe) {
            size_t tmp = joueur;
            joueurs = Joueurs::getInstance();
            joueurCourant = joueurs->getJoueur(0);

            // Ajoute des joueurs
            try {
                while(tmp > 2) {
                    joueurs->ajouterJoueur();
                    tmp--;
                }
            } catch(JoueurException& e) {}
        }

        /*! \brief Destructeur de Jeu */
        virtual ~Jeu();

        const Plateau& getPlateau() const { return plateau; }

        const Pioche& getPioche() const { return plateau.getPioche(); }

        const Joueurs* getJoueurs() const { return joueurs; }

        const Joueur* getJoueurCourant() const { return joueurCourant; }

        const Coordonnees& getEmplacementsJouables() const { return emplacementJouables; }

        const Coordonnees& getEmplacementsOuPeutPoserMeeple() const { return emplacementsMeeples; }

        const vector<int> getMeeplesJoueur(const Joueur& j) {
            vector<int> res;
            if(find(ext.begin(), ext.end(), extensions::Abbe) != ext.end()) {
                res.push_back(j.getNbAbbe());
            }
            if(find(ext.begin(), ext.end(), extensions::Auberge) != ext.end()) {
                res.push_back(j.getNbGrandMeeple());
            }
            if(find(ext.begin(), ext.end(), extensions::Base) != ext.end()) {
                res.push_back(j.getNbBasicMeeples());
            }


            return res;
        }

        /*!
            \brief Place une certaine Tuile sur le plateau
            \param[in] emplIdx Indice de l'emplacement (des coordonnees) ou la Tuile doit etre placee
        */
        void placerTuile(int emplIdx) {
            plateau.poserTuile(emplacementJouables[emplIdx]);
        }

        void nextTuile() {
            plateau.nextTuile();
        }

        /*! \brief Passe au joueur suivant */
        void nextJoueur() {
            joueurCourant = joueurs->getJoueur((joueurCourant->getNumero() + 1) % joueurs->getNbJoueurs());
        }

        /*! \brief Recupere les emplacements ou la tuile courante peut etre posee */
        void recupEmplacementsJouables() {
            emplacementJouables = plateau.getEmplacementsOuPeutPoser();
        }

        /*! \brief Recupere l'indice du joueur gagnant */
        int getJoueurGagnant() const {
            size_t idxJoueurScoreMax = 0;
            int scoreMax = 0;
            // Parcours tous les joueurs
            for(size_t idxJoueur = 0; idxJoueur < joueurs->getNbJoueurs(); idxJoueur++) {
                // Si le score du joueur courant est meilleur, c'est ce dernier qui est le meilleur joueur
                if(joueurs->getJoueur(idxJoueur)->getScore() > scoreMax) {
                    scoreMax = joueurs->getJoueur(idxJoueur)->getScore();
                    idxJoueurScoreMax = idxJoueur;
                }
            }

            return idxJoueurScoreMax;
        }

        const Meeple* placeMeeple(std::string idMeeple, Environnement* env) {
            if(!plateau.getTuile()->peutPoserMeepleDessus(env)) {
                throw TuileException("Erreur, ne peut pas poser de Meeple dessus !");
            }
            Meeple* m = nullptr;
            if(idMeeple == "Meeple") {
                m = joueurCourant->prendreMeeple();
            } else if(idMeeple == "Gd Meeple") {
                m = joueurCourant->prendreGrandMeeple();
            } else if(idMeeple == "Abbe") {
                m = joueurCourant->prendreAbbe();
            }

            plateau.poserMeeple(m, env);
            return m;
        }

        void restituerMeeple(Meeple* m) {
            BasicMeeple* b = dynamic_cast<BasicMeeple*>(m);
            if(b != nullptr) {
                joueurCourant->rendreMeeple(b);
            }

            GdMeeple* g = dynamic_cast<GdMeeple*>(m);
            if(g != nullptr) {
                joueurCourant->rendreGrandMeeple(g);
            }

            Abbe* a = dynamic_cast<Abbe*>(m);
            if(a != nullptr) {
                joueurCourant->rendreAbbe(a);
            }
        }

    };

    class JeuConsole final : public Jeu {
    private:
        InterfaceConsole& interface; /*!< Interface utilisateur */
    public:

        /*! \brief Constructeur de Jeu
            \param[in] in L'interface utilisateur utilisee
            \param[in] joueur Le nombre de joueurs dans la partie
                <defaut: 2>
        */
        JeuConsole(std::vector<extensions> ext, InterfaceConsole& in, size_t joueur = 2) : Jeu(ext, joueur), interface(in) {}

        /*! \brief Gere le deroulement d'une partie */
        void partie();
    };


    class JeuGraphique final : public Jeu {
    public:

        /*! \brief Constructeur de Jeu
            \param[in] joueur Le nombre de joueurs dans la partie
                <defaut: 2>
        */
        JeuGraphique(std::vector<extensions> ext, size_t joueur = 2) : Jeu(ext, joueur) {}

        void rotationTuileDroite() { plateau.tournerTuileDroite(); }

        void rotationTuileGauche() { plateau.tournerTuileGauche(); }

        void changerTuile() { plateau.remettreTuile(); }

        const Tuile* placerTuile(Coordonnee c);

        bool estFini() const { return !plateau.peutJouerDesTuiles(); }
    };
}

#endif
