#include <QPixmap>
#include <QPainter>

#include "InterfaceCouleurJoueur.h"

namespace Carcassonne {

    InterfaceMeeple::InterfaceMeeple(const QColor& couleur, QWidget* parent) : QPushButton(parent), couleurMeeple(couleur) {
        setBackgroundRole(QPalette::Base);
    }

    void InterfaceMeeple::paintEvent(QPaintEvent*) {
        QPainter peintre;
        peintre.begin(this);
        peintre.setRenderHint(QPainter::Antialiasing, true);
        peintre.setPen(QPen(Qt::white,1));
        peintre.setBrush(QBrush(couleurMeeple));

        peintre.drawEllipse(0, (this->size().height() - TAILLE_MEEPLE) / 2, TAILLE_MEEPLE, TAILLE_MEEPLE);
        peintre.end();
    }

}
