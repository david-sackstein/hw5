#include "ratfunc.h"
#include <algorithm>

ratfunc::ratfunc(const polynom& p, const polynom& q) :
    p_(p),
    q_(q)
{
}

void ratfunc::print(ostream& os) const
{
    p_.printcoefs(os);
    os << "/";
    q_.printcoefs(os);
    //TODO
}

int ratfunc::apply(int x) const
{
    return q_.apply(x)/p_.apply(x);
}

ratfunc ratfunc::add(const ratfunc& rhs, int sign) const
{
    //TODO
    return *this;
}

ratfunc ratfunc::operator+(const ratfunc& rhs) const
{
    return add(rhs, 1);
}

ratfunc ratfunc::operator-(const ratfunc& rhs) const
{
    return add(rhs, -1);
}

ratfunc ratfunc::operator*(const ratfunc& rhs) const
{
    //TODO
    return *this;
}

ratfunc ratfunc::operator/(const ratfunc& rhs) const
{
    //TODO
    return *this;
}

func* ratfunc::clone() const
{
    return new ratfunc(*this);
}
