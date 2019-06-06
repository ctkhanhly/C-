#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

struct Node{
    int coeff;
    Node* next; 
    Node(int coeff = 0, Node* next = nullptr): coeff(coeff), next(next){}
};

class Polynomial{
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    friend ostream& operator<<(ostream& os, const Polynomial& pol);
    
private:
    int degree;
    Node* headPtr;//
    void addHead(int coeff);
    void cleanup();
public:
    Polynomial();
    Polynomial(const vector<int>& vec);
    Polynomial(const Polynomial& other);
    ~Polynomial();
    Polynomial& operator=(const Polynomial& other);
    Polynomial& operator+=(const Polynomial& other);
    int evaluate(int val) const;
};

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    if(lhs.degree != rhs.degree) return false;
    Node* tracerThis = lhs.headPtr->next;
    Node* tracerOther = rhs.headPtr->next;
    while(tracerThis && tracerOther){
        if(tracerThis->coeff != tracerOther->coeff){
            return false;
        }
        tracerThis = tracerThis->next;
        tracerOther = tracerOther->next;
    }
    return true;
}

ostream& operator<<(ostream& os, const Polynomial& pol){
    Node* tracerThis = pol.headPtr->next;
    if(!pol.headPtr->next){
        os << '0';
        return os;
    }
    vector<int> coeffs;
    while(tracerThis){
        coeffs.push_back(tracerThis->coeff);
        tracerThis = tracerThis->next;
    }
    for(int i =  coeffs.size()-1; i >= 0; i--){
        if(i == 0){
            os << coeffs[i];
        } 
        else if(coeffs[i] == 0){
            continue;
        }
        else if(coeffs[i] == 1){
            os << "x + ";
        }
        else if(coeffs[i] == -1){
            os << "-x + ";
        }
        else if(i == 1){
            os << coeffs[i] << "x + ";
        }
        else{
            os << coeffs[i] << "x^" << i << " + ";
        }
    }
    return os;
}

void Polynomial::addHead(int coeff){
    headPtr = new Node(coeff, headPtr);
    degree++;
}
void Polynomial::cleanup(){
    int updatedDegree = 0;
    Node* tracer = headPtr->next;
    int count = 0;
    Node* tail = tracer;
    while(tracer){
        if(tracer->coeff != 0){
            updatedDegree = count;
            tail = tracer;
        }
        count ++;
        tracer = tracer->next;
    }
    Node* tracerTail = tail->next;
    tail->next = nullptr;
    while(tracerTail){
        Node* postTail = tail->next;
        delete tracerTail;
        tracerTail = nullptr;
        tracerTail = postTail;
    }
    degree = updatedDegree;
}
Polynomial::Polynomial():headPtr(new Node()), degree(0){}
Polynomial::Polynomial(const vector<int>& vec):  degree(0), headPtr(new Node(0)){
    for(size_t i = 0; i < vec.size(); i++){
        addHead(vec[i]);
    }
    addHead(0);
    cleanup();
}
Polynomial::Polynomial(const Polynomial& other): degree(other.degree), headPtr(new Node(0)){
    Node* tracerOther = other.headPtr;
    Node* tracerThis = headPtr;
    while(tracerOther->next){
        tracerThis->next = new Node(tracerOther->next->coeff);
        tracerThis = tracerThis->next;
        tracerOther = tracerOther -> next;
    } 
}
Polynomial::~Polynomial(){
    while(headPtr){
        Node* postThis = headPtr->next;
        delete headPtr;
        //headPtr = nullptr;
        headPtr = postThis;
    }
}
Polynomial& Polynomial::operator=(const Polynomial& other){
    if(this != &other){
        Node* tracerThis = headPtr;
        while(headPtr){
            Node* postThis = headPtr->next;
            delete headPtr;
            headPtr = nullptr;
            headPtr = postThis;
        }
        degree = other.degree;
        headPtr = new Node(other.headPtr->coeff);
        Node* tracerOther = other.headPtr;
        tracerThis = headPtr;
        while(tracerOther->next){
            tracerThis->next = new Node(tracerOther->next->coeff);
            tracerThis = tracerThis->next;
            tracerOther = tracerOther->next;
        }
    }
    return *this;
}
Polynomial& Polynomial::operator+=(const Polynomial& other){
    Node* tracerThis = headPtr->next;
    Node* tracerOther = other.headPtr->next;
    Node* tracerTail = headPtr;
    while(tracerThis && tracerOther){
        tracerTail = tracerThis;
        tracerThis->coeff = tracerThis->coeff + tracerOther->coeff;
        tracerThis = tracerThis->next;
        tracerOther = tracerOther->next;
    }
    while(tracerOther){
        tracerTail->next = new Node(tracerOther->coeff);
        tracerTail = tracerTail->next;
        tracerOther = tracerOther->next;
    }
    cleanup();
    return *this;
}
int Polynomial::evaluate(int val) const {
    int count = degree;
    Node* tracerThis = headPtr->next;
    int result = 0;
    while(tracerThis){
        result += (tracerThis->coeff)* pow(val, degree-count);
        tracerThis = tracerThis->next;
        --count;
    }
    return result;
}
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial result ;
    result += lhs;
    result+= rhs;
    return result;
} 
bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs==rhs);
}

void doNothing(Polynomial temp) {}

int main() {
	
    //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -1x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7
    //Polynomial p6;
    // p6=p4;
    // cout << boolalpha;
    // //cout << p4==p6 << endl;
    // cout << (p4==p6) << endl;

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;
    cout << "p2 + p3: " << (p2+p3) << endl; 
    cout << "p2 + p4: " << (p2+p4) << endl; 
    cout << "p4 + p2: " << (p4+p2) << endl;


    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;  
    cout << "p5: " << p5 << endl;  

    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
	
    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

	/*=================================================================
	NEW TEST CODE - test if cleaning the leading 0s
	===================================================================*/

	Polynomial p8({ 1, 1 });
	Polynomial p9({ -1, 1 });
	Polynomial p10({ 0, 0, 2 });
	//p8 + p9 tests if += does the cleanup()
	//p10 tests if constructor does the cleanup()
	cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;


}


