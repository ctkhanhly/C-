#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <string>

namespace CS2124{
    struct Node{
        int coeff;
        Node* next; 
        Node(int coeff = 0, Node* next = nullptr): coeff(coeff), next(next){}
    };

    class Polynomial{
        friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
        friend std::ostream& operator<<(std::ostream& os, const Polynomial& pol);    
    private:
        int degree;
        Node* headPtr;//
        void addHead(int coeff);
        void cleanup();
    public:
        Polynomial();
        Polynomial(const std::vector<int>& vec);
        Polynomial(const Polynomial& other);
        ~Polynomial();
        Polynomial& operator=(const Polynomial& other);
        Polynomial& operator+=(const Polynomial& other);
        int evaluate(int val) const;
    };
    bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
    const Polynomial& operator+(const Polynomial& lhs, const Polynomial& rhs);

}
#endif