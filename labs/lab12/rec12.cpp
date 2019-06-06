#include <iostream>
#include <string>
using namespace std;

//have trailer and header so that remove head and trailer will be O(1)

class DoublyLinkedList{
    struct Node{ //accessible within DoublyLinkedList only
        int data;
        Node* next;
        Node* prior;
        Node(int data, Node* next= nullptr, Node* prior = nullptr): data(data), next(next), prior(prior){}
    };
    friend ostream& operator<<(ostream& os, const DoublyLinkedList& dll){
        for(int data: dll){
            os << data << "->";
        }
        os << endl;
        return os;
    }
private:
    size_t size;
    Node* header;
    Node* trailer;
public:
    DoublyLinkedList(size_t size= 0,  Node* header = nullptr, Node* trailer = nullptr): size(size),header(header),trailer(header){
        header->next = trailer;
        trailer->prior =  header;
    }
    //public
    size_t size() const{ return size;}
    // push_back(int data)
    // pop_back()
    // front()

    void push_back(int data){
        Node* prev = trailer->prior;
        Node* newValue = new Node(data, prev, trailer);
        prev->next = newValue;
        //newValue->prior = prev;
        //newValue->next  = trailer;
        trailer->prior = newValue;
        size++;
    }
    void pop_back(){
        Node* last = trailer->prior;
        Node* prev = trailer->prior->prior;
        prev->next = trailer;
        trailer->prior = prev;
        delete last;
        last = nullptr;///????
        size--;
    }
    int front() const {
        if(size == 0){
            // That could include the program crashing
            cerr << "The list is empty" << endl;
            exit(1);
        }
        return header->next->data;
    }
    //setter
    int front(){
        if(size == 0){
            // That could include the program crashing
            cerr << "The list is empty" << endl;
            exit(1);
        }
        return header->next-> data;
    }

    int back() const{
        if(size == 0){
            // That could include the program crashing
            cerr << "The list is empty" << endl;
            exit(1);
        }
        return trailer->prior->data;
    }
    
    int back(){
        if(size == 0){
            // That could include the program crashing
            cerr << "The list is empty" << endl;
            exit(1);
        }
        return trailer->prior->data;
    }

    // push_front(int data)
    // pop_front()

    void push_front(int data){
        Node* first = header->next;
        Node* newValue = new Node(data,header, first);
        first->prior = newValue;
        header->next = newValue;  
        size++;   
    }

    void pop_front(){
        Node* prev = header->next->next;
        Node* first = header->next;
        header->next = prev;
        prev-> prior = header;
        delete first;
        first = nullptr;
        size--;
    }
    void clear(){
        Node* tracer = header;
        while(tracer->next != trailer){
            delete tracer;
            tracer = nullptr;
            tracer = tracer->next;
        }
        header->next = trailer;
        trailer->prior = header;
        size = 0;
    }



};