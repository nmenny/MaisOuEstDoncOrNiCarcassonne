/*! \file Coordonnee.h
    \version 0.1
*/

#ifndef __COORDONNEE_H__
#define __COORDONNEE_H__

#include <vector>
#include <iostream>

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \class Coordonnee
        \brief Represente une coordonnee sur le plateau en 2D
    */
    class Coordonnee {
    private:

        int x = 0; /*!< Composante en X */
        int y = 0; /*!< Composante en Y */

    public:

        /*! \brief Constructeur de la classe */
        Coordonnee()=default;

        /*! \brief Constructeur de la classe
            \param[in] theX Composante en X
            \param[in] theY Composante en Y
        */
        Coordonnee(int theX, int theY) : x(theX), y(theY) {}

        /*! \brief Destructeur de la classe */
        ~Coordonnee()=default;

        /*! \brief Recupere l'abscisse de la coordonnee
            \return Recupere la composante en X
        */
        int getX() const { return x; }

        /*! \brief Recupere l'ordonnee de la coordonnee
            \return Recupere la composante en Y
        */
        int getY() const { return y; }

        /*! \brief Compare deux coordonnees
            \param[in] c2 La coordonnee a comparer
            \return <tt>true</tt> si l'objet courant est equivalent a c2, <tt>false</tt> sinon
        */
        bool operator==(const Coordonnee& c2) const {
            return (c2.x == x) && (c2.y == y);
        }

        /*! \brief Affiche une coordonnee dans un stream
            \param[in,out] f Le stream dans lequel la coordonnee est ecrite
        */
        void affiche(std::ostream& f) const {
            f << "(" << x << " ; " << y << ")\n";
        }

    };

    /*! \class Coordonnees
        \brief Regroupement de coordonnees
    */
    class Coordonnees {
    private:

        std::vector<Coordonnee> coords; /*!< Vecteur de coordonnees */

    public:

        /*! \brief Constructeur de la classe */
        Coordonnees()=default;

        /*! \brief Destructeur de la classe */
        ~Coordonnees()=default;

        /*! \brief Ajoute une nouvelle coordonnee a la liste
            \param[in] c Coordonnee a ajouter
        */
        void push_back(const Coordonnee& c) {
            coords.push_back(c);
        }

        /*! Vide la liste */
        void clear() {
            coords.clear();
        }

        /*! \brief Recupere une coordonnee a un certain indice
            \param[in] idx Indice de la coordonnee a recuperer
            \return La coordonnee a l'indice idx
        */
        Coordonnee at(size_t idx) const {
            return coords[idx];
        }

        /*! \brief Recupere une coordonnee a un certain indice
            \param[in] idx Indice de la coordonnee a recuperer
            \return La coordonnee a l'indice idx
        */
        Coordonnee operator[](size_t idx) const {
            return at(idx);
        }

        /*! \brief Renvoie le nombre de coordonnees presentes dans la liste
            \return La longueur de la liste
        */
        size_t size() const {
            return coords.size();
        }

        /*! \class Iterateur de coordonnees
            \brief Premet d'iterer sur les coordonnees
        */
        class iterator : public std::vector<Coordonnee>::iterator {
		public:
		    /*! \brief Recupere la coordonnee courante
                \return La coordonnee courante
            */
			Coordonnee operator*() const {
				return std::vector<Coordonnee>::iterator::operator*();
			}
		private:

		    /*! \brief Constructeur de la classe
                \param[in] Vecteur sur lequel l'iterateur itere
		    */
			iterator(std::vector<Coordonnee>::iterator it):
				std::vector<Coordonnee>::iterator(it) {}

			friend class Coordonnees;
		};

		/*! \brief Renvoie l'iterateur sur le debut
            \return L'iterateur sur le premier element
        */
		iterator begin() { return iterator(coords.begin()); }

        /*! \brief Renvoie l'iterateur final
            \return L'iterateur de fin
        */
		iterator end() { return iterator(coords.end()); }
    };

}

#endif
