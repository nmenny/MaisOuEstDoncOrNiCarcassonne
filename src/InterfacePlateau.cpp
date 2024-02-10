/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <algorithm>

#include "Extensions.h"
#include "InterfacePlateau.h"
#include "CarcassonneException.h"
#include "Surface.h"

namespace Carcassonne {

    InterfacePlateau::InterfacePlateau(std::vector<extensions> extensionListe, QWidget* parent) : QWidget(parent), ext(extensionListe) {
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

    InterfaceTuile* InterfacePlateau::placerTuile(const Tuile* t, const Coordonnee& c, qreal rotTuile) {
        if(t == nullptr) {
            return nullptr;
        }
        if(c.getX() < 0 || c.getX() >= Plateau::NB_COLONNES_MAX || c.getY() < 0 || c.getY() >= Plateau::NB_LIGNES_MAX) {
            throw InterfaceException("Les coordonnees fournies sont hors du plateau !");
        }
        if(plateau[c.getY()][c.getX()]->getTuile() != nullptr) {
            throw InterfaceException("On ne peut pas poser de Tuile sur un emplacement deja occupe !");
        }
        plateau[c.getY()][c.getX()]->setTuile(t, rotTuile);
        update();

        return plateau[c.getY()][c.getX()];
    }


    void InterfacePlateau::handlePlacerTuile(Carcassonne::InterfaceTuile* i) {
        if(i != nullptr) {
            if(i->estPosee() && i->getTuile() == nullptr) {
                Coordonnee c = getCoordsTuile(i);
                if(c.getX() != -1) {
                    emit sig_tuilePlacee(c);
                }
            }
        }
    }


    void InterfacePlateau::handleVerifPlacementMeeple(Carcassonne::InterfaceTuile* t, Carcassonne::Environnement* e) {
        if(std::find(ext.begin(), ext.end(), extensions::Paysans) != ext.end() || dynamic_cast<Pre*>(e) == nullptr) {
            emit sig_placeMeeple(t, e);
        } else {
            emit sig_nePeutPasPlacerMeeple(t);
        }

    }

}
