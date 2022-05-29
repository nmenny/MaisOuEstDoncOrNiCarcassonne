#include "Tuile.h"

namespace Carcassonne {
    class Ville {
    private :
        bool eglise=false;
        Tuile** listeTuiles;
        int tailleMax=50;
        int tailleVille=0;
    public :
        Ville(Tuile* premiereTuile):listeTuiles(new Tuile*[tailleMax]){
            listeTuiles[0]=premiereTuile;
            tailleVille++;
        }
        ~Ville(){
            delete[] listeTuiles;
        }
        void ajouterTuile(Tuile* tuile){
            listeTuiles[tailleVille++]=tuile;
            if (tuile->getEglise()){eglise=true;}
        }
        int getTaille(){return tailleVille;}
        Tuile** getTuiles(){return listeTuiles;}
    };
}