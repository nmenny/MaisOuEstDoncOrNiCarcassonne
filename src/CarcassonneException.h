#ifndef __CARCASSONNEEXCEPTION_H___
#define __CARCASSONNEEXCEPTION_H___

#include <string>
#include <exception>

namespace Carcassonne {

    using namespace std;

    class CarcassonneException : public exception {
        string info;
	public:
	    CarcassonneException(const string msg) : info(msg) {}
	    virtual ~CarcassonneException()=default;
	    const char* what() const noexcept override { return info.c_str(); }
    };

    class JoueurException : public CarcassonneException {
    public:
        JoueurException(const string msg) : CarcassonneException(msg) {}
    };

    class PiocheException : public CarcassonneException {
    public:
        PiocheException(const string msg) : CarcassonneException(msg) {}
    };

    class TuileException : public CarcassonneException {
    public:
        TuileException(const string msg) : CarcassonneException(msg) {}
    };

    class PlateauException : public CarcassonneException {
    public:
        PlateauException(const string msg) : CarcassonneException(msg) {}
    };

}

#endif
