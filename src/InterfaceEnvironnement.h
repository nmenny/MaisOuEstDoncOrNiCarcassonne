#ifndef INTERFACEENVIRONNEMENT_H
#define INTERFACEENVIRONNEMENT_H

#include <QPushButton>
#include "Tuile.h"
#include "const.h"
#include "Personnages.h"
#include "Coordonnee.h"

namespace Carcassonne {

    class InterfaceEnvironnement : public QPushButton {
        Q_OBJECT
    private:
        static const QColor COULEUR_PROPOSITION_DE_POS;
        static constexpr int DIM_ENV = LONGUEUR_TUILE / Tuile::NB_ENV_COL;
        static const int TAILLE_MEEPLE = 6;
        QColor couleurMeeple = COULEUR_PROPOSITION_DE_POS;
        Coordonnees ouPeutPoser;
        Coordonnees meeplesPoses;
        Coordonnee coordAPoser;
    public:
        explicit InterfaceEnvironnement(QWidget *parent = nullptr);

        virtual ~InterfaceEnvironnement()=default;

        void defEmplPosables(const Coordonnees& c);

        void poserMeeple(const Meeple& m, const QColor& couleurJ);

        void clearEmplacementsPoses();

    private:

        void setCouleurMeeple(const QColor& c) { couleurMeeple = c; }

        Coordonnee extractCoord(const QPoint& p);

    protected:
        void paintEvent(QPaintEvent *) override;
    signals:
        void sig_environnementSelect(const Carcassonne::Coordonnee c);
    private slots:
        void handleClicked();
    };

}

#endif // INTERFACEENVIRONNEMENT_H
