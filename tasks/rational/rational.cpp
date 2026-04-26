#include "rational.h"

void Rational::set(int64_t numer, int64_t denom)
{
    if(denom == 0)
        throw RationalDivisionByZero{};
    if(denom < 0)
    {
        numer = -numer;
        denom = -denom;
    }
    int64_t gcd = std::gcd(numer, denom);
    numer_ = numer / gcd;
    denom_ = denom / gcd;
}

Rational::Rational(): numer_(0), denom_(1) {}
Rational::Rational(int value): numer_(value), denom_(1) {}
Rational::Rational(int numer, int denom) { set(numer, denom); }

int Rational::getNumerator() const { return numer_; }
int Rational::getDenominator() const { return denom_; }

void Rational::setNumerator(int value) { set(value, denom_); }
void Rational::setDenominator(int value) { set(numer_, value); }

Rational& operator+=(Rational& lhs, const Rational& rhs)
{
    int newDenom = lhs.denom_ * rhs.denom_;
    int newNumer = lhs.numer_ * rhs.denom_ + rhs.numer_ * lhs.denom_;
    lhs.set(newNumer, newDenom);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs)
{
    int newDenom = lhs.denom_ * rhs.denom_;
    int newNumer = lhs.numer_ * rhs.numer_;
    lhs.set(newNumer, newDenom);
    return lhs;
}

Rational& operator++(Rational& ratio)
{
    int newNumer = ratio.numer_ + ratio.denom_;
    ratio.set(newNumer, ratio.denom_);
    return ratio;
}

Rational& operator--(Rational& ratio)
{
    int newNumer = ratio.numer_ - ratio.denom_;
    ratio.set(newNumer, ratio.denom_);
    return ratio;
}

std::istream& operator>>(std::istream& ist, Rational& ratio)
{
    int numer;
    int denom;
    char slash;
    ist >> numer >> slash >> denom;
    ratio.set(numer, denom);
    return ist;
}

Rational operator+(const Rational& ratio) { return ratio; }

Rational operator-(const Rational& ratio)
{
    return Rational(-ratio.getNumerator(), ratio.getDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs)
{
    int64_t newDenom = lhs.getDenominator() * rhs.getDenominator();
    int64_t newNumer = lhs.getNumerator() * rhs.getDenominator() -
                       rhs.getNumerator() * lhs.getDenominator();
    lhs.setDenominator(newDenom);
    lhs.setNumerator(newNumer);
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs)
{
    if(rhs.getNumerator() == 0)
        throw RationalDivisionByZero{};
    int64_t newDenom = lhs.getDenominator() * rhs.getNumerator();
    int64_t newNumer = lhs.getNumerator() * rhs.getDenominator();
    lhs.setDenominator(newDenom);
    lhs.setNumerator(newNumer);
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
    Rational result = lhs;
    result += rhs;
    return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
    Rational result = lhs;
    result -= rhs;
    return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    Rational result = lhs;
    result *= rhs;
    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
    Rational result = lhs;
    result /= rhs;
    return result;
}

Rational operator++(Rational& ratio, int)
{
    Rational result = ratio;
    ++ratio;
    return result;
}

Rational operator--(Rational& ratio, int)
{
    Rational result = ratio;
    --ratio;
    return result;
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
    return lhs.getNumerator() * rhs.getDenominator() <
           rhs.getNumerator() * lhs.getDenominator();
}

bool operator>(const Rational& lhs, const Rational& rhs)
{
    return lhs.getNumerator() * rhs.getDenominator() >
           rhs.getNumerator() * lhs.getDenominator();
}

bool operator<=(const Rational& lhs, const Rational& rhs)
{
    return lhs.getNumerator() * rhs.getDenominator() <=
           rhs.getNumerator() * lhs.getDenominator();
}

bool operator>=(const Rational& lhs, const Rational& rhs)
{
    return lhs.getNumerator() * rhs.getDenominator() >=
           rhs.getNumerator() * lhs.getDenominator();
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
    return lhs.getNumerator() == rhs.getNumerator() &&
           lhs.getDenominator() == rhs.getDenominator();
}

bool operator!=(const Rational& lhs, const Rational& rhs)
{
    return lhs.getNumerator() != rhs.getNumerator() ||
           lhs.getDenominator() != rhs.getDenominator();
}

std::ostream& operator<<(std::ostream& ost, const Rational& ratio)
{
    if(ratio.getDenominator() == 1)
        ost << ratio.getNumerator();
    else
        ost << ratio.getNumerator() << '/' << ratio.getDenominator();
    return ost;
}
