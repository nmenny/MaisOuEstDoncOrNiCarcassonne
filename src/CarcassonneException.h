/*! \file CarcassonneException.h
    \version 0.1
*/

#ifndef __CARCASSONNEEXCEPTION_H___
#define __CARCASSONNEEXCEPTION_H___

#include <string>
#include <exception>

/*! \namespace Carcassonne

    espace de nom regroupant tout ce qui est utilise pour le jeu
*/
namespace Carcassonne {

    using namespace std;

    /*! \class CarcassonneException
        \brief Regroupe toutes les exceptions du jeu
    */
    class CarcassonneException : public exception {
        string info; /*!< chaine de caracteres representant l'erreur ayant declenche l'exception */
	public:

	    /*! \brief Constructeur de la classe
            \param[in] msg Message lie a l'exception
        */
	    CarcassonneException(const string msg) : info(msg) {}

	    /*! \brief Destructeur de la classe */
	    virtual ~CarcassonneException()=default;

	    /*! \brief Donne le message expliquant l'exception
            \return Message lie a l'exception
        */
	    const char* what() const noexcept override { return info.c_str(); }
    };

    /*! \class JoueurException
        \brief Exceptions declenchees par les joueurs
    */
    class JoueurException : public CarcassonneException {
    public:

        /*! \brief Constructeur de la classe
            \param[in] msg Message lie a l'exception
        */
        JoueurException(const string msg) : CarcassonneException(msg) {}
    };

    /*! \class MemoireException
        \brief Exceptions declenchees par les gestionnaires memoire
    */
    class MemoireException : public CarcassonneException {
    public:

        /*! \brief Constructeur de la classe
            \param[in] msg Message lie a l'exception
        */
        MemoireException(const string msg) : CarcassonneException(msg) {}
    };

    /*! \class PiocheException
        \brief Exceptions declenchees par la Pioche
    */
    class PiocheException : public CarcassonneException {
    public:

        /*! \brief Constructeur de la classe
            \param[in] msg Message lie a l'exception
        */
        PiocheException(const string msg) : CarcassonneException(msg) {}
    };

    /*! \class TuileException
        \brief Exceptions declenchees par les Tuiles
    */
    class TuileException : public CarcassonneException {
    public:

        /*! \brief Constructeur de la classe
            \param[in] msg Message lie a l'exception
        */
        TuileException(const string msg) : CarcassonneException(msg) {}
    };

    /*! \class PlateauException
        \brief Exceptions declenchees par le Plateau
    */
    class PlateauException : public CarcassonneException {
    public:

        /*! \brief Constructeur de la classe
            \param[in] msg Message lie a l'exception
        */
        PlateauException(const string msg) : CarcassonneException(msg) {}
    };

    /*! \class InterfaceException
        \brief Exceptions declenchees par l'interface
    */
    class InterfaceException : public CarcassonneException {
    public:

        /*! \brief Constructeur de la classe
            \param[in] msg Message lie a l'exception
        */
        InterfaceException(const string msg) : CarcassonneException(msg) {}
    };

}

#endif
