#include <QPixmap>
#include <QPainter>

#include "InterfaceCouleurJoueur.h"

namespace Carcassonne {

    InterfaceCouleurJoueur::InterfaceCouleurJoueur(const QColor& couleur, QWidget* parent) : QPushButton(parent), couleurPoint(couleur) {
        setBackgroundRole(QPalette::Base);
    }

    void InterfaceCouleurJoueur::paintEvent(QPaintEvent*) {
        QPainter peintre;
        peintre.begin(this);
        peintre.setRenderHint(QPainter::Antialiasing, true);
        peintre.setPen(QPen(Qt::white,1));
        peintre.setBrush(QBrush(couleurPoint));

        peintre.drawEllipse(0, (this->size().height() - TAILLE_POINT) / 2, TAILLE_POINT, TAILLE_POINT);
        peintre.end();
    }

}
