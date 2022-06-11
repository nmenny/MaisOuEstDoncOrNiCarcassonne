#ifndef INTERFACEPERSONNAGESH_H
#define INTERFACEPERSONNAGESH_H

#include <string>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

namespace Carcassonne {

    class InterfaceMeeple : public QWidget {
    private:
        const std::string nomTypeMeeple;
        QLabel *labelNomTypeMeeple, *labelNbMeeple;
        QVBoxLayout* layoutPrincipal;
    public:
        InterfaceMeeple(std::string typeMeeple, QWidget* parent = nullptr) : QWidget(parent), nomTypeMeeple(typeMeeple) {
            layoutPrincipal = new QVBoxLayout(this);
            layoutPrincipal->setAlignment(Qt::AlignHCenter);

            std::string c = "Nb " +nomTypeMeeple +"\nrestants:";
            labelNomTypeMeeple = new QLabel(c.c_str(), this);
            layoutPrincipal->addWidget(labelNomTypeMeeple);


            labelNbMeeple = new QLabel("0", this);
            layoutPrincipal->addWidget(labelNbMeeple);

        }

        virtual ~InterfaceMeeple()=default;

        void setNbMeeple(int nbMeeple) {
            labelNbMeeple->setText(std::to_string(nbMeeple).c_str());
        }
    };

}

#endif // INTERFACEPERSONNAGESH_H
