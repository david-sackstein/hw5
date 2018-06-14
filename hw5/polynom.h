#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include "func.h"

using namespace std;


class polynom : public func {
public:

    polynom(int n, int* coefs);
    polynom(const polynom& other);
    ~polynom();
    polynom& operator=(const polynom& rhs);

    polynom operator+(const polynom& rhs) const;
    polynom operator-(const polynom& rhs) const;
    polynom polynom::operator*(const polynom& rhs) const;

    int apply(int) const;
    void printcoefs(ostream&)  const;

protected:

    void print(ostream& os) const;

    polynom add(const polynom& rhs, int sign) const;

    int n_; //order of the polynom
    int* coefs_; //coefficients 
};



#endif

