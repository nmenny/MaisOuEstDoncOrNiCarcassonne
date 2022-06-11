#ifndef __INTERFACETUILE_H__
#define __INTERFACETUILE_H__

class QIcon;

#include <string>
#include <QPushButton>
#include "CarcassonneException.h"

namespace Carcassonne {

    class Tuile;

    class InterfaceTuile : public QPushButton {
    public:
        static const size_t HAUTEUR_TUILE = 70;
        static const size_t LONGUEUR_TUILE = 70;
    private:
        const Tuile* tuile = nullptr;
        QIcon* icon = nullptr;
    public:

        InterfaceTuile(QWidget *parent = nullptr);

        InterfaceTuile(Tuile* t, QWidget *parent = nullptr);

        virtual ~InterfaceTuile() {
            delete icon;
        }

        void setTuile(const Tuile* t);

        const Tuile* getTuile() const { return tuile; }

        void clearTuile() {
            tuile = nullptr;
            delete icon;
        }

        void loadImgIcon(const std::string& cheminFich);

    private:

        void initBtn() {
            setFixedSize(LONGUEUR_TUILE, HAUTEUR_TUILE);
            setEnabled(false);
        }
    };

}

#endif // __INTERFACETUILE_H__
