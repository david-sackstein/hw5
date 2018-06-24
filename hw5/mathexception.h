#ifndef __MATHEXCEPTION_H__
#define __MATHEXCEPTION_H__

#include <exception>
#include <ostream>

using namespace std;

class mathexception : public std::exception {
public:
    mathexception(const char* msg);

    virtual ~mathexception() throw() {}

    const char* what() const throw();

protected:

    string msg_;
};


#endif

