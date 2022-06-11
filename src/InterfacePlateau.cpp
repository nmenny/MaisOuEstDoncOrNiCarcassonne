#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>

#include "InterfacePlateau.h"
#include "CarcassonneException.h"

namespace Carcassonne {

    InterfacePlateau::InterfacePlateau(QWidget* parent) : QWidget(parent) {
        initPlateau();

        layoutPrincipal = new QVBoxLayout(this);

        titrePage = new QLabel("Plateau", this);
        layoutPrincipal->addWidget(titrePage);

        layoutTuiles = new QGridLayout(this);
        layoutTuiles->setSpacing(0);

        QWidget* w = new QWidget(this);
        w->setLayout(layoutTuiles);

        for(size_t idxLigne = 0; idxLigne < Plateau::NB_LIGNES_MAX; idxLigne++) {
            for(size_t idxCol = 0; idxCol < Plateau::NB_COLONNES_MAX; idxCol++) {
                layoutTuiles->addWidget(plateau[idxLigne][idxCol], idxLigne, idxCol);
            }
        }

        scroll = new QScrollArea(this);
        scroll->setWidget(w);
        scroll->verticalScrollBar()->setValue(scroll->verticalScrollBar()->maximum() / 2 - scroll->verticalScrollBar()->maximum() / 5);
        scroll->horizontalScrollBar()->setValue(scroll->horizontalScrollBar()->pageStep() + 100);
        layoutPrincipal->addWidget(scroll);

    }

    InterfacePlateau::~InterfacePlateau() {
        for(auto ligne : plateau) {
            for(InterfaceTuile* tuile : ligne) {
                delete tuile;
            }
        }
    }

    void InterfacePlateau::placerTuile(Tuile* t, const Coordonnee& c) {
        if(c.getX() < 0 || c.getX() >= Plateau::NB_COLONNES_MAX || c.getY() < 0 || c.getY() >= Plateau::NB_LIGNES_MAX) {
            throw InterfaceException("Les coordonnees fournies sont hors du plateau !");
        }
        if(plateau[c.getY()][c.getX()] != nullptr) {
            throw InterfaceException("On ne peut pas poser de Tuile sur un emplacement deja occupe !");
        }
        plateau[c.getY()][c.getX()]->setTuile(t);
        update();
    }

}
