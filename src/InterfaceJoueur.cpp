/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#include <string>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "InterfaceCouleurJoueur.h"
#include "InterfaceJoueur.h"


namespace Carcassonne {

    InterfaceJoueur::InterfaceJoueur(size_t numJoueur, const QColor& couleur, QWidget* parent) : QWidget(parent), num(numJoueur) {
        layoutPrincipal = new QVBoxLayout(this);
        layoutDetailJoueur = new QHBoxLayout(this);
        layoutPrincipal->addLayout(layoutDetailJoueur);

        std::string nomJ = "Joueur " + std::to_string(numJoueur);
        nomJoueur = new QLabel(nomJ.c_str(), this);
        layoutDetailJoueur->addWidget(nomJoueur);

        cercleCouleurJoueur = new InterfaceCouleurJoueur(couleur, this);
        layoutDetailJoueur->addWidget(cercleCouleurJoueur);

        champPts = new QSpinBox(this);
        champPts->setMinimum(0);
        champPts->setMaximum(1000);
        champPts->setSingleStep(1);
        champPts->setDisabled(true);
        layoutPrincipal->addWidget(champPts);

    }


    void InterfaceJoueur::setPoints(int pts) {
        champPts->setValue(pts);
    }

    void InterfaceJoueur::modifOk() {
        champPts->setEnabled(true);
    }

    int InterfaceJoueur::getScore() {
        return champPts->value();
    }

}
