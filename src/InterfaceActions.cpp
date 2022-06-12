#include <QLabel>
#include <string>
#include <vector>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "InterfaceActions.h"
#include "CarcassonneException.h"

namespace Carcassonne {

    InterfaceActions::InterfaceActions(std::vector<extensions> ext, QWidget* parent) : QWidget(parent) {
        layoutPrincipal = new QVBoxLayout(this);
        layoutPrincipal->setContentsMargins(0, 0, 0, 50);

        layoutMeeples = new QHBoxLayout(this);
        layoutMeeples->setSpacing(0);

        std::vector<std::string> idMeeples = getMeeples(ext);

        for(size_t i = 0; i < idMeeples.size(); i++) {
            InterfaceMeeple* meeple = new InterfaceMeeple(idMeeples[i], this);
            meeples.push_back(meeple);
            connect(meeple, &InterfaceMeeple::sig_demandePlacement, this, &InterfaceActions::handleClickActionBtn);
            layoutMeeples->addWidget(meeple);
        }

        layoutPrincipal->addLayout(layoutMeeples);
    }

    void InterfaceActions::afficherNombreRestantMeeples(std::vector<int> nbMeeplesParCat) {
        if(nbMeeplesParCat.size() != meeples.size()) {
            throw InterfaceException("Erreur, le nombre de meeples a afficher dans l'interface n'est pas correct !");
        }
        for(size_t mIdx = 0; mIdx < nbMeeplesParCat.size(); mIdx++) {
            meeples[mIdx]->setNbMeeple(nbMeeplesParCat[mIdx]);
        }
    }

}
