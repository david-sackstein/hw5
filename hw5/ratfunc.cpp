#include "ratfunc.h"
#include <algorithm>
#include "mathexception.h"

ratfunc::ratfunc(const polynom& p, const polynom& q) :
    p_(p),
    q_(q)
{
}

int ratfunc::apply(int x) const
{
    if (p_.apply(x) != 0)
    {
        return q_.apply(x) / p_.apply(x);
    }

    throw mathexception ("divide by zero");
}

ratfunc ratfunc::add(const ratfunc& rhs, int sign) const
{
    return ratfunc(q_*rhs.p_ + p_*rhs.q_, p_ * q_);
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
    return ratfunc(q_*rhs.q_, p_*rhs.p_);
}

ratfunc ratfunc::operator/(const ratfunc& rhs) const
{
    return ratfunc(q_*rhs.p_, p_*rhs.q_);
}

ratfunc ratfunc::Derivative() const
{
    return ratfunc(p_.Derivative()*q_ - q_.Derivative()*p_, q_*q_);
}

void ratfunc::printRat(ostream& os) const
{
    p_.printcoefs(os);
    os << "/";
    q_.printcoefs(os);
}

void ratfunc::print(ostream& os) const
{
    printRat(os);

    os << "Derivative: ";
    Derivative().printRat(os);

    plot(os);
}

func* ratfunc::clone() const
{
    return new ratfunc(*this);
}
