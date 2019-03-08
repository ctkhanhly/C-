#include <iostream>
#include <vector>
using namespace std;

//lost 5 points:
struct Thing{
    int value;
}//;

void updateThings(const vector<Thing>& v){
    for(Thing& t : v){
        //cannot change constant
        ++t.value;
    }
    for(size_t i = 0; i< v.size(); ++i){
        ++v[i];
    }

}

int main(){
    vector<Thing> vt;
    for(int i = 0; i < 10; ++i){
        //copy tempory Thing obj, initilize with i
        //e.g: in vector: vector<int> v{1,2,3,4}
        //do same thing with struct, if more fields - comma

        //not yet a constructor?
        vt.push_back(Thing(i));
    }

    //dont pass Thing by value - 5 points - lack correct use of parameter passing
//also constant reference
    for(Thing t : vt){
        cout << t.value;
    }

    cout << endl;

    updateThings(vt);
    cout << endl;

    //POD: Plain old data

    //non-primitives and struct, class, user-defined : const reference 

}
