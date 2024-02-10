/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef __INTERFACEJOUEURS_H__
#define __INTERFACEJOUEURS_H__

#include <array>
#include <QWidget>

#include "CarcassonneException.h"
#include "Joueurs.h"
#include "InterfaceJoueur.h"

class QLabel;
class QVBoxLayout;
class QGridLayout;
class QPushButton;

namespace Carcassonne {

    class InterfaceJoueurs : public QWidget {
        Q_OBJECT
    public:
        static const QColor COULEUR_J1;
        static const QColor COULEUR_J2;
        static const QColor COULEUR_J3;
        static const QColor COULEUR_J4;
        static const std::array<QColor, Joueurs::NB_JOUEUR_MAXI> COULEURS_JOUEURS;
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

        InterfaceJoueur* getJoueur(size_t idxJ) const {
            if(idxJ >= nbJoueurs) {
                throw InterfaceException("Erreur, essaie d'acceder a un joueur qui n'existe pas !!");
            }
            return joueurs[idxJ];
        }

        void modifScoreActif();

        std::array<int, Joueurs::NB_JOUEUR_MAXI> getScores();

    signals:
        void sig_validerScores();
    private slots:
        void handleValideScore() { emit sig_validerScores(); }
    };

}

#endif // __INTERFACEJOUEURS_H__
