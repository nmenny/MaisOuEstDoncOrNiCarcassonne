#ifndef INTERFACEACTIONS_H
#define INTERFACEACTIONS_H

#include <vector>
#include <array>
#include <QWidget>

#include "InterfacePersonnages.h"

class QLabel;
class QHBoxLayout;
class QVBoxLayout;

namespace Carcassonne {

    class InterfaceActions : public QWidget {
    public:
    private:
        QLabel* affAction;
        QVBoxLayout* layoutPrincipal;
        QHBoxLayout* layoutMeeples;
        std::vector<InterfaceMeeple*> meeples;
    public:
        InterfaceActions(QWidget* parent = nullptr);

        virtual ~InterfaceActions() {
            for(auto m : meeples) {
                delete m;
            }
        }

        void afficherAction(std::string msg) {
            affAction->setText(msg.c_str());
        }

        void afficherNombreRestantMeeples(int* nbMeeplesParCat, size_t nbCatMeepleDiff);
    };

}

#endif // INTERFACEACTIONS_H
