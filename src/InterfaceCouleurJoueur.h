#ifndef __INTERFACECOULEURJOUEUR_H__
#define __INTERFACECOULEURJOUEUR_H__

#include <QPushButton>

namespace Carcassonne {

    class InterfaceMeeple : public QPushButton {
    public:
        static const int TAILLE_MEEPLE = 15;
    private:
        QColor couleurMeeple;
    public:
        explicit InterfaceMeeple(const QColor& couleur, QWidget* parent = nullptr);

        virtual ~InterfaceMeeple()=default;
    protected:
        void paintEvent(QPaintEvent *event) override;
    };

}

#endif // __INTERFACECOULEURJOUEUR_H__
