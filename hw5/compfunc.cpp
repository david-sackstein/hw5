#include "compfunc.h"
#include <algorithm>

compfunc::compfunc(const func& q, const func& p) :
    q_(q.clone()),
    p_(p.clone())
{
}

compfunc::compfunc(const compfunc& other) :
    q_(other.q_->clone()),
    p_(other.p_->clone())
{
}

compfunc::~compfunc()
{
    delete p_;
    delete q_;
}

compfunc& compfunc::operator=(const compfunc& rhs)
{
    if (&rhs != this) // handle self-assignment
    {
        delete p_;
        delete q_;

        q_ = rhs.q_->clone();
        p_ = rhs.p_->clone();
    }

    return *this;
}

void compfunc::print(ostream& os) const
{
    //p_.plot(os);
    //os << "/";
    //q_.printcoefs(os);
    //TODO
}

int compfunc::apply(int x) const
{
    return q_->apply(p_->apply(x));
}

func* compfunc::clone() const
{
    return new compfunc(*this);
}