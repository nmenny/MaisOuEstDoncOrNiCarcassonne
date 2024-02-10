/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef INTERFACEACTIONS_H
#define INTERFACEACTIONS_H

#include <vector>
#include <array>
#include <QWidget>

#include "Extensions.h"
#include "InterfacePersonnages.h"

class QLabel;
class QHBoxLayout;
class QVBoxLayout;

namespace Carcassonne {

    class InterfaceActions : public QWidget {
        Q_OBJECT
    public:
    private:
        QVBoxLayout* layoutPrincipal;
        QHBoxLayout* layoutMeeples;
        std::vector<InterfaceMeeple*> meeples;
    public:
        InterfaceActions(std::vector<extensions> ext, QWidget* parent = nullptr);

        virtual ~InterfaceActions() {
            for(auto m : meeples) {
                delete m;
            }
        }

        void afficherNombreRestantMeeples(std::vector<int> nbMeeplesParCat);

        void rendreActifPoseMeeple() {
            for(auto m : meeples) {
                m->activeSelectionMeeple();
            }
        }

        void desactivePoseMeeple() {
            for(auto m : meeples) {
                m->desactiveSelectionMeeple();
            }
        }

    signals:
        void sig_veutPoserMeeple(Carcassonne::InterfaceMeeple*);

    private slots:
        void handleClickActionBtn(Carcassonne::InterfaceMeeple* i) {
            emit sig_veutPoserMeeple(i);
        }
    };

}

#endif // INTERFACEACTIONS_H
