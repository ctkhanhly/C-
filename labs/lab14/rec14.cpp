#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node(int data = 0, Node* next = nullptr):data(data), next(next){}
};
bool hasEven(int num){
    if(num==0) return true;//0 number of 1s
    else{
        bool lastCount = hasEven(num/2);
        if(lastCount && num% 2 == 0){
            return true;
        }
        else if(!lastCount && num%2 !=0){
            return true;
        }
        else{
            return false;
        }
    }
}

Node* sumOfLists(Node* list1, Node* list2){
    
    // if(list2 == nullptr && list1->next == nullptr){
    //      //cout << "clause 2\n";
    //     //return new Node(list1->data);

    // }
    // else if(list1== nullptr && list2->next == nullptr){
    //      cout << "clause 3\n";
    //     return new Node(list2->data);
    // }
    // else if(list1->next== nullptr && list2->next == nullptr){
    //      cout << "clause 1\n";
    //     return new Node(list1->data + list2->data);
    // }
    if(list2 == nullptr && list1 == nullptr) return nullptr;
    else{
        // cout << "clause 4\n";
        Node* node = new Node();
        if(list1 && list2){
             //cout << "clause 1\n";
            node->data = list1->data + list2->data;
            node->next = sumOfLists(list1->next, list2->next);
        }
        else if(list1){
            //cout << "clause 2\n";
            node->data = list1->data;
            node->next = sumOfLists(list1->next, list2);
        }
        else{
            //cout << "clause 3\n";
            node->data = list2->data;
            node->next = sumOfLists(list1, list2->next);
        }
        //cout << "here\n";
       
        return node;
    }
}
//char arr[]
// char* arr;
// delete arr;
//only delete if I do new

bool isPalindrome(char* arr, int size){
    if(size<=0){
        return true;
    }
    else{
        return arr[0] == arr[size-1] && isPalindrome(arr+1, size-2);
    }
}
//1) you are writing a recursive function. 
//We are not interested in seeing a function that 
//just outputs the result of computing a formula. 
//2) As always, no globals.
//start, spare, target
int towerOfHanoi(int n, char a, char b, char c){
    if(n==0) return 0;
    else{
        //move prev from start to spare: a->b
        int movePrevToSpare = towerOfHanoi(n-1,a,c,b);
        //move the current to target, then move prev from spare to target: b->c
        int movePrevToTarget = towerOfHanoi(n-1, b, c, a);
        return movePrevToSpare + 1 + movePrevToTarget;
    }
}
void mystery(int n) { 
   if (n > 1) { 
      cout << 'a'; //('a'*n/2 + 'b')*n/2
      mystery(n/2); 
      cout << 'b'; 
      mystery(n/2); 
      cout << 'd';
   } 
   cout << 'c'; 
}
//start, spare, targett
void towers(int n, char a, char b, char c){
    if(n==0) return;
    else{
        towers(n-1,a,c,b);
        cout << "Move " << n << " from " << a << " to " << c << endl;
        towers(n-1,b,a,c);
    }
}

Node* createList(const vector<int>& vec){
    cout << "creatingList\n";
    Node* head = new Node(vec[0]);
    Node* tracer = head;
    for(size_t i = 1; i < vec.size(); i++){
        tracer->next = new Node(vec[i]);
        tracer = tracer->next;
    }
    return head;
}
void printList(Node* head){
    cout <<"printing list\n";
    Node* tracer= head;
    while(tracer){
        cout << tracer->data << ' ';
        tracer = tracer->next;
    }
    cout << endl;
}
int main(){
    cout << "Test hasEven\n";
    cout << boolalpha;
    cout << "hasEven(11) " << hasEven(11) << endl;
     cout << "hasEven(10) " << hasEven(10) << endl;
    cout << "=================\nTest sumOfLists\n";
    Node* list1 = createList({1,2,3,4});
    printList(list1);
    Node* list2 = createList({3,4,5,6,7, 8, 9});
    printList(list2);
    Node* newList = sumOfLists(list1,list2);
    // while(newList){
    //     cout << newList->data << ' ';
    //     newList = newList->next;
    // }
    printList(newList);
    cout << endl;
    char arr1[] = "abcabc";
    char arr2[] = "ababa";
    char arr3[] = "abccba";
    cout << "Test isPalinddrom\n";
    cout << "isPalindrome(abcabc, 6) " << isPalindrome(arr1, 6) << endl;
    cout << "isPalindrome(abccba, 6) " << isPalindrome(arr3, 6) << endl;
    cout << "isPalindrome(ababa,5) "  << isPalindrome(arr2,5) << endl;

    //  ISO C++11 does not allow conversion from string
    //   literal to 'char *' [-Wwritable-strings]
    cout << "========\n";
    cout << "Test tower of Hanoi\n";
    cout << "towerOfHanoi(1, 'a', 'b', 'c'): " << towerOfHanoi(1, 'a', 'b', 'c') << endl;
    cout << "towerOfHanoi(2, 'a', 'b', 'c'): " << towerOfHanoi(2, 'a', 'b', 'c') << endl;
    cout << "towerOfHanoi(3, 'a', 'b', 'c'): " << towerOfHanoi(3, 'a', 'b', 'c') << endl;
    cout << "towerOfHanoi(4, 'a', 'b', 'c'): " << towerOfHanoi(4, 'a', 'b', 'c') << endl;
    cout << "towerOfHanoi(5, 'a', 'b', 'c'): " << towerOfHanoi(5, 'a', 'b', 'c') << endl;
    cout << "towerOfHanoi(6, 'a', 'b', 'c'): " << towerOfHanoi(6, 'a', 'b', 'c') << endl;
    cout << "towerOfHanoi(7, 'a', 'b', 'c'): " << towerOfHanoi(7, 'a', 'b', 'c') << endl;
    cout << "towerOfHanoi(8, 'a', 'b', 'c'): " << towerOfHanoi(8, 'a', 'b', 'c') << endl;
    cout << "towerOfHanoi(9, 'a', 'b', 'c'): " << towerOfHanoi(9, 'a', 'b', 'c') << endl;
    cout << "towerOfHanoi(10, 'a', 'b', 'c'): " << towerOfHanoi(10, 'a', 'b', 'c') << endl;

    cout << "========\n";
    cout << "Test myMystery\n";
    cout << "mystery(1): ";
    mystery(1);
    cout << endl;
     cout << "mystery(2): ";
    mystery(2);
    cout << endl;
     cout << "mystery(3): ";
    mystery(3);
    cout << endl;
     cout << "mystery(4): ";
    mystery(4);
    cout << endl;
     cout << "mystery(5): ";
    mystery(5);
    cout << endl;
     cout << "mystery(6): ";
    mystery(6);
    cout << endl;
     cout << "mystery(7): ";
    mystery(7);
    cout << endl;
     cout << "mystery(8): ";
    mystery(8);
    cout << endl;
     cout << "mystery(9): ";
    mystery(9);
    cout << endl;
     cout << "mystery(10): ";
    mystery(10);
    cout << endl;
     cout << "mystery(11): ";
    mystery(11);
     cout << endl;
     cout << "mystery(12): ";
    mystery(12);
     cout << endl;
     cout << "mystery(15): ";
    mystery(15);
     cout << endl;
      cout << "mystery(16): ";
    mystery(16);
    cout << endl;
     
    //'a'*n/2+ 'c'+'b'
    //'a'* n/2 cbcc + b + 'a'*n/4 + b + cbcc + c 

    cout <<"tower of hanoi \n";
    towers(5,'a','b','c');
}