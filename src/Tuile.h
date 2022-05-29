#include <string>

namespace Carcassonne {
    enum class TypeZone {Pre,Ville};
    enum class TypeChemin {Route,Riviere};

    struct ZoneRegion {
        TypeZone typeZone;
        int region;
        ZoneRegion(TypeZone t, int r){typeZone=t;region=r;}
        ZoneRegion(){};
    };

    struct CheminRegion {
        TypeChemin typeChemin;
        int region;
        CheminRegion(TypeChemin t, int r){typeChemin=t;region=r;}
        CheminRegion(){};
    };

    class Tuile {
    private :
        ZoneRegion* Bordures; //Tableau de taille 8, representant les zones des bordures, partant de haut-gauche, puis dans le sens horaire
        CheminRegion* Milieux; //Tableau de taille, representant les chemin sur chaque côté, partant du haut, puis sens horaire
        const std::string ID; //Identificateur de la carte, pour retrouver son dessin
        bool eglise;
    public :
        Tuile(std::string id, ZoneRegion*& b, CheminRegion*& m, bool e) : ID{id}, eglise(e) {
            Bordures = new ZoneRegion[8];
            for(int i=0;i<8;i++){
                Bordures[i]=b[i];
            }
            Milieux = new CheminRegion[4];
            for(int i=0;i<4;i++){
                Milieux[i]=m[i];
            }
        }
        ~Tuile(){
            delete[] Bordures;
            delete[] Milieux;
        }
        
        std::string getID() {
            return ID;
        }
        bool getEglise() {return eglise;}
    };
}