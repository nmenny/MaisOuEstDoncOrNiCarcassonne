/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#include <string>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <array>
#include <QMessageBox>
#include <QPushButton>
#include <algorithm>

#include "InterfaceJeu.h"
#include "InterfacePlateau.h"
#include "InterfaceJoueurs.h"
#include "InterfacePioche.h"
#include "InterfaceVariables.h"
#include "InterfaceJoueur.h"

namespace Carcassonne {

    InterfaceJeu::InterfaceJeu(std::vector<extensions> ext, size_t nbJoueurs, QWidget* parent) : QWidget(parent), plateau(ext), joueurs(nbJoueurs), actions(ext), jeu(ext, nbJoueurs) {

        // ----
        // Creation de l'interface graphique

        setWindowTitle(TITRE_FENETRE.c_str());
        setMaximumSize(FENETRE_PRINCIPALE_LONGUEUR_MAX, FENETRE_PRINCIPALE_HAUTEUR_MAX);
        setWindowState(Qt::WindowMaximized);

        layoutPrincipal = new QHBoxLayout(this);

        //
        layoutGauche = new QVBoxLayout(this);

        layoutGauche->addWidget(&plateau);

        layoutGauche->addWidget(&actions);

        layoutPrincipal->addLayout(layoutGauche);
        layoutPrincipal->setAlignment(layoutGauche, Qt::AlignHCenter);

        //
        layoutDroite = new QVBoxLayout(this);

        infoPartie = new QLabel("", this);
        infoPartie->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        QFont font;
        font.setBold(true);
        font.setPixelSize(15);
        infoPartie->setFont(font);
        layoutDroite->addWidget(infoPartie);
        layoutDroite->setAlignment(infoPartie, Qt::AlignHCenter);

        btnPass = new QPushButton("Passer", this);
        btnPass->setDisabled(true);
        layoutDroite->addWidget(btnPass);
        layoutDroite->setAlignment(btnPass, Qt::AlignHCenter);

        joueurs.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        layoutDroite->addWidget(&joueurs);

        pioche.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        layoutDroite->addWidget(&pioche);
        layoutDroite->setAlignment(&pioche, Qt::AlignHCenter);

        layoutPrincipal->addLayout(layoutDroite);
        layoutPrincipal->setAlignment(layoutDroite, Qt::AlignHCenter);

        // ----
        // Interractions avec l'utilisateur
        QObject::connect(&pioche, &InterfacePioche::sig_rotationTuile, this, &InterfaceJeu::handleRotation);
        QObject::connect(&pioche, SIGNAL(sig_repiocher()), this, SLOT(handleRepioche()));

        QObject::connect(&plateau, &InterfacePlateau::sig_tuilePlacee, this, &InterfaceJeu::handlePlacementTuile);
        QObject::connect(&plateau, &InterfacePlateau::sig_placeMeeple, this, &InterfaceJeu::handleDemandePlacementMeeple);
        QObject::connect(&plateau, &InterfacePlateau::sig_retraitMeeple, this, &InterfaceJeu::handleRetraitMeeple);

        QObject::connect(&actions, &InterfaceActions::sig_veutPoserMeeple, this, &InterfaceJeu::handlePlacementMeeple);

        QObject::connect(btnPass, SIGNAL(clicked()), this, SLOT(handlePassageTour()));

        QObject::connect(&joueurs, &InterfaceJoueurs::sig_validerScores, this, &InterfaceJeu::handleValidePoints);

        // ----
        // Debut la partie en tant que tel
        initPartie();

    }

    void InterfaceJeu::initPartie() {
        resetInterface();
        initPlateau();
        pioche.initNbTuiles(jeu.getPioche().getTaillePioche()+1);
        pioche.afficherTuile(jeu.getPlateau().getTuile());

        actualiser();
    }

    void InterfaceJeu::initPlateau() {
        for(size_t yTab = 0; yTab < Plateau::NB_LIGNES_MAX; yTab++) {
            const array<const Tuile*, Plateau::NB_COLONNES_MAX> ligne = jeu.getPlateau().getLigneDeTuiles(yTab);
            for(size_t xTab = 0; xTab < ligne.size(); xTab++) {
                if(ligne[xTab] != nullptr) {
                    plateau.placerTuile(ligne[xTab], Coordonnee(xTab, yTab));
                }

            }
        }
    }

    void InterfaceJeu::actualiser() {
        resetInterface();
        afficheScore();
        afficheJoueur();
        afficheMeeples();

        pioche.setNbTuilesDansPioche(jeu.getPioche().getTaillePioche());

        if(!jeu.estFini()) {
            jeu.recupEmplacementsJouables();
            afficheEmplacementsJouables();
        }

    }

    void InterfaceJeu::resetInterface() {
        while(!tuilesAReset.empty()) {
            InterfaceTuile* t = tuilesAReset.back();
            if(t->getTuile() == nullptr) {
                t->clearTuile();
            }
            tuilesAReset.pop_back();
        }
        if(tuilePosee != nullptr) {
            tuilePosee->cacheEmplacementsMeeple();
        }
        tuilePosee = nullptr;
        envPose = nullptr;
        btnPass->setDisabled(true);
        actions.desactivePoseMeeple();
        pioche.setEnabled(true);
    }

    void InterfaceJeu::afficheMeeples() {
        vector<int> nbM = jeu.getMeeplesJoueur(*jeu.getJoueurCourant());
        actions.afficherNombreRestantMeeples(nbM);
    }

    void InterfaceJeu::afficheEmplacementsJouables() {
        const Coordonnees c = jeu.getEmplacementsJouables();
        for(size_t idxEmpl = 0; idxEmpl < c.size(); idxEmpl++) {
            tuilesAReset.push_back(plateau.getTuile(c[idxEmpl]));
            tuilesAReset.back()->estEmplacementPosable();
        }
    }

    void InterfaceJeu::afficheScore() {
        const Joueurs* j = jeu.getJoueurs();
        for(size_t idxJ = 0; idxJ < j->getNbJoueurs(); idxJ++) {
            joueurs.getJoueur(idxJ)->setPoints(j->getJoueur(idxJ)->getScore());
        }
    }

    void InterfaceJeu::afficheJoueur() {
        std::string s = "Tour du\nJoueur " +std::to_string(jeu.getJoueurCourant()->getNumero()+1);
        infoPartie->setText(s.c_str());
    }

    void InterfaceJeu::afficheTuileCourante() {
        pioche.afficherTuile(jeu.getPlateau().getTuile());
    }

    void InterfaceJeu::tourSuivant() {
        jeu.nextTuile();
        interationMeeplesStop();
        if(!jeu.estFini()) {
            jeu.nextJoueur();
            actualiser();
            pioche.afficherTuile(jeu.getPlateau().getTuile());
        } else {
            actualiser();
            finPartie();
        }
    }

    void InterfaceJeu::finPartie() {
        pioche.setDisabled(true);
        joueurs.modifScoreActif();
    }

    void InterfaceJeu::afficheGagnant() {
        std::string s = "La partie est finie !!\nFelicitation au joueur " + std::to_string(jeu.getJoueurGagnant()+1);
        infoPartie->setText(s.c_str());
    }

    void InterfaceJeu::afficheMessageErreur(const InterfaceError& err, const std::string& msg) {
        QMessageBox message_warning;
        message_warning.setIcon(QMessageBox::Icon::Warning);
        switch(err) {
        case InterfaceError::indiceIncorrect:
            message_warning.setText(msg.c_str());
            message_warning.setInformativeText("Erreur : Indice fourni incorrect");
            break;
        default:
            message_warning.setText(msg.c_str());
            message_warning.setInformativeText("Erreur");

        }

        message_warning.exec();
    }

    void InterfaceJeu::interationMeeplesActif() {
        for(auto e : tuilesAvecMeeples) {
            e->activeInterractMeeple();
        }
    }

    void InterfaceJeu::interationMeeplesStop() {
        for(auto e : tuilesAvecMeeples) {
            e->cacheEmplacementsMeeple();
        }
    }

    void InterfaceJeu::handleRotation(Carcassonne::directionRotation d) {
        switch(d) {
        case directionRotation::droite:
            jeu.rotationTuileDroite();
            break;
        case directionRotation::gauche:
            jeu.rotationTuileGauche();
        }
        pioche.rotateTuile(d);
        actualiser();
    }


    void InterfaceJeu::handleRepioche() {
        jeu.changerTuile();
        pioche.afficherTuile(jeu.getPlateau().getTuile());
        actualiser();
    }

    void InterfaceJeu::handlePlacementTuile(Carcassonne::Coordonnee c) {
        pioche.setDisabled(true);
        InterfaceTuile* t = plateau.placerTuile(jeu.getPlateau().getTuile(), c, pioche.getTuileCour()->getRotationLevel());
        jeu.placerTuile(c);
        resetInterface();

        tuilePosee = t;

        Coordonnees cMeeple = jeu.getPlateau().getEmplacementOuPeutPoserMeeple(c);

        plateau.getTuile(c)->setEmplacementsMeeples(cMeeple);
        plateau.getTuile(c)->afficheEmplacementsMeeple();

        interationMeeplesActif();
        btnPass->setEnabled(true);
        pioche.setDisabled(true);
    }

    void InterfaceJeu::handleDemandePlacementMeeple(Carcassonne::InterfaceTuile* i, Carcassonne::Environnement* e) {
        envPose = e;
        actions.rendreActifPoseMeeple();
    }

    void InterfaceJeu::handlePassageTour() {
        tourSuivant();
    }

    void InterfaceJeu::handlePlacementMeeple(Carcassonne::InterfaceMeeple* i) {
        std::string mId = i->getId();
        const Meeple* m = jeu.placeMeeple(mId, envPose);
        if(tuilePosee->getTuile()->aMeepleDessus()) {
            tuilePosee->placeMeeple(*m, InterfaceJoueurs::COULEURS_JOUEURS[jeu.getJoueurCourant()->getNumero()]);
            tuilesAvecMeeples.push_back(tuilePosee);
        } else {
            tuilePosee->clearEnv();
        }
        tourSuivant();
    }

    void InterfaceJeu::handlePlacementImpossible(Carcassonne::InterfaceTuile* i) {
        i->cacheEmplacementsMeeple();
    }

    void InterfaceJeu::handleRetraitMeeple(Carcassonne::InterfaceTuile* i, Carcassonne::Environnement* e) {
        try {
            if(i->getTuile()->aMeepleDessus() &&
                    e->getMeeple() != nullptr &&
                    i->getTuile()->getMeeple()->getProprietaire() == jeu.getJoueurCourant() &&
                    e->getMeeple() == i->getTuile()->getMeeple() &&
                    i->getTuile()->getMeeple()->peutEtreRetire(*e)
                    ) {
                Meeple* m = const_cast<Tuile*>(i->getTuile())->retirerMeeple();
                jeu.restituerMeeple(m);
                i->clearEnv();
                i->cacheEmplacementsMeeple();
                auto it = std::find(tuilesAvecMeeples.begin(), tuilesAvecMeeples.end(), i);
                if(it != tuilesAvecMeeples.end()) {
                    tuilesAvecMeeples.erase(it);
                }
                tourSuivant();
            }
        } catch(std::exception) {}

    }

    void InterfaceJeu::handleValidePoints() {
        array<int, Joueurs::NB_JOUEUR_MAXI> scores = joueurs.getScores();
        for(int idxJ = 0; idxJ < jeu.getJoueurs()->getNbJoueurs(); idxJ++) {
            jeu.getJoueurs()->getJoueur(idxJ)->setScore(scores[idxJ]);
        }
        afficheScore();
        afficheGagnant();
    }
}
