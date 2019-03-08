/*
Ly Cao
CS2124 ELAB
This program combines Hydrocarbon of the same formulas 
but different names and output these formulas in the order according
to the number of carbons and hydrogens they have.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//consistent naming convention 
struct Hydrocarbon{
    vector<string> names;
    int numOfCarbons;
    int numOfHydrogens;
};

void fillTheVector(ifstream& ifs, vector<Hydrocarbon>& hydrocarbons);

void sortFormulas(vector<Hydrocarbon>& hydrocarbons);

void displayVector(const vector<Hydrocarbon>& hydrocarbons);

size_t findLocation(const vector<Hydrocarbon>& hydrocarbons, int numOfCarbons, int numOfHydrogens);

void addAMolecule(vector<Hydrocarbon>& hydrocarbons, 
    string& name, int numOfCarbons, int numOfHydrogens);

void openStream(ifstream& hydrocarbon_formulas);

int main(){
    ifstream hydrocarbon_formulas;
    openStream(hydrocarbon_formulas);
    vector<Hydrocarbon> hydrocarbons;
    fillTheVector(hydrocarbon_formulas, hydrocarbons);
    hydrocarbon_formulas.close();
    sortFormulas(hydrocarbons);

    displayVector(hydrocarbons);

    
}

void fillTheVector(ifstream& ifs, vector<Hydrocarbon>& hydrocarbons){
    char carbon;
    char hydrogen;
    string name;
    int numOfCarbons;
    int numOfHydrogens;

    while(ifs >> name >> carbon >> numOfCarbons >> hydrogen >> numOfHydrogens){     
        addAMolecule(hydrocarbons, name, numOfCarbons, numOfHydrogens);      
    }
}

void sortFormulas(vector<Hydrocarbon>& hydrocarbons){
    //e.g: size_t makes into int => casting (1 data type to another)
    for(size_t i = 0; i < hydrocarbons.size(); ++i){
        bool done =  true;
        for(size_t j = 0; j < hydrocarbons.size() - 1 - i; ++j){
            if(hydrocarbons[j].numOfCarbons > hydrocarbons[j+1].numOfCarbons){
                Hydrocarbon temp = hydrocarbons[j];
                hydrocarbons[j] = hydrocarbons[j+1];
                hydrocarbons[j+1] = temp;
                done = false;
            }
            else if(hydrocarbons[j].numOfCarbons == hydrocarbons[i].numOfCarbons &&
            hydrocarbons[j].numOfHydrogens > hydrocarbons[i].numOfHydrogens){
                    Hydrocarbon temp = hydrocarbons[j];
                    hydrocarbons[j] = hydrocarbons[j+1];
                    hydrocarbons[j+1] = temp;
                    done = false;
            }
        }
        if(done){
            break;
        }
    }
}

void displayVector(const vector<Hydrocarbon>& hydrocarbons){
    for(int i = 0; i < hydrocarbons.size(); ++i){
        cout <<  'C' << hydrocarbons[i].numOfCarbons
            << 'H' << hydrocarbons[i].numOfHydrogens;
        for(int j = 0; j < hydrocarbons[i].names.size(); ++j){
            cout  << " " + hydrocarbons[i].names[j];
            cout << " ";
        }
        cout << endl;
    }
}

size_t findLocation(const vector<Hydrocarbon>& hydrocarbons, int numOfCarbons, int numOfHydrogens){
    for(size_t i = 0; i < hydrocarbons.size(); ++i){
        if(hydrocarbons[i].numOfCarbons == numOfCarbons && hydrocarbons[i].numOfHydrogens == numOfHydrogens){
            return i;
        }
    }
    return hydrocarbons.size();
}

void addAMolecule(vector<Hydrocarbon>& hydrocarbons, 
    string& name, int numOfCarbons, int numOfHydrogens){

    int locationOfFormula = findLocation(hydrocarbons, numOfCarbons, numOfHydrogens);

    if(locationOfFormula == hydrocarbons.size()){
        Hydrocarbon hydrocarbon;
        hydrocarbon.names.push_back(name);
        hydrocarbon.numOfCarbons = numOfCarbons;
        hydrocarbon.numOfHydrogens = numOfHydrogens;
        hydrocarbons.push_back(hydrocarbon);
    }
    else{
        hydrocarbons[locationOfFormula].names.push_back(name);
    }
}
void openStream(ifstream& hydrocarbon_formulas){
    string fileName;
    cout << "Please enter the correct filename" << endl;
    cin >> fileName;
    // hydrocarbon_formulas = ifstream(fileName);
    hydrocarbon_formulas.open(fileName);
    //this is only checking the outer varibale, not the variable created inside while loop
    while(!hydrocarbon_formulas){
        //already clear the outer variable here
        hydrocarbon_formulas.clear();
        cout << "Please enter the correct filename" << endl;
        cin >> fileName;

        //this is a local variable
        // ifstream hydrocarbon_formulas(fileName);

        //hydrocarbon_formulas = ifstream(fileName);
        hydrocarbon_formulas.open(fileName);
    }
}