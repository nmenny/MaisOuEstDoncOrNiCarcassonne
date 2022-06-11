#include <string>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <Qfont>

#include "InterfaceJeu.h"
#include "InterfacePlateau.h"
#include "InterfaceJoueurs.h"
#include "InterfacePioche.h"
#include "InterfaceVariables.h"

namespace Carcassonne {

    static const std::string TITRE_FENETRE = "Carcassonne";

    InterfaceJeu::InterfaceJeu(size_t nbJoueurs, QWidget* parent) : QWidget(parent), joueurs(nbJoueurs) {
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

        infoTour = new QLabel("", this);
        infoTour->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        QFont font;
        font.setBold(true);
        font.setPixelSize(15);
        infoTour->setFont(font);
        layoutDroite->addWidget(infoTour);
        layoutDroite->setAlignment(infoTour, Qt::AlignHCenter);

        joueurs.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        layoutDroite->addWidget(&joueurs);

        pioche.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        layoutDroite->addWidget(&pioche);
        layoutDroite->setAlignment(&pioche, Qt::AlignHCenter);

        layoutPrincipal->addLayout(layoutDroite);
        layoutPrincipal->setAlignment(layoutDroite, Qt::AlignHCenter);

    }

}
