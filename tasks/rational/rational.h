#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <cstdint>
#include <iostream>
#include <numeric>
#include <stdexcept>

class RationalDivisionByZero: public std::runtime_error
{
public:
    RationalDivisionByZero(): std::runtime_error("RationalDivisionByZero") {}
};

class Rational
{
public:
    Rational();

    Rational(int value);  // NOLINT

    Rational(int numer, int denom);

    int getNumerator() const;

    int getDenominator() const;

    void setNumerator(int value);

    void setDenominator(int value);

    friend Rational& operator+=(Rational& lhs, const Rational& rhs);

    friend Rational& operator*=(Rational& lhs, const Rational& rhs);

    friend Rational& operator++(Rational& ratio);  // faster than += 1

    friend Rational& operator--(Rational& ratio);

    friend std::istream& operator>>(std::istream& ist, Rational& ratio);

private:
    void set(int64_t numer, int64_t denom);

    int numer_;
    int denom_;
};

Rational operator+(const Rational& ratio);

Rational operator-(const Rational& ratio);

Rational& operator-=(Rational& lhs, const Rational& rhs);

Rational& operator/=(Rational& lhs, const Rational& rhs);

Rational operator+(const Rational& lhs, const Rational& rhs);

Rational operator-(const Rational& lhs, const Rational& rhs);

Rational operator*(const Rational& lhs, const Rational& rhs);

Rational operator/(const Rational& lhs, const Rational& rhs);

Rational operator++(Rational& ratio, int);

Rational operator--(Rational& ratio, int);

bool operator<(const Rational& lhs, const Rational& rhs);

bool operator>(const Rational& lhs, const Rational& rhs);

bool operator<=(const Rational& lhs, const Rational& rhs);

bool operator>=(const Rational& lhs, const Rational& rhs);

bool operator==(const Rational& lhs, const Rational& rhs);

bool operator!=(const Rational& lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& ost, const Rational& ratio);

#endif  // RATIONAL_H_

