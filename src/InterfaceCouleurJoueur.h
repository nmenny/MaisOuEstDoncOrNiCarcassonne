/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef __INTERFACECOULEURJOUEUR_H__
#define __INTERFACECOULEURJOUEUR_H__

#include <QPushButton>

namespace Carcassonne {

    class InterfaceCouleurJoueur : public QPushButton {
        Q_OBJECT
    private:
        static const int TAILLE_POINT = 15;
    private:
        QColor couleurPoint;
    public:
        explicit InterfaceCouleurJoueur(const QColor& couleur, QWidget* parent = nullptr);

        virtual ~InterfaceCouleurJoueur()=default;
    protected:
        void paintEvent(QPaintEvent *event) override;
    };

}

#endif // __INTERFACECOULEURJOUEUR_H__
