#include <iostream>
#include <string>
#include <vector>
using namespace std;

// int gcd(int a, int b){
//         int smallerNum = min(a,b);
//         int biggerNum = max(a,b);
        
//         int gdivisor = 1;
//         if(smallerNum == 0){
//             cout << "gcd: " << gdivisor << endl;
//             return gdivisor;
//         }
//         for(int i = smallerNum; i * i >= smallerNum; i--){
//             int complementFactor = smallerNum / i;
//             if(smallerNum % i == 0){
//                 if(biggerNum % i == 0){
//                     gdivisor = i;
//                     cout << "gcd: " << gdivisor << endl;
//                     return abs(gdivisor);
//                 }else if(biggerNum % complementFactor == 0 && complementFactor != 1){
//                     gdivisor = complementFactor;
//                     cout << "gcd: " << complementFactor << endl;
//                     return abs(complementFactor);
//                 } 
//             }
//         }
//         cout << "gcd: " << gdivisor << endl;
//         return abs(gdivisor);
//     }

int gcd(int a, int b){
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;

}
class Number{
    friend ostream& operator<<(ostream& os, const Number& num);//Need const here!!!
    friend bool operator==(const Number& lhs, const Number& rhs);//const!!!!
    friend bool operator<(const Number& lhs, const Number& rhs);

    friend istream& operator>>(istream& ifs, Number& num){//friend = non-member
        char slash;
        ifs >> num.numerator >> slash >> num.denumerator;
        num.normalize();
        return ifs;
    }

    void normalize(){
        if((denumerator < 0 && numerator < 0) || denumerator < 0){
            this->denumerator = -this->denumerator;
            this->numerator = -this->numerator;
        }
        int gCDivisor = abs(gcd(denumerator, numerator));
        numerator /= gCDivisor;
        denumerator /= gCDivisor;
    }
    
private:
    int numerator;
    int denumerator;
public:
    Number(int numerator = 0, int denumerator = 1):numerator(numerator), denumerator(denumerator){
        normalize(); // 1 parameter -> change numerator only
    }
    Number& operator+=(const Number& otherNum){//*****
        if(this->denumerator == otherNum.denumerator){
            this->numerator += otherNum.numerator;
        }
        else{
            this->numerator = this->numerator * otherNum.denumerator + otherNum.numerator * this->denumerator;
            this->denumerator *= otherNum.denumerator;
        }
        //cout  << "+=: " << *this << endl;
        normalize();
        return *this;
    }
    
    Number& operator++(){
        if(denumerator == 1){
            numerator += 1;
        }
        else if(numerator != 1 && denumerator != 1){
            numerator += denumerator;
            normalize();
        }
        return *this;
    }
    Number operator++(int dummy){//no ref return type for local variable
        Number result = *this;
        if(denumerator == 1){
            numerator += 1;
        }
        else if(numerator != 1 && denumerator != 1){
            numerator += denumerator;
            normalize();
        }
        return result;
    }
    explicit operator bool() const{
        if(numerator == 0){
            return false;
        }
        return true;
    }
//     Member for ++
// Non-member, non-friend for --

};

ostream& operator<<(ostream& os, const Number& num){ //****
    if(abs(num.numerator) > 1 && num.denumerator > 1){
        os << num.numerator << "/" << num.denumerator;
    }
    else if(num.denumerator == 1){
        os <<  num.numerator ;
    }
    return os;
}
bool operator==(const Number& lhs, const Number& rhs){
    return lhs.numerator == rhs.numerator && lhs.denumerator == rhs.denumerator;
}
Number operator+(const Number& lhs, const Number& rhs){ //*****
    //return lhs+=rhs; --- WRONG: dont want to change lhs, rhs
    Number result;
    //cout << result << endl;
    result += lhs;
    //cout << result << endl;
    result += rhs;
    //cout << "\nhi: "   << lhs << " " << rhs << " " << result << endl;
    return result;
}


bool operator!=(const Number& lhs, const Number& rhs){
     return !(lhs == rhs);
}
bool operator<(const Number& lhs, const Number& rhs){
    return lhs.numerator/lhs.denumerator < rhs.numerator/rhs.denumerator;
}
bool operator<=(const Number& lhs, const Number& rhs){
    return lhs < rhs || lhs == rhs;
}
bool operator>(const Number& lhs, const Number& rhs){
    return rhs < lhs;
}
bool operator>=(const Number& lhs, const Number& rhs){
    return rhs > lhs || lhs == rhs;
}
Number& operator--(Number& num){
    return num += (-1); //compiler automatically converts -1 to Number
}
Number operator--(Number& num, int dummy){
    Number result = num;
    num += (-1); //compiler automatically converts -1 to Number
    return result;
}

int main(){
    //cout << gcd(7,3) << endl;
    Number twoThirds(2,3);
    cout << twoThirds << endl;
    
    Number a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Number one = 1;

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
    if (Number(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Number(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 
}