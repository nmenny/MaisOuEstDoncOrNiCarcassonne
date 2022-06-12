#ifndef __INTERFACEJOUEUR_H__
#define __INTERFACEJOUEUR_H__

#include <QWidget>
#include "InterfaceCouleurJoueur.h"

class QLabel;
class QSpinBox;
class QVBoxLayout;
class QHBoxLayout;

namespace Carcassonne {

    class InterfaceJoueur : public QWidget {
        Q_OBJECT
    public:
    private:
        size_t num;
        QLabel* nomJoueur;
        QSpinBox* champPts;
        InterfaceCouleurJoueur* cercleCouleurJoueur;
        QVBoxLayout* layoutPrincipal;
        QHBoxLayout* layoutDetailJoueur;
    public:
        InterfaceJoueur(size_t numJoueur, const QColor& couleur, QWidget* parent = nullptr);

        InterfaceJoueur(const InterfaceJoueur& j)=delete;
        InterfaceJoueur& operator=(const InterfaceJoueur& j)=delete;

        virtual ~InterfaceJoueur()=default;

        void setPoints(int pts);

        size_t getNum() const { return num; }

        int getScore();

        void modifOk();
    };

}

#endif // __INTERFACEJOUEUR_H__
