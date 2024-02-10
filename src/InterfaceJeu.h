/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef __INTERFACEJEU_H__
#define __INTERFACEJEU_H__

#include <QWidget>
#include <list>
#include <vector>
#include "Jeu.h"
#include "types.h"
#include "InterfacePlateau.h"
#include "InterfaceJoueurs.h"
#include "InterfacePioche.h"
#include "InterfaceActions.h"

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;

namespace Carcassonne {

    class InterfaceJeu : public QWidget {
        Q_OBJECT
    public:
    private:
        InterfacePlateau plateau;
        InterfaceJoueurs joueurs;
        InterfacePioche pioche;
        InterfaceActions actions;
        QHBoxLayout* layoutPrincipal;
        QVBoxLayout *layoutGauche, *layoutDroite;
        QLabel* infoPartie;
        QPushButton* btnPass;

        std::list<InterfaceTuile*> tuilesAReset;
        std::list<InterfaceTuile*> tuilesAvecMeeples;

        JeuGraphique jeu;
        InterfaceTuile* tuilePosee = nullptr;
        Environnement* envPose = nullptr;

    public:
        InterfaceJeu(std::vector<extensions> ext, size_t nbJoueurs = 2, QWidget* parent = nullptr);

        InterfaceJeu(const InterfaceJeu& j)=delete;
        InterfaceJeu& operator=(const InterfaceJeu& j)=delete;

        virtual ~InterfaceJeu()=default;

        /*! \brief Reinitialise des elements d'interfaces apres qu'un utilisateur a pose une Tuile par exemple */
        void resetInterface();

        /*! \brief Affiche a l'utilisateur les emplacements ou il peut poser une Tuile */
        void afficheEmplacementsJouables();

        /*! \brief Affiche le score */
        void afficheScore();

        /*! \brief Affiche a quel joueur c'est au tour de jouer */
        void afficheJoueur();

        void afficheMeeples();

        /*! \brief Affiche a l'utilisateur la Tuile courante */
        void afficheTuileCourante();

        void tourSuivant();

        /*! \brief Affiche un message signalant la fin de la partie */
        void finPartie();

        /*! \brief Affiche le gagnant */
        void afficheGagnant();

        /*!
            \brief Affiche un message d'erreur
            \param[in] err Le type d'erreur
            \param[in] msg Le message d'erreur
                <optionnel>
        */
        void afficheMessageErreur(const InterfaceError& err, const std::string& msg = "");

    private:

        void initPartie();

        void initPlateau();

        void actualiser();

        void interationMeeplesActif();

        void interationMeeplesStop();

    private slots:

        void handleRotation(Carcassonne::directionRotation d);
        void handleRepioche();
        void handlePlacementTuile(Carcassonne::Coordonnee);
        void handleDemandePlacementMeeple(Carcassonne::InterfaceTuile*, Carcassonne::Environnement*);
        void handlePlacementImpossible(Carcassonne::InterfaceTuile*);
        void handlePassageTour();
        void handlePlacementMeeple(Carcassonne::InterfaceMeeple*);
        void handleRetraitMeeple(Carcassonne::InterfaceTuile*, Carcassonne::Environnement*);
        void handleValidePoints();
    };

}

#endif // __INTERFACEJEU_H__
