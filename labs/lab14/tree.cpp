#include <iostream>
#include <stdexcept>
using namespace std;

struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};
class EmptyListException: public exception{
    const char* what() const noexcept{
        return "Cannot pass in an empty list";
    }
    //has a field & constructor that can tell the failed value
};

// Note that the standard exceptions are in a header file called stdexcept. 
// Also, they tend not to have a default constructor, 
// but rather to require a string argument that will be returned by the method what().

int max(TNode* root) {
  // Provide this code
  // We will assume there is no meaningful value for 
  // the maximum of an empty tree. 
  // You should throw an appropriate exception for C++'s exception heirarchy 
  if(root == nullptr){
    //throw exception::length_error;
    throw invalid_argument("Cannot pass in an empty list");
    //throw exception("Cannot pass in an empty list");

  }
  else if(root->left == nullptr && root->right == nullptr) return root->data;
  else if(root->right && root->left){
      return max(max(max(root->left),max(root->right)),root->data);
  }
  else if (root->right){
      return max(max(root->right),root->data);
  }
  else{
      return max(max(root->left),root->data);
  }
  // if(root->right){
  //   return max(root->right);

  // }
}

int main() {

  TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
  try{
    cout << max(&f) << endl;
    cout << max(nullptr) << endl;
  }
  catch(const invalid_argument& ex){//hehe, this works
  // catch(exception& ex){
    cout << ex.what() << endl;
  }
  

}

  
  
