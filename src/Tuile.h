/*! \file Tuile.h
    \version 0.1
*/

#ifndef __TUILE_H__
#define __TUILE_H__

#include <string>
#include <array>
#include <iostream>

#include "Coordonnee.h"

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

    /*! \enum zoneTuile
        \brief Les differentes zones pour les environnements d'une Tuile
    */
    enum class zoneTuile {
        nord, /*!< Zone nord */
        sud, /*!< Zone sud */
        est, /*!< Zone est */
        ouest /*!< Zone ouest */
    };

    /*! \enum extensions
        \brief Les differentes extensions du jeu
    */
    enum class extensions {
        Base,
        Riviere
    };

    /*! \enum specificiteTuile
        \brief Les specificites liees a une Tuile (ex: Tuile de demarrage, ..)
    */
    enum class specificiteTuile {
        Aucune,
        Bouclier,
        Demarrage,
        Fin
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
        extensions idExtension; /*!< L'extension a laquelle appartient la Tuile */
        specificiteTuile specif; /*!< La specificite de la Tuile */
        int nbTuile; /*!< Le numero de la Tuile */

        /*! \brief Constructeur de la classe
            \param[in] str Identifiant de la Tuile
        */
        IdentificateurTuile(const string& str);

        /*! \brief Destructeur de la classe */
        ~IdentificateurTuile()=default;

        /*!
            \brief Recupere l'extension a partir d'une chaine de caracteres
            \param[in] ext La chaine de caracteres representant l'extension d'une Tuile
            \return L'extension de la Tuile
        */
        extensions extractExtension(const string& ext);

        /*!
            \brief Recupere la specificite a partir d'une chaine de caracteres
            \param[in] spe La chaine de caracteres representant la specificite d'une Tuile
            \return La specificite de la Tuile
        */
        specificiteTuile extractSpecif(const string& spe);

    public:

        /*!
            \brief Recupere l'identifiant de la Tuile
            \return Identifiant de la Tuile
        */
        const string& getStringId() const { return idString; }

        /*!
            \brief Recupere l'extension a laquelle appartient la tuile
            \return Extension de la Tuile
        */
        const extensions& getExtension() const { return idExtension; }

        /*!
            \brief Recupere la specificite de la Tuile
            \return Specificite de la Tuile
        */
        const specificiteTuile& getSpecificite() const { return specif; }

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

        static const size_t NB_ENV_COL = 7; /*!< Nombre d'environnements sur une colonne */
        static const size_t NB_ENV_LIGNE = 7; /*!< Nombre d'environnements sur une ligne */
        static constexpr size_t NB_ZONES = NB_ENV_COL * NB_ENV_LIGNE; /*!< Nombre de zones sur une Tuile */
        static const size_t NB_ZONES_BORDURE = 5; /*!< Nombre de zones en bordure d'une Tuile */
        static const string TUILE_VIDE_STR; /*!< Represente une Tuile vide sous forme de chaine de caracteres */

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
            \brief Recupere les NB_ZONES_BORDURE environnements sur une bordure de la Tuile
            \param[in] d La zone que l'on recupere dans la tuile
            \return Un tableau contenant des pointeurs sur les environnements adjacents
        */
        array<Environnement*, NB_ZONES_BORDURE> getEnvironnementsDansUneZone(const zoneTuile& d) const;

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

        /*!
            \brief Fusionne les environnements adjacents a un environnement specifique
            \param[in] x Coordonnee en x de l'environnement a fusionner
            \param[in] y Coordonnee en y de l'environnement a fusionner
            \param[in,out] envDiff Pointeur sur l'environnement qui fusionne
        */
        void fusionnerEnvironnementsAdjacents(int x, int y, Environnement* envDiff) {
            Coordonnees* parcours = new Coordonnees();

            fusionnerEnvironnementsAdjacentsRec(x, y, envDiff, parcours);

            delete parcours;
        }

    private:

        /*!
            \brief Fusionne les environnements adjacents a un environnement specifique recursivement
            \param[in] x Coordonnee en x de l'environnement a fusionner
            \param[in] y Coordonnee en y de l'environnement a fusionner
            \param[in,out] envDiff Pointeur sur l'environnement qui fusionne
            \param[in,out] parcours Pointeur sur les coordonnees deja parcourues
        */
        void fusionnerEnvironnementsAdjacentsRec(int x, int y, Environnement* envDiff, Coordonnees* parcours);

        /*!
            \brief Fait la fusion interne des environnements de la Tuile (les environnements adjacents)
        */
        void fusionnerEnvironnementsInternes();

    };

}

#endif
