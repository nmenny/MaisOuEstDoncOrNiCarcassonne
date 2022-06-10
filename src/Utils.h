/*! \file Utils.h
    \version 0.1
*/

#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    using namespace std;

    /*!
        \brief Separe une chaine de caracteres selon par rapport a un certain separateur
        \param[in] chaine Chaine de caracteres a separer
        \param[in] sep Caractere de separation dans la chaine
        \return Vecteur de chaines de caracteres contenant les differents champs de la chaine qui etaient separes par sep
    */
    vector<string> splitString(const string& chaine, const char& sep);

    /*!
        \brief Converti une chaine de caracteres en minuscule
        \param[in] str Chaine a convertir en minuscule
        \return La chaine passee en argument en minuscule
    */
    string toLowerCase(const string& str);

}

#endif // __UTILS_H__
