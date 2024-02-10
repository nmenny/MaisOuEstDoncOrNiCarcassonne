/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#ifndef INTERFACEACCUEIL_H
#define INTERFACEACCUEIL_H

#include <QWidget>>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QSpinBox>
#include <QGridLayout>
#include <QCheckBox>
#include <list>
#include <vector>

#include "InterfaceJeu.h"

#include "InterfaceVariables.h"
#include "Extensions.h"

namespace Carcassonne {

    class InterfaceAccueil : public QWidget {
        Q_OBJECT
    private:
        QHBoxLayout *layoutConfig, *layoutRentrerJoueurs;
        QLabel *titre, *titreConfigJ, *titreConfigExt, *demanderRentrerNomJ;
        QVBoxLayout *layoutPrincipal, *layoutConfigJoueurs, *layoutConfigExtensions;
        QGridLayout *layoutAllExtensions;
        QSpinBox* nbJoueurs;
        QPushButton* commencerPartie;
        std::list<QCheckBox*> choixExtensions;
        InterfaceJeu* jeu;
    public:
        InterfaceAccueil(QWidget* parent = nullptr) : QWidget(parent) {

            //---
            // Interface Graphique
            setWindowTitle(TITRE_FENETRE.c_str());
            setMaximumSize(FENETRE_PRINCIPALE_LONGUEUR_MAX, FENETRE_PRINCIPALE_HAUTEUR_MAX);
            setWindowIcon(QIcon("img/Carcassonne_Icon"));

            //
            layoutPrincipal = new QVBoxLayout(this);

            titre = new QLabel("Carcassonne", this);
            QFont titreFont;
            titreFont.setBold(true);
            titreFont.setUnderline(true);
            titreFont.setPointSize(30);
            titre->setFont(titreFont);
            titre->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

            layoutPrincipal->addWidget(titre);
            layoutPrincipal->setAlignment(titre, Qt::AlignHCenter);

            ////
            layoutConfig = new QHBoxLayout();

            /////
            layoutConfigJoueurs = new QVBoxLayout();
            titreConfigJ = new QLabel("Configuration des joueurs", this);
            titreConfigJ->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            layoutConfigJoueurs->addWidget(titreConfigJ);
            layoutConfigJoueurs->setAlignment(titreConfigJ, Qt::AlignHCenter);

            ///////
            layoutRentrerJoueurs = new QHBoxLayout();


            demanderRentrerNomJ = new QLabel("Nb de joueurs :", this);
            demanderRentrerNomJ->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            layoutRentrerJoueurs->addWidget(demanderRentrerNomJ);
            layoutRentrerJoueurs->setAlignment(demanderRentrerNomJ, Qt::AlignTop);

            nbJoueurs = new QSpinBox(this);
            nbJoueurs->setRange(2, NB_MAX_J);
            layoutRentrerJoueurs->addWidget(nbJoueurs);
            layoutRentrerJoueurs->setAlignment(nbJoueurs, Qt::AlignTop);

            layoutConfigJoueurs->addLayout(layoutRentrerJoueurs);

            layoutConfig->addLayout(layoutConfigJoueurs);

            /////
            layoutConfigExtensions = new QVBoxLayout();
            titreConfigExt = new QLabel("Configuration des extensions", this);
            layoutConfigExtensions->addWidget(titreConfigExt);
            layoutConfigExtensions->setAlignment(titreConfigExt, Qt::AlignHCenter);

            for(extensions e = extensions::Paysans;
                e <= extensions::Auberge;
                e = static_cast<extensions>(static_cast<int>(e) + 1)) {
                QCheckBox* c = new QCheckBox(toString(e).c_str(), this);
                c->setChecked(true);
                choixExtensions.push_back(c);
                layoutConfigExtensions->addWidget(c);
            }

            layoutConfig->addLayout(layoutConfigExtensions);
            layoutPrincipal->addLayout(layoutConfig);

            commencerPartie = new QPushButton("Commencer la partie", this);
            connect(commencerPartie, SIGNAL(clicked()), this, SLOT(handleDebutPartie()));
            layoutPrincipal->addWidget(commencerPartie);
        }
        virtual ~InterfaceAccueil()=default;

    private slots:
        void handleDebutPartie() {
            size_t nbJ = static_cast<size_t>(nbJoueurs->value());

            std::vector<extensions> ext;
            ext.push_back(extensions::Base);

            extensions e = extensions::Paysans;
            for(auto c : choixExtensions) {
                if(c->isChecked()) {
                    ext.push_back(e);
                }
                e = static_cast<extensions>(static_cast<int>(e) + 1);
            }

            jeu = new InterfaceJeu(ext, nbJ);
            jeu->show();
            close();

        }

    };

}

#endif // INTERFACEACCUEIL_H
