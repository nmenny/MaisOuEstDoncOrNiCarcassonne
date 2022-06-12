#include <QPainter>
#include <QColor>
#include <QPoint>
#include "InterfaceEnvironnement.h"
#include "CarcassonneException.h"

namespace Carcassonne {

    const QColor InterfaceEnvironnement::COULEUR_PROPOSITION_DE_POS = QColor("#E21CE9");

    InterfaceEnvironnement::InterfaceEnvironnement(QWidget *parent) : QPushButton(parent) {
        connect(this, SIGNAL(clicked()), this, SLOT(handleClicked()));
        setAttribute(Qt::WA_NoSystemBackground);
        setDisabled(true);
        //setAttribute(Qt::WA_TransparentForMouseEvents);
        hide();
        coordAPoser = Coordonnee(-1, -1);
    }

    void InterfaceEnvironnement::defEmplPosables(const Coordonnees& c) {
        ouPeutPoser = c;
        clearEmplacementsPoses();
        setEnabled(true);
        coordAPoser = Coordonnee(-1, -1);
    }

    void InterfaceEnvironnement::clearEmplacementsPoses() {
        meeplesPoses.clear();
        setCouleurMeeple(COULEUR_PROPOSITION_DE_POS);
        update();
    }

    void InterfaceEnvironnement::poserMeeple(const Meeple& m, const QColor& couleurJ) {
        setCouleurMeeple(couleurJ);
        setEnabled(true);
        meeplesPoses.push_back(coordAPoser);
        update();
    }

    void InterfaceEnvironnement::paintEvent(QPaintEvent *) {
        QPainter p(this);
        p.begin(this);

        if(couleurMeeple == COULEUR_PROPOSITION_DE_POS) {
            for(Coordonnee c : ouPeutPoser) {
                p.fillRect((c.getX() * DIM_ENV) + (DIM_ENV - TAILLE_MEEPLE) / 2, (c.getY() * DIM_ENV) + (DIM_ENV - TAILLE_MEEPLE) / 2, TAILLE_MEEPLE, TAILLE_MEEPLE, couleurMeeple);
            }
        } else {
            for(Coordonnee c : meeplesPoses) {
                p.fillRect((c.getX() * DIM_ENV) + (DIM_ENV - TAILLE_MEEPLE) / 2, (c.getY() * DIM_ENV) + (DIM_ENV - TAILLE_MEEPLE) / 2, TAILLE_MEEPLE, TAILLE_MEEPLE, couleurMeeple);
            }
        }
        p.end();
    }

    Coordonnee InterfaceEnvironnement::extractCoord(const QPoint& p) {
        int x = 0, y = 0;
        while(y < static_cast<int>(Tuile::NB_ENV_LIGNE)) {
            x = 0;
            while(x < static_cast<int>(Tuile::NB_ENV_COL)) {
                if(p.y() >= y * DIM_ENV && p.y() < (y+1) * DIM_ENV &&
                   p.x() >= x * DIM_ENV && p.x() < (x+1) * DIM_ENV
                  ) {
                    return Coordonnee(x, y);
                }
                x++;
            }
            y++;
        }
        return Coordonnee(-1, -1);
    }

    void InterfaceEnvironnement::handleClicked() {
        QPoint p = this->mapFromGlobal(QCursor::pos());
        Coordonnee c = extractCoord(p);
        if(c.getX() != -1) {
            coordAPoser = c;
            emit sig_environnementSelect(c);
        }
    }

}
