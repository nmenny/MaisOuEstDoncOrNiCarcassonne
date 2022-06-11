#ifndef __INTERFACEPLATEAU_H__
#define __INTERFACEPLATEAU_H__

#include <QWidget>
#include <array>
#include "Plateau.h"
#include "InterfaceTuile.h"
#include "Coordonnee.h"

class QGridLayout;
class QVBoxLayout;
class QLabel;
class QScrollArea;

namespace Carcassonne {

    class InterfacePlateau : public QWidget {
    public:
    private:
        QLabel* titrePage;
        QVBoxLayout* layoutPrincipal;
        QGridLayout* layoutTuiles;
        QScrollArea* scroll;
        std::array<std::array<InterfaceTuile*, Plateau::NB_COLONNES_MAX>, Plateau::NB_LIGNES_MAX> plateau;
    public:
        InterfacePlateau(QWidget* parent = nullptr);

        InterfacePlateau(const InterfacePlateau& p)=delete;
        InterfacePlateau& operator=(const InterfacePlateau& p)=delete;

        virtual ~InterfacePlateau();

        void placerTuile(Tuile* t, const Coordonnee& c);

    private:

        void initPlateau() {
            for(size_t idxLigne = 0; idxLigne < Plateau::NB_LIGNES_MAX; idxLigne++) {
                for(size_t idxCol = 0; idxCol < Plateau::NB_COLONNES_MAX; idxCol++) {
                    plateau[idxLigne][idxCol] = new InterfaceTuile();
                }
            }
        }
    };

}

#endif // èèINTERFACEPLATEAU_H__
