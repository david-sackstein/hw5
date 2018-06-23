#include "polynom.h"
#include <algorithm>

polynom::polynom(int n, int* coefs) :
	n_(n),
	coefs_(new int[n + 1])
{
	for (int i = 0; i < n + 1; i++)
	{
		coefs_[i] = coefs[i];
	}
}

polynom::polynom(const polynom& other) :
	n_(other.n_),
	coefs_(new int[other.n_ + 1])
{
	for (int i = 0; i < other.n_ + 1; i++)
	{
		coefs_[i] = other.coefs_[i];
	}
}

polynom::~polynom()
{
	delete[] coefs_;
}

int polynom::apply(int x) const
{
	int sum = coefs_[n_];
	for (int i = n_ - 1; i >= 0; --i)
	{
		sum = x * sum + coefs_[i];
	}

	return sum;
}

polynom polynom::add(const polynom& rhs, int sign) const
{
	int newOrder = std::max(n_, rhs.n_);
	int minOrder = n_ + rhs.n_ - newOrder;

	int* newCoefs = new int[newOrder + 1]; // poly of order A has A+1 coefs
	for (int i = 0; i < newOrder + 1; i++)
	{
		if (i < minOrder + 1)
		{
			newCoefs[i] = coefs_[i] + sign * rhs.coefs_[i];
		}
		else if (i > rhs.n_ + 1)
		{
			newCoefs[i] = coefs_[i];
		}
		else
		{
			newCoefs[i] = sign * rhs.coefs_[i];
		}
	}

	polynom poly = polynom(newOrder, newCoefs);
	delete[] newCoefs;

	poly.updateOrder();
	return poly;
}

polynom& polynom::operator=(const polynom& rhs)
{
	if (&rhs != this) // handle self-assignment
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

void polynom::updateOrder()
{
	int i = n_;
	while ((coefs_[i] == 0) && (i >= 0))
	{
		--i;
	}

	n_ = i;
}

bool polynom::isZero() const
{
	return n_ == 0 && coefs_[0] == 0;
}

polynom polynom::operator*(const polynom& rhs) const
{
	int newOrder;
	int* newCoefs;

	if (isZero() || rhs.isZero())
	{
		newOrder = 0;
		newCoefs = new int[1];
		newCoefs[0] = 0;
	}
	else
	{
		newOrder = n_ + rhs.n_;

		newCoefs = new int[newOrder + 1];
		for (int i = 0; i < newOrder + 1; i++)
		{
			newCoefs[i] = 0;
		}

		for (int i = 0; i < n_ + 1; i++)
		{
			for (int j = 0; j < rhs.n_ + 1; j++)
			{
				newCoefs[i + j] += coefs_[i] * rhs.coefs_[j];
			}
		}
	}

	polynom poly = polynom(newOrder, newCoefs);
	delete[] newCoefs;

	return poly;
}

polynom polynom::Derivative() const
{
	int newOrder = n_ == 0 ? 0 : n_ - 1;
	int* newCoefs = new int[newOrder + 1];

	if (n_ == 0) // derivative of const is const (zero)
	{
		newCoefs[0] = 0;
	}
	else
	{
		for (int i = 0; i < newOrder + 1; i++)
		{
			newCoefs[i] = (i + 1)*coefs_[i + 1];
		}
	}

	polynom poly = polynom(newOrder, newCoefs);
	delete[] newCoefs;

	return poly;
}

polynom polynom::Integral() const // TODO: check logically again
{
	int* newCoefs;
	int newOrder;

	if (n_ == 0 && coefs_[0] == 0)  // integral of zero is zero
	{
		newCoefs = new int[1];
		newCoefs[0] = 0;
		newOrder = 0;
	}
	else
	{
		newOrder = n_ + 1;

		newCoefs = new int[newOrder + 1];
		newCoefs[0] = 0; // Set C=0
		for (int i = 1; i < newOrder + 1; i++)
		{
			// Guaranteed: all coefs will be whole
			newCoefs[i] = coefs_[i - 1] / i;
		}
	}

	polynom poly = polynom(newOrder, newCoefs);
	delete[] newCoefs;

	return poly;
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

void polynom::print(ostream& os) const
{
	printcoefs(os);
	os << "\n";

	os << "Derivative: ";
	Derivative().printcoefs(os);
	os << "\n";

	os << "Integral: ";
	Integral().printcoefs(os);
	os << "+C";
	os << "\n";
}

func* polynom::clone() const
{
	return new polynom(*this);
}