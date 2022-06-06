/*! \file Tuile.h
    \version 0.1
*/

#ifndef __TUILE_H__
#define __TUILE_H__

#include <string>
#include <array>
#include <iostream>

using namespace std;

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    /*! \enum directionRotation
        \brief Les differents sens de rotation possibles
    */
    enum class directionRotation {
        droite, /*!< Rotation a droite */
        gauche /*!< Rotation a gauche */
    };

    class Environnement;
    class Meeple;

    /*! \class IdentificateurTuile
        \brief Identificateur d'un tuile
    */
    class IdentificateurTuile {

        friend class Tuile;

    private:
        const string idString = ""; /*!< Chaine contenant l'identifiant de la Tuile */
        string idExtension = ""; /*!< Chaine contenant l'extension a laquelle appartient la Tuile */
        int nbTuile; /*!< Le numero de la Tuile */

        /*! \brief Constructeur de la classe
            \param[in] str Identifiant de la Tuile
        */
        IdentificateurTuile(const string& str);

        /*! \brief Destructeur de la classe */
        ~IdentificateurTuile()=default;

    public:

        /*!
            \brief Recupere l'identifiant de la Tuile
            \return Identifiant de la Tuile
        */
        const string& getId() const { return idString; }

        /*!
            \brief Recupere l'extension a laquelle appartient la tuile
            \return Extension de la Tuile
        */
        const string& getExtension() const { return idExtension; }

        /*!
            \brief Recupere le numero de la Tuile
            \return Le numero de la Tuile
        */
        int getNbTuile() const { return nbTuile; }
    };


    /*! \class Tuile
        \brief Represente une Tuile
    */
    class Tuile {
    public:

        static const size_t NB_ZONES = 9; /*!< Nombre de zones sur une Tuile */

    private:

        const IdentificateurTuile idTuile; /*!< Identificateur de la carte */
        array<Environnement*, NB_ZONES> surfaces; /*!< Represente les environnements presentant dans la Tuile */
        Environnement* environnementAvecMeeple = nullptr; /*!< Environnement sur lequel un Meeple est pose */
        size_t indiceDeEnvAvecMeeple = -1; /*!< Indice dans la liste des environnements de celui possedant un meeple */

    public:

        /*! \brief Constructeur de la classe
            \param[in] id Identifiant de la Tuile
            \param[in] zonesSurfaces Les differents environnements presents sur la Tuile
        */
        Tuile(std::string& id, std::string& zonesSurfaces);

        /*! \brief Destructeur de la classe */
        ~Tuile()=default;

        /*!
            \brief Recupere l'identificateur de la Tuile
            \return Identificateur de la Tuile
        */
        const IdentificateurTuile& getID() const {
            return idTuile;
        }

        /*!
            \brief Affiche la tuile dans un stream
            \param[in,out] f Le stream dans lequel est affiche la Tuile
            \param[in] isinline Affichage en ligne ou non
                <Default: false>
        */
        void affiche(ostream& f, bool isinline=false) const;

        /*!
            \brief Convertit la Tuile en chaine de caracteres
            \param[in] isinline Affichage en ligne ou non
                <Default: false>
            \return Une Tuile sous forme de chaine de caracteres
        */
        string toString(bool isinline=false) const;

        /*!
            \brief Fait une rotation de la Tuile
            \param[in] dir Direction dans laquelle la Tuile rotate
            \return Pointeur sur la Tuile qui a subit la rotation
        */
        Tuile* rotation(const directionRotation& dir);

        /*!
            \brief Pose un meeple sur un environnement particulier sur la Tuile
            \param[in] env L'environnement surlequel le meeple est pose
            \param[in,out] m Le meeple a poser
        */
        void poserMeeple(const Environnement& env, Meeple& m);

        /*!
            \brief Retire le meeple qui est pose sur la Tuile
            \return Le meeple retire
        */
        Meeple* retirerMeeple();

    private:

        /*!
            \brief Fait la fusion interne des environnements de la Tuile (les environnements adjacents)
        */
        void fusionnerEnvironnementsInternes();

    };

}

#endif
