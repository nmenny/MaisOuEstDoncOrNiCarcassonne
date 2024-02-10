/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef INTERFACEPERSONNAGESH_H
#define INTERFACEPERSONNAGESH_H

#include <string>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

namespace Carcassonne {

    class InterfaceMeeple : public QWidget {
        Q_OBJECT
    private:
        const std::string nomTypeMeeple;
        QLabel *labelNomTypeMeeple, *labelNbMeeple;
        QVBoxLayout* layoutPrincipal;
        QPushButton* jouer;
    public:
        InterfaceMeeple(std::string typeMeeple, QWidget* parent = nullptr) : QWidget(parent), nomTypeMeeple(typeMeeple) {
            layoutPrincipal = new QVBoxLayout(this);
            layoutPrincipal->setAlignment(Qt::AlignHCenter);

            std::string c = "Nb " +nomTypeMeeple +"\nrestants:";
            labelNomTypeMeeple = new QLabel(c.c_str(), this);
            layoutPrincipal->addWidget(labelNomTypeMeeple);

            labelNbMeeple = new QLabel("0", this);
            layoutPrincipal->addWidget(labelNbMeeple);

            jouer = new QPushButton("Placer", this);
            jouer->setDisabled(true);
            layoutPrincipal->addWidget(jouer);

            //------
            // Geston d'events
            connect(jouer, SIGNAL(clicked()), this, SLOT(handleClickBtn()));
        }

        virtual ~InterfaceMeeple()=default;

        const std::string& getId() const {
            return nomTypeMeeple;
        }

        void setNbMeeple(int nbMeeple) {
            labelNbMeeple->setText(std::to_string(nbMeeple).c_str());
        }

        void activeSelectionMeeple() {
            if(labelNbMeeple->text() != "0") {
                jouer->setEnabled(true);
            }
        }

        void desactiveSelectionMeeple() {
            jouer->setDisabled(true);
        }

    signals:
        void sig_demandePlacement(Carcassonne::InterfaceMeeple*);

    private slots:
        void handleClickBtn() {
            emit sig_demandePlacement(this);
        }

    };

}

#endif // INTERFACEPERSONNAGESH_H
