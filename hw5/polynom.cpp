#include "polynom.h"
#include <algorithm>

polynom::polynom(int n, int* coefs) :
    n_(n),
    coefs_(new int[n + 1])
{
    for (int i = 0; i < n; i++)
    {
        coefs_[i] = coefs[i];
    }
}

polynom::polynom(const polynom& other) :
    n_(other.n_),
    coefs_(new int[other.n_ + 1])
{
    for (int i = 0; i < other.n_; i++)
    {
        coefs_[i] = other.coefs_[i];
    }
}

polynom::~polynom()
{
    delete[] coefs_;
}

void polynom::print(ostream& os) const
{
    printcoefs(os); //TODO
}

int polynom::apply(int x) const
{
    int sum = coefs_[n_ - 1];
    for (int i = n_ - 2; i >= 0; --i)
    {
        sum = x*sum + coefs_[i];
    }

    return sum;
}

polynom polynom::add(const polynom& rhs, int sign) const
{
    int newOrder = std::max(n_, rhs.n_);

    int* newCoefs = new int[newOrder + 1];
    for (int i = 0; i < newOrder; i++)
    {
        newCoefs[i] = coefs_[i] + sign*rhs.coefs_[i];
    }

    return polynom(newOrder, newCoefs);
}

polynom& polynom::operator=(const polynom& rhs)
{
    if(&rhs != this) // handle self-assignment
    {
        delete[] coefs_;

        n_ = rhs.n_;
        for (int i = 0; i < n_; i++)
        {
            coefs_[i] = rhs.coefs_[i];
        }
    }

    return *this;
}

polynom polynom::operator+(const polynom& rhs) const
{
    return add(rhs, 1);
}

polynom polynom::operator-(const polynom& rhs) const
{
    return add(rhs, -1);
}

polynom polynom::operator*(const polynom& rhs) const
{
    int newOrder = n_ + rhs.n_;

    int* newCoefs = new int[newOrder + 1];
    for (int i = 0; i < n_; i++)
    {
        for (int j = 0; j < rhs.n_; j++)
        {
            newCoefs[i + j] = coefs_[i] * rhs.coefs_[j];
        }
    }

    return polynom(newOrder, newCoefs);
}

void polynom::printcoefs(ostream& os)  const {
    int allZero = 1;
    for (int i = n_; i >= 0; i--) {
        if (coefs_[i] > 0) {
            allZero = 0;
            if (i != n_) {
                os << "+";
            }
            if (coefs_[i] != 1 || i == 0) {
                os << coefs_[i];
            }
            if (i > 0) {
                os << "x";
                if (i > 1)
                    os << "^" << i;
            }
        }
        else if (coefs_[i] < 0) {
            allZero = 0;
            if (coefs_[i] != -1 || i == 0) {
                os << coefs_[i];
            }
            else
                os << "-";
            if (i > 0) {
                os << "x";
                if (i > 1)
                    os << "^" << i;
            }
        }
        else if (i == 0 && allZero == 1) { //zero polynom
            os << "0";
            continue;
        }
    }
}
