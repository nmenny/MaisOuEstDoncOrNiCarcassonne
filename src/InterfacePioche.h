#ifndef __INTERFACEPIOCHE_H__
#define __INTERFACEPIOCHE_H__

#include <QWidget>

class QLabel;
class QProgressBar;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;

namespace Carcassonne {

    class InterfaceTuile;
    class Tuile;

    class InterfacePioche : public QWidget {
    public:
    private:
        QProgressBar* nbTuilesRestantes;
        QLabel* titrePage;
        InterfaceTuile* tuilePioche;
        QHBoxLayout *layoutEtatPioche, *layoutRotation;
        QVBoxLayout* layoutPrincipal, *layoutActions;
        QPushButton *btnRotGauche, *btnRotDroite, *btnRepiocher;
    public:

        InterfacePioche(QWidget* parent = nullptr);

        virtual ~InterfacePioche()=default;

        void afficherTuile(const Tuile* t);

        void retirerElementDePioche();

        void setNbTuilesDansPioche(int nbTuiles);

    };

}

#endif // __INTERFACEPIOCHE_H__
