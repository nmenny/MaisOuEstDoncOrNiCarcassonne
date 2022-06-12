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
        Q_OBJECT
    public:
    private:
        QLabel* titrePage;
        QVBoxLayout* layoutPrincipal;
        QGridLayout* layoutTuiles;
        QScrollArea* scroll;
        std::array<std::array<InterfaceTuile*, Plateau::NB_COLONNES_MAX>, Plateau::NB_LIGNES_MAX> plateau;
        std::vector<extensions> ext;
    public:
        InterfacePlateau(std::vector<extensions> extensionListe, QWidget* parent = nullptr);

        InterfacePlateau(const InterfacePlateau& p)=delete;
        InterfacePlateau& operator=(const InterfacePlateau& p)=delete;

        virtual ~InterfacePlateau();

        InterfaceTuile* placerTuile(const Tuile* t, const Coordonnee& c, qreal rotTuile = 0);

        InterfaceTuile* getTuile(const Coordonnee& c) {
            return plateau[c.getY()][c.getX()];
        }

    private:

        void initPlateau() {
            for(size_t idxLigne = 0; idxLigne < Plateau::NB_LIGNES_MAX; idxLigne++) {
                for(size_t idxCol = 0; idxCol < Plateau::NB_COLONNES_MAX; idxCol++) {
                    plateau[idxLigne][idxCol] = new InterfaceTuile();
                    plateau[idxLigne][idxCol]->poser();
                    connect(plateau[idxLigne][idxCol], &InterfaceTuile::sig_placerTuile, this, &InterfacePlateau::handlePlacerTuile);
                    connect(plateau[idxLigne][idxCol], &InterfaceTuile::sig_placementMeepleOk, this, &InterfacePlateau::handleVerifPlacementMeeple);
                    connect(plateau[idxLigne][idxCol], &InterfaceTuile::sig_enleverMeeple, this, &InterfacePlateau::handleRelaiDemandeRetraitMeeple);
                }
            }
        }

        Coordonnee getCoordsTuile(const InterfaceTuile* i) {
            for(size_t idxLigne = 0; idxLigne < Plateau::NB_LIGNES_MAX; idxLigne++) {
                for(size_t idxCol = 0; idxCol < Plateau::NB_COLONNES_MAX; idxCol++) {
                    if(plateau[idxLigne][idxCol] == i) {
                        return Coordonnee(idxCol, idxLigne);
                    }
                }
            }

            return Coordonnee(-1, -1);
        }

    signals:
        void sig_tuilePlacee(Carcassonne::Coordonnee);
        void sig_placeMeeple(Carcassonne::InterfaceTuile*, Carcassonne::Environnement*);
        void sig_nePeutPasPlacerMeeple(Carcassonne::InterfaceTuile*);
        void sig_retraitMeeple(Carcassonne::InterfaceTuile*, Carcassonne::Environnement*);

    private slots:
        void handlePlacerTuile(Carcassonne::InterfaceTuile*);
        void handleVerifPlacementMeeple(Carcassonne::InterfaceTuile*, Carcassonne::Environnement*);
        void handleRelaiDemandeRetraitMeeple(Carcassonne::InterfaceTuile* i, Carcassonne::Environnement* e) {
            emit sig_retraitMeeple(i, e);
        }

    };

}

#endif // èèINTERFACEPLATEAU_H__
