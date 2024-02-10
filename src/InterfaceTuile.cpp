/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#include <string>
#include <QPixmap>
#include <QIcon>
#include <QWidget>
#include <QPainter>
#include <QSize>
#include <QTransform>
#include <algorithm>

#include "Environnement.h"
#include "InterfaceTuile.h"
#include "Tuile.h"

namespace Carcassonne {

    static const std::string CHEMIN_REPERTOIRE_IMAGES = "img/";

    InterfaceTuile::InterfaceTuile(QWidget *parent) : QPushButton(parent) {
        initBtn();
    }

    InterfaceTuile::InterfaceTuile(Tuile* t, QWidget *parent) : QPushButton(parent), tuile(t) {
       initBtn();
       loadImgIcon(CHEMIN_REPERTOIRE_IMAGES + t->getID().getStringId());
    }

    void InterfaceTuile::loadImgIcon(const std::string& cheminFich) {
        QPixmap img(cheminFich.c_str());
        QTransform tr;
        tr.rotate(tuileRot);
        img = img.transformed(tr);
        icon = new QIcon(img);
        setIcon(*icon);
        QSize s(LONGUEUR_TUILE, LONGUEUR_TUILE);
        setIconSize(s);
        setEnabled(true);
    }

    void InterfaceTuile::setTuile(const Tuile* t, qreal rot) {
        if(tuile != nullptr) {
            throw InterfaceException("Erreur, l'interface de Tuile est deja associee a une Tuile !");
        }
        tuile = t;
        tuileRot = rot;
        loadImgIcon(CHEMIN_REPERTOIRE_IMAGES + t->getID().getStringId());
    }

    void InterfaceTuile::rotate(qreal v) {
        if(tuile != nullptr) {
            tuileRot = static_cast<int>(tuileRot + v) % 360;
            std::string cheminFich = CHEMIN_REPERTOIRE_IMAGES + tuile->getID().getStringId();
            loadImgIcon(cheminFich);
        }
    }

    void InterfaceTuile::setEmplacementsMeeples(const Coordonnees& c) {
        env->defEmplPosables(c);
    }


    void InterfaceTuile::handleVerifPlacementMeeple(const Carcassonne::Coordonnee c) {
        Environnement* envClick = tuile->getEnvironnement(c);
        if(tuile->peutPoserMeepleDessus(envClick)) {
            env->setDisabled(true);
            emit sig_placementMeepleOk(this, envClick);
        } else if(tuile->aMeepleDessus()) {
            emit sig_enleverMeeple(this, envClick);
        } else {
            env->clearEmplacementsPoses();
        }
    }
}

