#include "Polynomial.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

namespace CS2124{

    //Compare two Polynomials if they're equal
    bool operator==(const Polynomial& lhs, const Polynomial& rhs){

        //If they don't have the same degree then they're obviously not equal
        if(lhs.degree != rhs.degree) return false;

        Node* tracerThis = lhs.headPtr->next;
        Node* tracerOther = rhs.headPtr->next;

        //Check if each coeffients of two Polynomials are the same
        while(tracerThis && tracerOther){
            if(tracerThis->coeff != tracerOther->coeff){
                return false;
            }
            tracerThis = tracerThis->next;
            tracerOther = tracerOther->next;
        }
        return true;
    }

    //output the Polynomial
    ostream& operator<<(ostream& os, const Polynomial& pol){
        Node* tracerThis = pol.headPtr->next;

        //If the list is empty, just print 0
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

    //Add more terms into the Polynomial, used only for the constructor
    void Polynomial::addHead(int coeff){
        headPtr = new Node(coeff, headPtr);
        degree++;
    }

    //Delete leading zeros of the Polynomial
    void Polynomial::cleanup(){
        int updatedDegree = 0;
        Node* tracer = headPtr->next;
        int count = 0;
        Node* tail = tracer;

        //Keep track of the largest degree, 
        //ignoring the larger degree with 0 coefficients

        while(tracer){
            if(tracer->coeff != 0){
                updatedDegree = count;
                tail = tracer;
            }
            count ++;
            tracer = tracer->next;
        }

        //Delete the leading zeros
        Node* tracerTail = tail->next;
        tail->next = nullptr;
        while(tracerTail){
            Node* postTail = tail->next;
            delete tracerTail;
            tracerTail = nullptr;
            tracerTail = postTail;
        }
        //Update the real degree
        degree = updatedDegree;
    }

    //Constructors for polynomial
    Polynomial::Polynomial():headPtr(new Node()), degree(0){}
    Polynomial::Polynomial(const vector<int>& vec):  degree(0), headPtr(new Node(0)){
        for(size_t i = 0; i < vec.size(); i++){
            addHead(vec[i]);
        }
        addHead(0);
        cleanup();
    }

    //Copy contructor for Polynomial
    Polynomial::Polynomial(const Polynomial& other): degree(other.degree), headPtr(new Node(0)){
        Node* tracerOther = other.headPtr;
        Node* tracerThis = headPtr;
        //Deep copy all values from other Polynomial
        while(tracerOther->next){
            tracerThis->next = new Node(tracerOther->next->coeff);
            tracerThis = tracerThis->next;
            tracerOther = tracerOther -> next;
        } 
    }

    //Destructor for Polynomial
    Polynomial::~Polynomial(){
        while(headPtr){
            Node* postThis = headPtr->next;
            delete headPtr;
            headPtr = postThis;
        }
    }

    //Assign this number to another number
    Polynomial& Polynomial::operator=(const Polynomial& other){
        if(this != &other){
            //free up old values
            Node* tracerThis = headPtr;
            while(headPtr){
                Node* postThis = headPtr->next;
                delete headPtr;
                headPtr = nullptr;
                headPtr = postThis;
            }

            //Allocate new headPtr and 
            //copy over values from other Polynomial

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

    //Add this Polynomial to another number and assign itself to that number
    Polynomial& Polynomial::operator+=(const Polynomial& other){
        Node* tracerThis = headPtr->next;
        Node* tracerOther = other.headPtr->next;
        Node* tracerTail = headPtr;

        //Add the coefficients of corresponding terms with the same
        //degree in both Polynomials
        while(tracerThis && tracerOther){
            tracerTail = tracerThis;
            tracerThis->coeff = tracerThis->coeff + tracerOther->coeff;
            tracerThis = tracerThis->next;
            tracerOther = tracerOther->next;
        }

        //If the other Polynomial has higher degree than this Polynomial,
        //add more higher degree terms from the other Polynomial

        while(tracerOther){
            tracerTail->next = new Node(tracerOther->coeff);
            tracerTail = tracerTail->next;
            tracerOther = tracerOther->next;
        }

        //Delete leading zeros, or terms of highest degrees that 
        //have 0 as a coefficient
        cleanup();
        return *this;
    }

    //Evaluate a Polynomial at x = val
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

    //Add two Polynomials
    const Polynomial& operator+(const Polynomial& lhs, const Polynomial& rhs){
        Polynomial result ;
        result += lhs;
        result+= rhs;
        return result;
    } 

    //Compare if two Polynomials are not equal
    bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
        return !(lhs==rhs);
    }

}