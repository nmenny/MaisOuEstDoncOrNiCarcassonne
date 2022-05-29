#ifndef __PERSONNAGES_H__
#define __PERSONNAGES_H__

#include "Joueurs.h"

namespace Carcassonne {
    class Meeple{
    private:
        bool enJeu;
        Joueur * joueur;
    public:
        Meeple(Joueur * j): enJeu(false), joueur(j){}
        Joueur* getProprietaire() const { return joueur; }
        void misEnJeu() {
            enJeu = true;
        }
        void recuperer() {
            enJeu = false;
        }
    };

    class BasicMeeple : public Meeple{
    public:
        BasicMeeple(Joueur* j): Meeple(j){}
    };

    class BasicMeeples{
    private:
        BasicMeeple** listeMpls;
        unsigned int n=0;
        unsigned int tailleMax;
    public:
        unsigned int getcurrentpos() const { return n; }
        BasicMeeples(unsigned int t) : listeMpls(new BasicMeeple*[t]){}
        ~BasicMeeples(){
            for (unsigned int i=0; i<n; i++) delete listeMpls[i];
            delete[] listeMpls;
        }
        BasicMeeples(const BasicMeeples& b):
            listeMpls(new BasicMeeple*[b.tailleMax]), tailleMax(b.tailleMax){}
        BasicMeeples& operator=(const BasicMeeples& b){
            if (this!=&b){
                n=b.n;
                tailleMax=b.tailleMax;
                BasicMeeple** listeMpls = new BasicMeeple*[tailleMax];
                for (unsigned int i=0; i<b.n; i++) listeMpls[i]=b.listeMpls[i];
            }
            return *this;
        }
        BasicMeeple* ajoutMeeple(Joueur* j) {
            listeMpls[n]=new BasicMeeple(j);
            n+=1;
            return listeMpls[n];
        }
        BasicMeeple** getMeeple() { return listeMpls; }
    };

    class GdMeeple : public Meeple{
    public:
        GdMeeple(Joueur* j): Meeple(j){}
    };

    class GdMeeples{
    private:
        GdMeeple** listeGdMpls;
        unsigned int n=0;
        unsigned int tailleMax;
    public:
        unsigned int getcurrentpos() const { return n; }
        GdMeeples(unsigned int t) : listeGdMpls(new GdMeeple*[t]){}
        ~GdMeeples(){
            for (unsigned int i=0; i<n; i++) delete listeGdMpls[i];
            delete[] listeGdMpls;
        }
        GdMeeples(const GdMeeples& b): listeGdMpls(new GdMeeple*[b.tailleMax]), tailleMax(b.tailleMax){}
        GdMeeples& operator=(const GdMeeples& b){
            if (this!=&b){
                n=b.n;
                tailleMax=b.tailleMax;
                for (unsigned int i=0; i<b.n; i++) listeGdMpls[i]=b.listeGdMpls[i];
            }
            return *this;
        }
        GdMeeple* ajoutGdMeeple(Joueur* j) {
            listeGdMpls[n]=new GdMeeple(j);
            n+=1;
            return listeGdMpls[n];
        }
        GdMeeple** getGdMeeple() { return listeGdMpls; }
    };

    class Abbe{
    private:
        bool enJeu;
        Joueur * joueur;
    public:
        Abbe(Joueur* j): enJeu(false), joueur(j){}
        void misEnJeu() {
            enJeu = true;
        }
        void repris() {
            enJeu = false;
        }
    };

    class Abbes{
    private:
        Abbe** listeAb;
        unsigned int n=0;
        unsigned int tailleMax;
    public:
        unsigned int getcurrentpos() const { return n; }
        Abbes(unsigned int t) : listeAb(new Abbe*[t]){}
        ~Abbes(){
            for (unsigned int i=0; i<n; i++) delete listeAb[i];
            delete[] listeAb;
        }
        Abbes(const Abbes& b): listeAb(new Abbe*[b.tailleMax]), tailleMax(b.tailleMax){}
        Abbes& operator=(const Abbes& b){
            if (this!=&b){
                n=b.n;
                tailleMax=b.tailleMax;
                Abbe** listeAb = new Abbe*[tailleMax];
                for (unsigned int i=0; i<b.n; i++) listeAb[i]=b.listeAb[i];
            }
            return *this;
        }
        Abbe* ajoutAb(Joueur* j) {
            listeAb[n]=new Abbe(j);
            n+=1;
            return listeAb[n];
        }
        Abbe** getAbbe() { return listeAb; }
    };
}

#endif