#include <iostream>
#include <string>
using namespace std;

int gcd(int a, int b){
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;

}
class Rational{
    friend ostream& operator<<(ostream& os, const Rational& num);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    friend istream& operator>>(istream& ifs, Rational& num);

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
Rational& Rational::operator+=(const Rational& otherNum){//*****
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
Rational Rational::operator++(int dummy){//no ref return type for local variable
    Rational result = *this; 
    numerator += denumerator; //+=1 too 
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

int main(){
    Rational twoThirds(2,3);
    cout << twoThirds << endl;
    
    Rational a, b;
    cout << "Input a rational Rational, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input as rational Rational, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;//*****
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;//*****
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?

    // cout << "a-- -- = " << (a-- --) << endl; //not supposed to work: return local, takes in ref
    // cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 
}