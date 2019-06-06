#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;


class Polynomial{
    struct Node{
        int coeff;
        Node* next;    
        //header is nullptr
        //I didnt do anything in initialization list => fatal error
        //if i have 2 parameter, next won't get initialized? and degree too?
        //this is why in constructor of Polynomial, head kept being added with 2 parameter constructors
        //ptr and coeff never gets initialized
        Node(int coeff = 0, Node* next = nullptr): coeff(coeff), next(next){}
    };
    //non-member, cannot be const
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs){
        if(lhs.degree != rhs.degree) return false;
        Node* tracerThis = lhs.headPtr;
        Node* tracerOther = rhs.headPtr;
        // while(tracerThis && tracerOther){
        while(tracerThis && tracerOther){
            if(tracerThis->coeff != tracerOther->coeff){
                return false;
            }
            tracerThis = tracerThis->next;
            tracerOther = tracerOther->next;
        }
        //if(tracerThis || tracerOther){
        // if(tracerThis){
        //     return false;
        // }
        return true;
    }
    friend ostream& operator<<(ostream& os, const Polynomial& pol){
        //if()
        //cout<< pol.degree;
        Node* tracerThis = pol.headPtr;
        vector<int> coeffs;
        while(tracerThis){
            //cout << tracerThis->coeff << endl;
            coeffs.push_back(tracerThis->coeff);
            tracerThis = tracerThis->next;
        }
        // for(int val: coeffs){
        //     cout << val << endl;
        // }
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
                //REMEMBER pol.degree not degree
                os << coeffs[i] << "x^" << i << " + ";
            }
        }
        return os;
    }
//degree = 0: constant, val = 0 or another constant, size still 1.
private:
    int degree;
    Node* headPtr;//

    void addHead(int coeff, int index = 0){
        //ahhhh degree never gets updated here
        //if(degree==0){
        //if(!headPtr->next){
        if(!index){
            //*headPtr ==very wrong!!!!
            headPtr-> coeff =  coeff;
        }
        else{
            headPtr = new Node(coeff, headPtr);
            degree++;// why doesnt degree get updated?
        }
    }
    Node* findTail() const{
        Node* tracer = headPtr;
        while(tracer->next){
            tracer = tracer->next;
        }
        return tracer;
    }
     // Node* findTail() const{
    //     Node* tracer = headPtr;
    //     while(tracer->next){
    //         tracer = tracer->next;
    //     }
    //     return tracer;
    // }

    // void addTail(Node* tracerThis, Node* tracerOther){
    //     //while(tracerOther->next){
    //         //count++;
    //         tracerThis->next = new Node(tracerOther->next->coeff);
    //         // tracerThis = tracerThis->next;
    //         // tracerOther = tracerOther->next;
    //         //degree++;
    //     //}
    // }
public:
// +=
// +
// copy control, i.e. destructor, copy constructor and assignment operator
// ==
// !=
// << Use the caret ^ for exponentiation. So: 5x^3 represents five times the term with an exponent of three.
// evaluation. Takes a single argument and evaluates the polynomial for that value of "X".


//when I have this constructor with 2 default values instead of just default constructor, I had this error
//19: warning: braces around scalar initializer [-Wbraced-scalar-init]
  //  Polynomial p1({17});                 // 17
    //Polynomial(int degree = 0, Node* headPtr = new Node(0)){}
    Polynomial():headPtr(new Node()), degree(0){}
    Polynomial(const vector<int>& vec):  degree(0), headPtr(new Node(0)){
        //for(int val: vec){
        for(size_t i = 0; i < vec.size(); i++){
            //cout << val<< endl;
            addHead(vec[i],i);     
        }

        // Node* tracerThis = headPtr;
        // while(tracerThis){
        //     cout << tracerThis->coeff << ' ';
        //     tracerThis=tracerThis->next;
        // }
        // cout << endl;

        //cout << degree << endl;
        //Node*  tracerHead= headPtr;
        // while(tracerHead){
        //     cout<< tracerHead->coeff<<  ' ';
        //     tracerHead = tracerHead->next;
        // }

        //cout << tracerHead->coeff <<endl;
    }
    // Node*& headPtr(){
    //     return headPtr;
    // }
    Polynomial(const Polynomial& other): degree(0), headPtr(new Node(other.headPtr->coeff)){
        // Node* tracerOther = other.headPtr;
        // while(tracerOther){
        //     addHead(tracerOther->coeff);
        //     tracerOther = tracerOther->next;
        // }
        // if(other.degree == 0){
        //     headPtr = new Node(other.headPtr->coeff);
        // }
        // else{
        //     Node* tracerOther = other.headPtr;
        //     tracerOther = tracerOther->next;
        //     Node* tracerThis = headPtr;
        //     //allocate new values
        //     while(tracerOther){
        //         //this may not be a good idea to be honest!!!!!
        //         tracerThis->next = new Node(tracerOther->coeff);
        //         tracerThis = tracerThis -> next;
        //         tracerOther = tracerOther->next;
        //         degree++;
        //     }
        // }
        Node* tracerOther = other.headPtr;
        Node* tracerThis = headPtr;
        while(tracerOther->next){//not next here and access below -> segmentation fault
            tracerThis->next = new Node(tracerOther->next->coeff);
            tracerThis = tracerThis->next;
            tracerOther = tracerOther -> next;
        }
    }
    ~Polynomial(){
        while(headPtr){
            Node* postThis = headPtr->next;
            delete headPtr;
            headPtr = postThis;
            //degree--;
        }
    }
    Polynomial& operator=(const Polynomial& other){
        if(this != &other){
            // //free up the heap
            // Node* tracerThis = headPtr;
            // tracerThis = tracerThis->next;
            // while(tracerThis){
            //     Node* postThis = tracerThis->next;
            //     delete tracerThis;
            //     tracerThis = postThis;
            //     degree--;
            // }
            // //degree = 0, just change value of the headPtr
            // if(other.degree == 0){
            //     //headPtr = new Node(other.headPtr->coeff);
            //     headPtr->coeff = 0;
            // }
            // else{
            //     cout << "entered here" << endl;
            //     Node* tracerOther = other.headPtr;
            //     tracerOther = tracerOther->next;
            //     headPtr->coeff = other.headPtr->coeff;
            //     tracerThis = headPtr;
            //     //allocate new values
            //     while(tracerOther){
            //         //this may not be a good idea to be honest!!!!!
            //         tracerThis->next = new Node(tracerOther->coeff);
            //         tracerThis = tracerThis -> next;
            //         tracerOther = tracerOther->next;
            //         degree++;
            //     }
            //}

            //********
            Node* tracerThis = headPtr;
            while(headPtr){
                Node* postThis = headPtr->next;
                delete headPtr;
                headPtr = postThis;
                headPtr = nullptr;
                degree--;
            }
            headPtr = new Node(other.headPtr->coeff);
            Node* tracerOther = other.headPtr;
            tracerThis = headPtr;
            //int count = 0;
            while(tracerOther->next){
                //count++;
                tracerThis->next = new Node(tracerOther->next->coeff);
                tracerThis = tracerThis->next;
                tracerOther = tracerOther->next;
                degree++;
            }

            // Node* tracerThis = headPtr;
            // tracerThis = tracerThis->next;
            // while(tracerThis){
            //     Node* postThis = tracerThis->next;
            //     cout << tracerThis << endl;
            //     delete tracerThis;//delete tracerThis but not the actual node itself!!!!
            //     tracerThis = nullptr;
            //     tracerThis = postThis; 
            //     degree--;
            // }
            // cout << headPtr << endl;
            // cout << headPtr->coeff << endl;
            // //headPtr = new Node(other.headPtr->coeff);
            // headPtr->coeff = other.headPtr-> coeff;
            // Node* tracerOther = other.headPtr;
            // tracerThis = headPtr;
            // //int count = 0;
            // while(tracerOther->next){
            //     cout << "here" << endl;
            //     //count++;
            //     tracerThis->next = new Node(tracerOther->next->coeff);
            //     tracerThis = tracerThis->next;
            //     tracerOther = tracerOther->next;
            //     degree++;
            // }
            // cout <<degree << endl;

            
            

        }
        return *this;
        //what if the other list is empty? addHead will take care of it dont worry
    }
    Polynomial& operator+=(const Polynomial& other){
        //cannot print here?

        //cout << "Other " << other << endl;
        // cout << "this is += " << headPtr->coeff << ' ' << other.headPtr->coeff  << degree <<' '<< other.degree<< endl;
        Node* tracerThis = headPtr;
        // while(tracerThis){
        //     cout << tracerThis->coeff << ' ';
        //     tracerThis = tracerThis->next;
        // }
        // cout << endl;
        //tracerThis = headPtr;

        Node* tracerOther = other.headPtr;

        // while(tracerOther){
        //     cout << tracerOther->coeff << ' ';
        //     tracerOther = tracerOther->next;
        // }
        // cout << endl;
        // tracerOther = headPtr;

        //I missed  this before and used tracerThis after while loop - fatal!!!
        Node* tracerTail = tracerThis;
        //both conditions fail if other is empty
        //if both empty - both have const 0, result also const 0
        while(tracerThis && tracerOther){
        //while(tracerThis){
            //cout << "entered this loop " << endl;
            tracerTail = tracerThis;
            //I made a fatal mistake :((( *tracerThis??
            //tracerThis->coeff += tracerOther->coeff;
            //cout << tracerThis->coeff << ' ' << tracerOther->coeff << endl;
            tracerThis->coeff = tracerThis->coeff + tracerOther->coeff;
           // cout << tracerThis->coeff << ' ' << tracerOther->coeff << endl;
            tracerThis = tracerThis->next;
            tracerOther = tracerOther->next;
        }
    //I am so stupid? why if????????
        //if(tracerOther!= nullptr){
        while(tracerOther){
            //cout << "In tracerOther " << tracerOther->coeff << endl;
            tracerTail->next = new Node(tracerOther->coeff);
            degree++;
            tracerTail = tracerTail->next;
            tracerOther = tracerOther->next;
            //cout << "NULL? " <<(tracerTail == nullptr) << ' ' << (tracerOther == nullptr) << endl;
        }
        //cout << "End of +=, degree = " << degree << endl;
        return *this;
    }
    int evaluate(int val) const {
        int count = degree;
        Node* tracerThis = headPtr;
        int result = 0;
        while(tracerThis){
            result += (tracerThis->coeff)* pow(val, degree-count);
            tracerThis = tracerThis->next;
            --count;
        }
        return result;
    }

};

// int exp = 16;
// for(int base_2 = 1; base_2 < (1 << exp); (base_2 <<= 1)){
// std::cout << base_2 << std::endl;
// }

//cannot put const here bc not a member method

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    //  Rational result;
    //     result += lhs;
    //     result += rhs;
    //     return result;
    //this one is doing copy contructor, sth wrong w my copy contructor!!!
    
    //cout << "lsh degree" << result.degree << endl;
    //cout << lhs << endl;

    Polynomial result ;//= lhs;
    result += lhs;

    //Polynomial result = lhs;
    result+= rhs;
    //cout << rhs << endl;
    //cannot return ref to local variable:
    //warning: reference to stack memory associated with local
    //  variable 'result' returned [-Wreturn-stack-address]
    return result;
} 
bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs==rhs);
}
// int main(){

// }

void doNothing(Polynomial temp) {}

int main() {
	
    //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -1x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7
    // p2 = p1;
    // cout << "p2=p1\n p2= "<< p2 << endl;
    // //p2+p3;
    // p2=p3;
    // cout << "p2=p3\n p2= " << p2 << endl;
    //cout << "p2+p3 " << p2+p3 << endl;
    //cout << "p2+p4 " << p2+p4 << endl;

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


