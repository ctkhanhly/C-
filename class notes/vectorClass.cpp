#include <iostream> //vector: API
using namespace std;

class Vector{
public:
    //array of ints [1] - in square bracket: how many ur allocating.
    //C++ base on C -> sloppy here:
    //not telling you that it points to an array, 
    //but same as pointing to any other element


//array of int pointers: new int*[1]
    Vector():data(new int[1]), theSize(0), theCapacity(1){}
//capacity 0 -> data pointer nullptr
    //Copy Controll
    Vector(const Vector& rhs){
        theSize= rhs.theSize;
        theCapacity = rhs.theCapacity;
        data = new int[theCapacity];
        for(size_t i = 0; i < theSize; ++i ){
            data[i] = rhs.data[i]; //square bracket for pointer
        }
    }//loop to copy data +  pointer to new array.
    ~Vector(){delete [] data;} //need to tell if deleting 1 or an array of things
    //Vector(const Vector& rhs);
    Vector& operator=(const Vector& rhs){
        //0. Check for self-assignment:
        if(this != &rhs){
            //1. Free up
            delete [] data;
            //2. Allocate
            data = new int[rhs.theCapacity];

            //3. Copy over all the data
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;
            for(size_t i = 0; i < theSize; ++i){
                data[i]= rhs.data[i];
            }

        }
         //4. return yourself
        return *this;
        

    }

    //void push_back(int val);

    size_t size() const { return theSize;}
    void clear(){theSize = 0;}
    void push_back(int val){
        if(theCapacity == 0){
            
        }
        else if(theSize == theCapacity){
            //if capacity = 0 when initilized
            //then now have to check allocate new array probably size 1
            //C++ starts out with 0.
            int* oldArray = data;
            data =new int[theCapacity*2];
            for(size_t i = 0; i< theSize; ++i){
                data[i] = oldArray[i];
            }
            delete [] oldArray;
            theCapacity *= 2;
        }

        data[theSize] = val;
        ++theSize;
    }
    void pop_back(){ --theSize; }//failing silently, no return type

    //Square  brackets?
    //like a getter - has to be const method.
    int operator[](size_t index) const { return data[index]; }
private:
    size_t theSize;
    size_t theCapacity;
    int* data;

};

int main(){
    Vector v;
    for(size_t i = 0; i < v.size(); ++i){
        cout << v[i] << endl;
    }
    Vector v2(v);//copy constructor
    //convert it to a function call******, name of function operator[]()
    //v.operator[](0);
    //v[0] 

    //assignment operator must be implemented as a member function
    //v[0] = 100; 
}