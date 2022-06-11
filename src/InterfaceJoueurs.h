#ifndef __INTERFACEJOUEURS_H__
#define __INTERFACEJOUEURS_H__

#include <array>
#include <QWidget>

#include "Joueurs.h"

class QLabel;
class QVBoxLayout;
class QGridLayout;
class QPushButton;

namespace Carcassonne {

    class InterfaceJoueur;

    class InterfaceJoueurs : public QWidget {
    public:
        static const QColor COULEUR_J1;
        static const QColor COULEUR_J2;
        static const QColor COULEUR_J3;
        static const QColor COULEUR_J4;
    private:
        size_t nbJoueurs = 2;
        QLabel* titrePage;
        QVBoxLayout* layoutPrincipal;
        QGridLayout* layoutJoueurs;
        QPushButton* btnValideScore;
        std::array<InterfaceJoueur*, Joueurs::NB_JOUEUR_MAXI> joueurs;

    public:
        InterfaceJoueurs(size_t nbJ = 2, QWidget* parent = nullptr);

        InterfaceJoueurs(const InterfaceJoueurs& j)=delete;
        InterfaceJoueurs& operator=(const InterfaceJoueurs& j)=delete;

        virtual ~InterfaceJoueurs();
    };

}

#endif // __INTERFACEJOUEURS_H__
