#ifndef __INTERFACEJOUEUR_H__
#define __INTERFACEJOUEUR_H__

#include <QWidget>

class QLabel;
class QSpinBox;
class QVBoxLayout;
class QHBoxLayout;

namespace Carcassonne {

    class InterfaceMeeple;

    class InterfaceJoueur : public QWidget {
    public:
    private:
        size_t num;
        QLabel* nomJoueur;
        QSpinBox* champPts;
        InterfaceMeeple* cercleCouleurJoueur;
        QVBoxLayout* layoutPrincipal;
        QHBoxLayout* layoutDetailJoueur;
    public:
        InterfaceJoueur(size_t numJoueur, const QColor& couleur, QWidget* parent = nullptr);

        InterfaceJoueur(const InterfaceJoueur& j)=delete;
        InterfaceJoueur& operator=(const InterfaceJoueur& j)=delete;

        virtual ~InterfaceJoueur()=default;

        void setPoints(int pts);

        size_t getNum() const { return num; }
    };

}

#endif // __INTERFACEJOUEUR_H__
