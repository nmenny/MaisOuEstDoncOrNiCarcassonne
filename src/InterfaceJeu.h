#ifndef __INTERFACEJEU_H__
#define __INTERFACEJEU_H__

#include <QWidget>
#include "Interface.h"
#include "InterfacePlateau.h"
#include "InterfaceJoueurs.h"
#include "InterfacePioche.h"
#include "InterfaceActions.h"

class QVBoxLayout;
class QHBoxLayout;
class QLabel;

namespace Carcassonne {

    class InterfacePlateau;
    class InterfaceJoueurs;
    class InterfacePioche;

    class InterfaceJeu : public QWidget {
    public:
    private:
        InterfacePlateau plateau;
        InterfaceJoueurs joueurs;
        InterfacePioche pioche;
        InterfaceActions actions;
        QHBoxLayout* layoutPrincipal;
        QVBoxLayout *layoutGauche, *layoutDroite;
        QLabel* infoTour;
    public:
        InterfaceJeu(size_t nbJoueurs = 2, QWidget* parent = nullptr);

        InterfaceJeu(const InterfaceJeu& j)=delete;
        InterfaceJeu& operator=(const InterfaceJeu& j)=delete;

        virtual ~InterfaceJeu()=default;
    };

}

#endif // __INTERFACEJEU_H__
