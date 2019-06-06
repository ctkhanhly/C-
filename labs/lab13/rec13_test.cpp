// rec13_test.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

void printListNonConst(const list<int>& l){
    // for(list<int>::iterator p = l.begin(); p!= l.end(); p++){
    //     cout << *p << ' ';
    // }
}
void printListConst(const list<int>& l ){
    for(list<int>::const_iterator p = l.begin(); p!= l.end(); p++){
        cout << *p << ' ';
    }
}
void printListConst10(const list<int>& l ){
    for(int val : l){ // const int val?
        cout << val << ' ';
    }
}
//12
void printListAuto(const list<int>& l){
    for(auto p = l.begin(); p!= l.end(); p++){
        cout << *p << ' ';
    }
}
//11
list<int>::const_iterator myFindList(const list<int>& l, int val){
    //outside function, use normal list => normal iterator
    //inside function,use cosnt list => const iterator
    for(list<int>::const_iterator p = l.begin(); p!= l.end(); p++){
        if(*p == val){
            return p;
        }
    }
    return l.end();
}

//13
auto findAuto(const list<int>& l, int val){
    for(auto p = l.begin(); p != l.end(); p++){
        if(*p==val){
            //no viable conversion from returned value of type
    //   'std::__1::__list_const_iterator<int, void *>' to function return type
    //   'int'
            return p;
        }
    }

    // no viable conversion from returned value of type
    //   'std::__1::list<int, std::__1::allocator<int> >::const_iterator' (aka
    //   '__list_const_iterator<int, void *>') to function return type 'int'

    return l.end();
}

//15 support find_if()
// bool find_if15(const list<int>& l, int val){
//     for(int val: l){
//         if(val %2 == 0){
//             return true;
//         }
//     }
//     return false;
// }

bool find_if15(int val){
    return val%2 == 0;
}

class Task16{
public:
//has to be public!!!!!!!!!!!
    bool operator()(int val){
        return val%2 == 0;
    }

};

//task19
list<int>::iterator ourFind(list<int>::iterator start, list<int>::iterator end, int val){
    cout << "ourFind for list of ints" << endl;
    for(list<int>::iterator p = start; p!= end; p++){
        if(*p == val){
            return p;
        }
    }
    return end;
}

template <typename T, typename U>
T ourFind(T start, T end, U target){
    cout << "Template ourFind" << endl;
    for(T p = start; p!= end; p++){
        if(*p == target){
            return p;
        }
    }
    return end;
}
int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> v1 = {5,4,1,6,7,8,3,2};
    for(int val: v1){
        cout << val << ' ';
    }
    cout << endl;
    
    // cout << "sorted" << endl;
    // cout << "Vector\n"; 
   
   





    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> l(v1.begin(), v1.end());
    //for(int* p = l.begin(); p!= l.end(); p++){
    cout << "List\n";
    for(list<int>::iterator p =  l.begin(); p!=l.end(); p++){
        cout << *p << ' ';
    }
    cout << endl;

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(v1.begin(), v1.end());

    for(int val: v1){
        cout << val << ' ';
    }
    cout << endl;

     cout << "List\n";
    for(list<int>::iterator p =  l.begin(); p!=l.end(); p++){
        cout << *p << ' ';
    }
    cout << endl;

    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for(size_t i = 0; i < v1.size(); i+=2){
        cout << v1[i] << ' ';
    }
    cout << endl;

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    //cannot print out list this way:
    // for(size_t i = 0; i < v1.size(); i+=2){
    //     cout << l[i] << ' ';
    // }
    // cout << endl;

    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";

    for(vector<int>::iterator p = v1.begin(); p!= v1.end(); p+=2){
        cout << *p << ' ';
    }
    cout << endl;


    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
//jump past the end, nullptr
    for(list<int>::iterator p = l.begin(); p!= l.end(); ++ ++p){
        cout << *p << ' ';
        //p++;
    }
    cout << endl;

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    l.sort();
    for(list<int>::iterator p = l.begin(); p!= l.end(); p++){
        cout << *p << ' ';
    }
    cout << endl;
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    //printListNonConst(l);
    printListConst(l);
    cout << endl;
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printListConst10(l);
    cout << endl;
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printListAuto(l);
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    //refer to myFindList()

    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    //auto

    //refer to findAuto()
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    list<int>::iterator val = find(l.begin(), l.end(), 3);
    if(val == l.end()){
        cout << "Val 1 not found" << endl;
    }
    else{
        cout << "Val 1: " << *val << endl;
    }
    // cout << *find(l.begin(), l.end(),3);
    // cout << endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";

    // list<int>::iterator val1 = find_if(l.begin(), l.end(), find_if15(4));
    // list<int>::iterator val2 = find_if(l.begin(), l.end(), find_if15(0));
    list<int>::iterator val1 = find_if(l.begin(), l.end(), find_if15);
    if(val1 == l.end()){
        cout << "Val 1 not found" << endl;
    }
    else{
        cout << "Val 1: " << *val1 << endl;
    }
    // if(val2 == l.end()){
    //     cout << "Val 2 not found" << endl;
    // }
    // else{
    //     cout << "Val 2: " << *val2 << endl;
    // }

    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    Task16 functor16;
    list<int>::iterator val2 = find_if(l.begin(), l.end(), functor16);
    if(val2 == l.end()){
        cout << "Val 2 not found" << endl;
    }
    else{
        cout << "Val 2: " << *val2 << endl;
    }

    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    //I need to keyword return in my lambda expression
    list<int>::iterator val3 = find_if(l.begin(), l.end(), [](int val){ return val%2 == 0;});

    if(val3 == l.end()){
        cout << "Val 3 not found" << endl;
    }
    else{
        cout << "Val 3: " << *val2 << endl;
    }

    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int arr[8];
    copy(l.begin(), l.end(),arr);
    for(int* p = arr; p!= arr+8; p++){
        cout << *p << ' ';
    }
    cout << endl;

    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    list<int>::iterator val19 = ourFind(l.begin(), l.end(), 4);
    if(val19 == l.end()){
        cout << "Val 19 not found" << endl;
    }
    else{
        cout << "Val 19: " << *val19 << endl;
    }

    // cout << *ourFind(l.begin(), l.end(), 4);
    // cout << endl;

    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    vector<int>::iterator val20 = ourFind(v1.begin(), v1.end(), 4);
    if(val20 == v1.end()){
        cout << "Val 20 not found" << endl;
    }
    else{
        cout << "Val 20: " << *val20 << endl;
    }

    // cout << *ourFind(v1.begin(), v1.end(), 4);
    // cout<< endl;

    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream ifs("pooh-nopunc.txt");
    vector<string> inputs;
    string input;
    bool in = false;
    while(ifs>>input){
        for(const string& s: inputs){
            if(input==s){
                in = true;
            }
        }
        if(!in){
            inputs.push_back(input);
        }
        in = false;
        
    }
    cout << "Size: " << inputs.size() << endl;
    for(const string& s: inputs){
        cout << s << ' ';
    }
    cout << endl;
    ifs.close();
    ifs.clear();

    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";

    ifstream ifs2("pooh-nopunc.txt");
    set<string> inputs2;
    string input2;
    while(ifs2>>input2){
        if(find(inputs2.begin(), inputs2.end(), input2) == inputs2.end()){
            inputs2.insert(input2);
        }
    }
    cout << "Size: " << inputs2.size() << endl;
    for(const string& s: inputs2){
        cout << s << ' ';
    }
    cout << endl;
    ifs2.close();
    ifs2.clear();


    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    //ifs.open()
    ifstream ifs3("pooh-nopunc.txt");
    string input3;
    int count = 1;
    while(ifs3>>input3){
        wordMap[input3].push_back(count);
        count ++;
    }
    cout << "Size: " << wordMap.size() << endl;
    for(const pair<string, vector<int>>& p: wordMap){
        //cout << p[0] << ' ';
        cout << p.first << ' ';
        //for(int i: p[1]){
        for(int i: p.second){
            cout << i << ' ';
        }
        cout << endl;
    }
    cout << endl;
    ifs3.close();
    ifs3.clear();
    cout << "=======\n";
}
