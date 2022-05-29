#include "Ville.h"

namespace Carcassonne {
    class Villes {
    private :
        Ville** listeVilles;
        int nbVilles=0;
        int nbVillesMax=30;
    public :
        Villes() : listeVilles(new Ville*[nbVillesMax]) {}
        ~Villes() {

        }
        Ville* creerVille(Tuile* premiereTuile) {
            Ville* newVille=new Ville(premiereTuile);
            listeVilles[nbVilles]=newVille;
            return newVille;
        }
        Ville* fusionnerVilles(Ville* villeOriginale, Ville* villeAAjouter) {
            Tuile** tuilesAChanger=villeAAjouter->getTuiles();
            int nbTuilesAChanger=villeAAjouter->getTaille();
            for(int i=0;i<nbTuilesAChanger;i++){
                villeOriginale->ajouterTuile(tuilesAChanger[i]);
            }
            //Suppression de villeAAjouter
            for(int i=0;i<nbVilles;i++){
                if (listeVilles[i]==villeAAjouter) {
                    listeVilles[i]=listeVilles[--nbVilles];
                }
            }
            delete villeAAjouter;
            return villeOriginale;
        }
    };
}