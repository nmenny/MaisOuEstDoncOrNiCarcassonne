#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "InterfacePioche.h"
#include "InterfaceTuile.h"
#include "Tuile.h"

namespace Carcassonne {

    InterfacePioche::InterfacePioche(QWidget* parent ) : QWidget(parent) {

        // ----
        // Creation de l'interface graphique

        layoutPrincipal = new QVBoxLayout(this);

        //
        layoutEtatPioche = new QHBoxLayout(this);

        titrePage = new QLabel("Pioche", this);
        layoutEtatPioche->addWidget(titrePage);

        nbTuilesRestantes = new QProgressBar(this);
        nbTuilesRestantes->setMinimum(0);
        layoutEtatPioche->addWidget(nbTuilesRestantes);

        layoutPrincipal->addLayout(layoutEtatPioche);

        //
        tuilePioche = new InterfaceTuile(this);
        layoutPrincipal->addWidget(tuilePioche);
        layoutPrincipal->setAlignment(tuilePioche, Qt::AlignHCenter);

        //
        layoutActions = new QVBoxLayout(this);

        layoutRotation = new QHBoxLayout(this);

        btnRotGauche = new QPushButton("Gauche", this);
        layoutRotation->addWidget(btnRotGauche);

        btnRotDroite = new QPushButton("Droite", this);
        layoutRotation->addWidget(btnRotDroite);

        layoutActions->addLayout(layoutRotation);

        //

        btnRepiocher = new QPushButton("Repiocher", this);
        btnRepiocher->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        layoutActions->addWidget(btnRepiocher);
        layoutActions->setAlignment(btnRepiocher, Qt::AlignHCenter);

        layoutPrincipal->addLayout(layoutActions);


        // ----
        // Interractions avec l'utilisateur
        connect(btnRotGauche, SIGNAL(clicked()), this, SLOT(evtRotGaHandler()));
        connect(btnRotDroite, SIGNAL(clicked()), this, SLOT(evtRotDrHandler()));
        connect(btnRepiocher, SIGNAL(clicked()), this, SLOT(evtRepiocherHandler()));


    }

    void InterfacePioche::afficherTuile(const Tuile* t) {
        tuilePioche->clearTuile();
        tuilePioche->setTuile(t);
    }

    void InterfacePioche::retirerElementDePioche() {
        nbTuilesRestantes->setValue(nbTuilesRestantes->value()-1);
    }

    void InterfacePioche::setNbTuilesDansPioche(int nbTuiles) {
        nbTuilesRestantes->setValue(nbTuiles);
    }

    void InterfacePioche::initNbTuiles(int nbTuiles) {
        nbTuilesRestantes->setMaximum(nbTuiles);
        nbTuilesRestantes->setValue(nbTuiles-1);
    }

}
