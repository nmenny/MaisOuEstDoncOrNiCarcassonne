#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include "InterfaceJoueurs.h"
#include "InterfaceJoueur.h"
#include "CarcassonneException.h"

namespace Carcassonne {

    const QColor InterfaceJoueurs::COULEUR_J1 = Qt::blue;
    const QColor InterfaceJoueurs::COULEUR_J2 = Qt::red;
    const QColor InterfaceJoueurs::COULEUR_J3 = Qt::green;
    const QColor InterfaceJoueurs::COULEUR_J4 = Qt::yellow;

    InterfaceJoueurs::InterfaceJoueurs(size_t nbJ, QWidget* parent) : QWidget(parent), nbJoueurs(nbJ) {
        if(nbJ > Joueurs::NB_JOUEUR_MAXI) {
            throw InterfaceException("Trop de joueurs definis dans l'interface !");
        }

        layoutPrincipal = new QVBoxLayout(this);
        titrePage = new QLabel("Points", this);
        layoutPrincipal->addWidget(titrePage);

        layoutJoueurs = new QGridLayout(this);


        QColor tabCouleurTmp[] = {COULEUR_J1, COULEUR_J2, COULEUR_J3, COULEUR_J4};
        for(size_t idxJ = 0; idxJ < nbJ; idxJ++) {
            joueurs[idxJ] = new InterfaceJoueur(idxJ+1, tabCouleurTmp[idxJ], this);
            if(idxJ < 2) {
                layoutJoueurs->addWidget(joueurs[idxJ], 0 ,idxJ % 2);
            } else {
                layoutJoueurs->addWidget(joueurs[idxJ], 1 ,idxJ % 2);
            }

        }

        layoutPrincipal->addLayout(layoutJoueurs);

        //
        btnValideScore = new QPushButton("Valider les scores", this);
        btnValideScore->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        btnValideScore->setDisabled(true);

        layoutPrincipal->addWidget(btnValideScore);
        layoutPrincipal->setAlignment(btnValideScore, Qt::AlignHCenter);
    }

    InterfaceJoueurs::~InterfaceJoueurs() {
        for(size_t idxJ = 0; idxJ < nbJoueurs; idxJ++) {
            delete joueurs[idxJ];
        }
    }

}
