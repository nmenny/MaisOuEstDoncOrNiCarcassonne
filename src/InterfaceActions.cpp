#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "InterfaceActions.h"
#include "CarcassonneException.h"

namespace Carcassonne {

    static const size_t NB_MEEPLES_DIFF = 3;

    InterfaceActions::InterfaceActions(QWidget* parent) : QWidget(parent) {
        layoutPrincipal = new QVBoxLayout(this);
        layoutPrincipal->setContentsMargins(0, 0, 0, 50);

        affAction = new QLabel("", this);
        layoutPrincipal->addWidget(affAction);

        layoutMeeples = new QHBoxLayout(this);

        InterfaceMeeple* meeple = new InterfaceMeeple("Meeple", this);
        meeples.push_back(meeple);
        layoutMeeples->addWidget(meeple);

        meeple = new InterfaceMeeple("Gd Meeple", this);
        meeples.push_back(meeple);
        layoutMeeples->addWidget(meeple);

        meeple = new InterfaceMeeple("Abbe", this);
        meeples.push_back(meeple);
        layoutMeeples->addWidget(meeple);

        layoutPrincipal->addLayout(layoutMeeples);
    }

    void InterfaceActions::afficherNombreRestantMeeples(int* nbMeeplesParCat, size_t nbCatMeepleDiff) {
        if(nbCatMeepleDiff != NB_MEEPLES_DIFF) {
            throw InterfaceException("Erreur, le nombre de meeples a afficher dans l'interface n'est pas correct !");
        }
        for(size_t mIdx = 0; mIdx < nbCatMeepleDiff; mIdx++) {
            meeples[mIdx]->setNbMeeple(nbMeeplesParCat[mIdx]);
        }
    }

}
