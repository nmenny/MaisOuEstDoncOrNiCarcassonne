#include <string>
#include <QPixmap>
#include <QIcon>
#include <QWidget>

#include "InterfaceTuile.h"
#include "Tuile.h"

namespace Carcassonne {

    static const std::string CHEMIN_REPERTOIRE_IMAGES = "img/";

    InterfaceTuile::InterfaceTuile(QWidget *parent) : QPushButton(parent) {
        initBtn();
    }

    InterfaceTuile::InterfaceTuile(Tuile* t, QWidget *parent) : QPushButton(parent), tuile(t) {
       initBtn();
       loadImgIcon(CHEMIN_REPERTOIRE_IMAGES + t->getID().getStringId());
    }

    void InterfaceTuile::loadImgIcon(const std::string& cheminFich) {
        QPixmap img(cheminFich.c_str());
        icon = new QIcon(img);
        setIcon(*icon);
        setIconSize(img.rect().size());
    }

    void InterfaceTuile::setTuile(const Tuile* t) {
        if(tuile != nullptr) {
            throw InterfaceException("Erreur, l'interface de Tuile est deja associee a une Tuile !");
        }
        tuile = t;
        loadImgIcon(CHEMIN_REPERTOIRE_IMAGES + t->getID().getStringId());
    }

}

