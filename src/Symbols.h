/*! \file Symbols.h
    \version 0.1
    \brief Definis dans le fichier csv representant une les differents elements de decors presents sur une tuile
*/

#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    enum class idTypesVilles {CLASSIQUE = 0, AVEC_BOUCLIER = 1, AVEC_CATHEDRALE = 2};

    //Cas Particuliers
    const char C_COIN = '@';
    const char C_BOUCLIER = 'B';

    //Surfaces
    const char C_PRES = '#'; /*!< Caractere representant un pre */
    const char C_VILLE = 'V'; /*!< Caractere representant une ville */

    //Batiments
    const char C_ABBAYE = 'A'; /*!< Caractere representant une abbaye */
    const char C_JARDIN = 'J'; /*!< Caractere representant un jardin */
    const char C_AUBERGE = 'L';
    const char C_CATHEDRALE = 'T';

    //Chemins
    const char C_ROUTE = 'C'; /*!< Caractere representant une route */
    const char C_RIVIERE = 'R'; /*!< Caractere representant une riviere */
}


#endif
