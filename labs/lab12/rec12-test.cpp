// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;



class DoublyLinkedList {
    struct Node{ //accessible within DoublyLinkedList only
        int data;
        Node* prior;
        Node* next;
        Node(int data = 0, Node* prior= nullptr, Node* next = nullptr): data(data), prior(prior), next(next){}
        int operator*(){ return data;}
    };
    
    friend ostream& operator<<(ostream& os, const DoublyLinkedList& dll){
        //for(int data: dll){
        // for(size_t i=0; i < dll.size(); i++){
        //     //os << data << "->";
        //     os << dll[i] << endl;
        // }
        Node* tracer = dll.header;
        tracer = tracer->next;
        while(tracer!=dll.trailer){
            os << tracer->data;
            tracer = tracer->next;
            //if(tracer->next != dll.trailer){  
            if(tracer != dll.trailer){  
                os << "->";
            }
        }
        //cout << endl;
        //os << endl;
        return os;
    }
    Node* findNodeByIndex(size_t index) const{
        Node* tracer = header;
        index ++;
        while(tracer != trailer && index > 0){
            tracer =  tracer ->next;
            index --;
        }
        return tracer;
    }
private:
    size_t length;
    Node* header;
    Node* trailer;
public:
    // friend class iterator;
    class iterator{
        friend DoublyLinkedList;
        friend bool operator==(const iterator& lhs, const iterator& rhs){
            return lhs.node == rhs.node;
        }
    private:
        Node* node;
    public:
    //we should consider the copy constructor. 
    // Not that we need copy control. 
    // Why not? Because the iterator does not own the Node. 
    // So we will not be doing a deep copy, and in fact do not 
    // need to implement a copy constructor. The one the system provides is good enough.

        // iterator(Node* node): node(node){}
        // iterator(Node* node): node(new Node(node->data, node->prior, node->next)){
        //     //node = node;
        // }


        iterator(Node* node):node(node){}
        iterator(const iterator& iterator){
            //node = new Node(*(iterator.node));//using copy constructor of node
            node = iterator.node;
        }

        int& operator*(){ return node->data;}
        //this is deference to the object not pointer!!!!!!!


        //range for !!!!!!!!

        //int& operator++(){ 
        iterator& operator++(){
            //node->data++;
            node = node->next;
            return *this;
            // return node->data;
            //return **this; -> get iterator ->deference: get node->data now
        }
        //int& operator--(){
        iterator& operator--(){
            // node->data--;
            node = node->prior;
            return *this;
            //return node->data;
            //return **this;
        }
    };
    
    
    //const class? not  really right?
    //because it is an iterator, it needs to be incremented and decremented

    // const class const_iterator{
    class const_iterator{
        friend DoublyLinkedList;
        //const qualifier is not allowed on a non-member function
        //friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) const {
        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs){
            return lhs.node == rhs.node;
        }
    private:
        Node* node;//node has to be incremented => cannot be const
    public:
    //we should consider the copy constructor. 
    // Not that we need copy control. 
    // Why not? Because the iterator does not own the Node. 
    // So we will not be doing a deep copy, and in fact do not 
    // need to implement a copy constructor. The one the system provides is good enough.

        // iterator(Node* node): node(node){}
        // iterator(Node* node): node(new Node(node->data, node->prior, node->next)){
        //     //node = node;
        // }


        const_iterator(Node* node):node(node){}
        const_iterator(const iterator& const_iterator){
            //node = new Node(*(iterator.node));//using copy constructor of node
            node = const_iterator.node;
        }

        int operator*() const { return node->data;}
        //this is deference to the object not pointer!!!!!!!

        bool operator!=(const iterator& rhs) const {
            return !(*this == rhs);
        } 


        //range for !!!!!!!!

        //int& operator++(){ 
        const_iterator& operator++(){
            //node->data++;
            node = node->next;
            return *this;
            // return node->data;
            //return **this; -> get iterator ->deference: get node->data now
        }
        //int& operator--(){
        const_iterator& operator--(){
            // node->data--;
            node = node->prior;
            return *this;
            //return node->data;
            //return **this;
        }
    };
    
//  Node* header = nullptr, Node* trailer = nullptr
//segmentation fault here
    DoublyLinkedList(): length(0), header(new Node()), trailer(new Node(0, header)){
        header->next = trailer;
        // trailer->prior =  header;
    }
    //public
    size_t size() const { return length;}
    //bool size() const{  return length!=0;}
    // push_back(int data)
    // pop_back()
    // front()

    DoublyLinkedList(const DoublyLinkedList& dll):length(0), header(new Node()), trailer(new Node(0, header)){
        //length = dll.length;
        // header = new Node();
        header->next = trailer;
        Node* tracerOther = dll.header->next;
        //Node* tracerThis  = header; 
        while(tracerOther != dll.trailer){
            push_back(tracerOther->data);
            tracerOther = tracerOther->next;
        }
        //trailer  =  new Node();

    }

    ~DoublyLinkedList(){
        clear();
        delete header;
        delete trailer;
        //trailer = nullptr; - never obj used again  - no nullptr
    }
    DoublyLinkedList& operator=(const DoublyLinkedList& dll){
        if(this!= &dll){
            clear();
            //dont have to delete header and trailer => dont need to redo the work
            //clear already associate header next to trailer
            //length = dll.length;
            Node* tracerOther = dll.header->next;
            //Node* tracerThis  = header; 
            while(tracerOther != dll.trailer){
                push_back(tracerOther->data);
                tracerOther = tracerOther->next;
            }
        }
        
        return *this;
    }

    void push_back(int data){
        Node* prev = trailer->prior;
        Node* newValue = new Node(data, prev, trailer);
        prev->next = newValue;
        //newValue->prior = prev;
        //newValue->next  = trailer;
        trailer->prior = newValue;
        length++;
    }
    void pop_back(){
        if(length == 0){
            // That could include the program crashing
            cerr << "The list is empty" << endl;
            exit(1);
        }
        Node* last = trailer->prior;//= back()
        Node* prev = trailer->prior->prior;
        prev->next = trailer;
        trailer->prior = prev;
        delete last;
        last = nullptr;///????
        length--;
    }
    int front() const {
        if(length == 0){
            // That could include the program crashing
            cerr << "The list is empty" << endl;
            exit(1);
        }
        return header->next->data;
    }
    //setter
    int& front(){
        if(length == 0){
            // That could include the program crashing
            cerr << "The list is empty" << endl;
            exit(1);
        }
        return header->next-> data;
    }

    int back() const{
        if(length == 0){
            // That could include the program crashing
            cerr << "The list is empty" << endl;
            exit(1);
        }
        return trailer->prior->data;
    }
    
    int& back(){
        if(length == 0){
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
        length++;   
    }

    void pop_front(){
        if(length == 0){
            // That could include the program crashing
            cerr << "The list is empty" << endl;
            exit(1);
        }
        Node* prev = header->next->next;
        Node* first = header->next;//front()
        header->next = prev;
        prev-> prior = header;
        delete first;
        first = nullptr;
        length--;
    }
    void clear(){
        Node* tracer = header;
        // while(tracer->next != trailer){
        //cannot delete header of course!!!
        tracer = tracer->next;
        while(tracer!= trailer){
            //cout << tracer->data << endl;
            Node* nodeToDelete = tracer;
            delete nodeToDelete;
            nodeToDelete = nullptr;
            //never use this variable again - dont need to use this var no need nullptr
            //cannot access next afer delete hoho
            tracer = tracer->next;
        }
        header->next = trailer;
        trailer->prior = header;
        length = 0;
    }

    int& operator[](size_t index){ return findNodeByIndex(index)->data;}
    int operator[](size_t index)const{ return findNodeByIndex(index)->data;}

    const Node* begin() const { return header->next;}
    const Node* end() const{ return trailer->prior;}
    // const int* begin() const { return &header->next;}
    // const int* end() const { return &trailer->prior;}

    iterator begin() { return iterator(header->next);}
    iterator end() { return iterator(trailer);}

    const_iterator cbegin() const { return const_iterator(header->next);}
    const_iterator cend() const { return const_iterator(trailer->prior);}

    void insert(const iterator& i, int val){
        Node* prev = i.node->prior;
        Node* newValue = new Node(val, prev, i.node);
        prev ->next = newValue;
        i.node->prior = newValue;
        length++;
    }

    void erase(const iterator& i){
        Node* prev = i.node->prior;
        Node* post = i.node->next;
        delete i.node;
        prev->next = post;
        post->prior = prev;
        length--;
    }
};
//or make != a friend
bool operator!=(const DoublyLinkedList::iterator& lhs, const DoublyLinkedList::iterator& rhs){
    return !(lhs == rhs);
} 
// Task 1
void printListInfo(const DoublyLinkedList& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(DoublyLinkedList& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const DoublyLinkedList& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(DoublyLinkedList aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}    
void testRangedFor(const DoublyLinkedList& dll){
    for(int val: dll){
        cout << val << ' ';
    }
    cout << endl;
}
int main() {

    // Task 1
    cout << "\n------Task One------\n";
    DoublyLinkedList myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        //cout << myList.size() <<endl;
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);

    cout << "Now display the elements in a ranged for\n";
    //not const, copy ---> iterator

    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (DoublyLinkedList::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";


    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";


    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";


    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    DoublyLinkedList listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";

    testRangedFor(myList);


}
