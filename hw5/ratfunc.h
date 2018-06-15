#ifndef __RATFUNC_H__
#define __RATFUNC_H__

#include "func.h"
#include "polynom.h"

using namespace std;

class ratfunc : public func {
public:
    ratfunc(const polynom& p, const polynom& q);

    ratfunc operator+(const ratfunc& rhs) const;
    ratfunc operator-(const ratfunc& rhs) const;
    ratfunc operator*(const ratfunc& rhs) const;
    ratfunc operator/(const ratfunc& rhs) const;

    ratfunc Derivative() const;

    void printRat(ostream& os) const;

protected:

    int apply(int) const;
    void print(ostream& os) const;

    ratfunc add(const ratfunc& rhs, int sign) const;

    const polynom p_;
    const polynom q_;

private:
    func* clone() const;
};


#endif
 
