/*
Ly Cao
Object-Oritented section DLEC 
Homework 1: decrypt a message from file encrypted.txt that was encrypted
using Caesar encryption.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

char decryptChar(char c, int caesar_shift);
string decryptString(string& s, int caesar_shift);

int main(){

    //Read the encrypted message
    ifstream encrypted_text("encrypted.txt");

    //Check whether the file was opened successfully
    if(!encrypted_text){
        cerr << "Cannot open file.\n";
        exit(1);
    }

    //Get the number on the first line of the file as the caesar shift
    int caesar_shift;
    encrypted_text >> caesar_shift;
    string line;
    vector<string> lines;

    //Move on to the next line from the line that has caesar shift
    getline(encrypted_text, line);

    //Put all the lines in the encrypted.txt into a vector
    while(getline(encrypted_text, line)){
        lines.push_back(line);
    }
    encrypted_text.close();

    //Decrypt each line and print them in reverse order of the original text
    for(size_t i = lines.size() - 1; i > 0; --i){
        cout << decryptString(lines[i], caesar_shift) << endl;
    }
    cout << decryptString(lines[0], caesar_shift) << endl;

}

/*
This method takes an encrypted character and a Caesar shift 
and return a decrypted character
*/
char decryptChar(char c, int caesar_shift){
    
    //Exclude all CAPS and punctuation marks
    if(c < 'a' || c > 'z'){
        return c;
    }
    else if(c - caesar_shift >= 'a'){
        return c - caesar_shift;
    }
    else{
        return 'z' - (caesar_shift - (c - 'a')) + 1;
    }
}

/*
This method takes an encrypted string and a Caesar shift 
and return a decrypted string
*/
string decryptString(string& s, int caesar_shift){
    for(char& letter : s){
        letter = decryptChar(letter, caesar_shift);
    }
    return s;
}
