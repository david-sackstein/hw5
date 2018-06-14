#ifndef __COMPFUNC_H__
#define __COMPFUNC_H__

#include "func.h"

using namespace std;

class compfunc : public func {
public:
    compfunc(const func& q, const func& p);

    compfunc operator+(const compfunc& rhs) const;
    compfunc operator-(const compfunc& rhs) const;
    compfunc compfunc::operator*(const compfunc& rhs) const;

protected:

    int apply(int) const;
    void print(ostream& os) const;
    compfunc add(const compfunc& rhs, int sign) const;

    const func& q_;
    const func& p_;

};

#endif
 
