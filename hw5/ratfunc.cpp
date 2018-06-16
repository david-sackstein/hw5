#include "ratfunc.h"
#include <algorithm>
#include "mathexception.h"
#include <iostream>//TODO

ratfunc::ratfunc(const polynom& p, const polynom& q) :
    p_(p),
    q_(q)
{
}

int ratfunc::apply(int x) const
{
    int denom = p_.apply(x);
    if (denom != 0)
    {
        return q_.apply(x) / denom;
    }
    //std::cout << denom << endl;

    throw mathexception ("divide by zero");
}

ratfunc ratfunc::add(const ratfunc& rhs, int sign) const
{
    return ratfunc(p_ * q_, q_*rhs.p_ + p_*rhs.q_);
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
    return ratfunc(p_*rhs.p_, q_*rhs.q_);
}

ratfunc ratfunc::operator/(const ratfunc& rhs) const
{
    return ratfunc(p_*rhs.q_, q_*rhs.p_);
}

ratfunc ratfunc::Derivative() const
{
    polynom num = q_.Derivative()*p_ - p_.Derivative()*q_;
    polynom den  = p_*p_;
    return ratfunc(den,num);
}

void ratfunc::printRat(ostream& os) const
{
    os << "(";
    q_.printcoefs(os);
    os << ")/(";
    p_.printcoefs(os);
    os << ")";
}

void ratfunc::print(ostream& os) const
{
    printRat(os);
    os << "\n";

    os << "Derivative: ";
    Derivative().printRat(os);
    os << "\n";
}

func* ratfunc::clone() const
{
    return new ratfunc(*this);
}
