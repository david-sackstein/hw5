#include "compfunc.h"
#include <algorithm>

compfunc::compfunc(const func& q, const func& p) :
    q_(q),
    p_(p)
{
    
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
    return q_.apply(p_.apply(x));
}
