#ifndef __INTERFACETUILE_H__
#define __INTERFACETUILE_H__

#include <string>
#include <QPushButton>
#include <QPainter>
#include "Personnages.h"
#include "CarcassonneException.h"
#include "InterfaceEnvironnement.h"
#include "Tuile.h"
#include "const.h"

class QIcon;

namespace Carcassonne {

    class InterfaceTuile : public QPushButton {
        Q_OBJECT
    private:
        const Tuile* tuile = nullptr;
        QIcon* icon = nullptr;
        qreal tuileRot = 0;
        bool posee = false;
        InterfaceEnvironnement* env;
    public:

        InterfaceTuile(QWidget *parent = nullptr);

        InterfaceTuile(Tuile* t, QWidget *parent = nullptr);

        virtual ~InterfaceTuile() {
            delete icon;
        }

        void poser() { posee = true; }

        bool estPosee() const { return posee; }

        void setTuile(const Tuile* t, qreal rot = 0);

        void setEmplacementsMeeples(const Coordonnees& c);

        void afficheEmplacementsMeeple() { env->show(); env->setEnabled(true); }

        void cacheEmplacementsMeeple() {
            if(!tuile->aMeepleDessus()) {
                env->hide();
                env->setDisabled(true);
            }
            env->setDisabled(true);
        }

        const Tuile* getTuile() const { return tuile; }

        void clearTuile() {
            tuile = nullptr;
            delete icon;
            icon = nullptr;
            setDisabled(true);
            env->hide();
            tuileRot = 0;
        }

        void activeInterractMeeple() {
            env->show();
            env->setEnabled(true);
        }

        void clearEnv() {
            env->clearEmplacementsPoses();
        }

        void placeMeeple(const Meeple& m, const QColor& j) {
            env->poserMeeple(m, j);
        }

        void estEmplacementPosable() {
            setEnabled(true);
        }

        void loadImgIcon(const std::string& cheminFich);

        qreal getRotationLevel() const { return tuileRot; }

        void rotate(qreal v);

    signals:

        void sig_placerTuile(Carcassonne::InterfaceTuile*);
        void sig_placementMeepleOk(Carcassonne::InterfaceTuile*, Carcassonne::Environnement*);
        void sig_enleverMeeple(Carcassonne::InterfaceTuile*, Carcassonne::Environnement*);

    private slots:

        void handleClicked() { emit sig_placerTuile(this); }

        void handleVerifPlacementMeeple(const Carcassonne::Coordonnee c);

    private:

        void initBtn() {
            setFixedSize(LONGUEUR_TUILE, HAUTEUR_TUILE);
            setDisabled(true);
            tuileRot = 0;
            env = new InterfaceEnvironnement(this);
            env->resize(this->size());
            connect(this, SIGNAL(clicked()), this, SLOT(handleClicked()));
            connect(env, &InterfaceEnvironnement::sig_environnementSelect, this, &InterfaceTuile::handleVerifPlacementMeeple);
        }

    };

}

#endif // __INTERFACETUILE_H__
