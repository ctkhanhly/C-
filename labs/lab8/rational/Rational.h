#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <string>
//using namespace std; // need to qualify everything 

namespace CS2124{

    class Rational{
        friend std::ostream& operator<<(std::ostream& os, const Rational& num);
        friend bool operator==(const Rational& lhs, const Rational& rhs);
        friend bool operator<(const Rational& lhs, const Rational& rhs);
        friend std::istream& operator>>(std::istream& ifs, Rational& num);

        void normalize();
        
    private:
        int numerator;
        int denumerator;
    public:
        Rational(int numerator = 0, int denumerator = 1);
        Rational& operator+=(const Rational& otherNum);
        Rational& operator++();
        Rational operator++(int dummy);
        explicit operator bool() const;
    };
    Rational operator+(const Rational& lhs, const Rational& rhs);
    bool operator!=(const Rational& lhs, const Rational& rhs);
    bool operator<(const Rational& lhs, const Rational& rhs);
    bool operator<=(const Rational& lhs, const Rational& rhs);
    bool operator>(const Rational& lhs, const Rational& rhs);
    bool operator>=(const Rational& lhs, const Rational& rhs);
    Rational& operator--(Rational& num);
    Rational operator--(Rational& num, int dummy);
    int gcd(int a, int b);
}


#endif
