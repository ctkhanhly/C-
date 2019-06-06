
#include "Rational.h"
#include <iostream>
#include <string>
using namespace std;

namespace CS2124{
    //gcd has to be in cpp not in .h
    int gcd(int a, int b){
        while (b != 0) {//when two numbers are equal, a%b = b = 0
            int temp = a % b;
            a = b;
            b = temp;
        }
        return a;

    }
    istream& operator>>(istream& ifs, Rational& num){
        char slash;
        ifs >> num.numerator >> slash >> num.denumerator;
        num.normalize();
        return ifs;
    }
    ostream& operator<<(ostream& os, const Rational& num){ 
        if(num.denumerator == 1 || num.numerator == 0){
            os <<  num.numerator ;
        }else if(num.denumerator > 1){
            os << num.numerator << "/" << num.denumerator;
        }
        return os;
    }
    void Rational::normalize(){
        if(denumerator < 0){
            denumerator = -denumerator;
            numerator = -numerator;
        }
        int gCDivisor = gcd(abs(denumerator), abs(numerator));
        numerator /= gCDivisor;
        denumerator /= gCDivisor;
    }
    Rational::Rational(int numerator, int denumerator):numerator(numerator), denumerator(denumerator){
        normalize();
    }
    Rational& Rational::operator+=(const Rational& otherNum){
        if(this->denumerator == otherNum.denumerator){
            this->numerator += otherNum.numerator;
        }
        else{
            this->numerator = this->numerator * otherNum.denumerator + otherNum.numerator * this->denumerator;
            this->denumerator *= otherNum.denumerator;
            normalize();
        }
        return *this;
    }
    Rational& Rational::operator++(){
        numerator += denumerator;
        normalize();
        return *this;
    }
    Rational::operator bool() const{
        return (numerator == 0);
    }
    bool operator==(const Rational& lhs, const Rational& rhs){
        return lhs.numerator == rhs.numerator && lhs.denumerator == rhs.denumerator;
    }
    Rational operator+(const Rational& lhs, const Rational& rhs){ 
        Rational result;
        result += lhs;
        result += rhs;
        return result;
    }
    Rational Rational::operator++(int dummy){
        Rational result = *this; 
        numerator += denumerator; 
        normalize();
        return result;
    }

    bool operator!=(const Rational& lhs, const Rational& rhs){
        return !(lhs == rhs);
    }
    bool operator<(const Rational& lhs, const Rational& rhs){
        return lhs.numerator/lhs.denumerator < rhs.numerator/rhs.denumerator;
    }
    bool operator<=(const Rational& lhs, const Rational& rhs){
        return lhs < rhs || lhs == rhs;
    }
    bool operator>(const Rational& lhs, const Rational& rhs){
        return rhs < lhs;
    }
    bool operator>=(const Rational& lhs, const Rational& rhs){
        return rhs > lhs || lhs == rhs;
    }
    Rational& operator--(Rational& num){
        return num += (-1); 
    }
    Rational operator--(Rational& num, int dummy){
        Rational result = num;
        num += (-1); 
        return result;
    }


}

