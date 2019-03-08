#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void printGeneration(vector<string>& generation_map){
    for(size_t row = 0; row < generation_map.size(); ++row){
        cout << generation_map[row] << endl;
    }
    for(size_t row = 0; row < generation_map[0].size(); ++row){
        cout << "=";
    }
    cout << endl;
}

void decide_life(int total_neighbors, vector<string>& temp_generation, int row, int column){
    if(total_neighbors > 3 || total_neighbors < 2){
        temp_generation[row][column] = '-';
    }
    if(total_neighbors == 3){
        temp_generation[row][column] = '*';
    }
}
int count_total_neighbors(vector<string>& generation_map, int row, int column){
    int total_neighbors = 0;
    bool left_column = false;
    bool right_column = false;
    bool up_row = false;
    bool down_row = false;

    if(column - 1 >= 0){
        left_column = true;
    }
    if(column + 1 < generation_map[0].size()){
        right_column = true;
    }
    if(row - 1 >= 0){
        up_row = true;
    }
    if(row + 1 < generation_map.size()){
        down_row = true;
    }

//adding up the neighbors 
    if(left_column){
        if(generation_map[row][column-1] == '*'){
            total_neighbors += 1;
        }
        if(up_row){
            if(generation_map[row-1][column] == '*'){
                total_neighbors += 1;
            }
            if(generation_map[row-1][column-1] == '*'){
                total_neighbors += 1;
            }
        }
        if(down_row){
            if(generation_map[row+1][column] == '*'){
                total_neighbors += 1;
            }
            if(generation_map[row+1][column-1] == '*'){
                total_neighbors += 1;
            }
        }
    }
    if(right_column){
        if(generation_map[row][column+1] == '*'){
            total_neighbors += 1;
        }
        if(up_row){
            if(!left_column){
                if(generation_map[row-1][column] == '*'){
                    total_neighbors += 1;
                }
            }
            if(generation_map[row-1][column+1] == '*'){
                total_neighbors += 1;
            }
        }
        if(down_row){
            if(!left_column){
                if(generation_map[row+1][column] == '*'){
                    total_neighbors += 1;
                }
            }
            
            if(generation_map[row+1][column+1] == '*'){
                total_neighbors += 1;
            }
        }
    }
    return total_neighbors;
}
int main(){
    ifstream initial_state("life.txt");
    string line;
    vector<string> generation_map;
    // getline(cin, line); - reading from the console, 
    //waiting for input before outputting anything

    cout << "Initial world" << endl;

    while(getline(initial_state, line)){
        generation_map.push_back(line);
        cout << line << endl;
    }

    initial_state.close();

    int x = 1;
    while(x < 28){
        cout << "=";
        x += 1;
    }
    cout << endl;

    //cout << generation_map.size() << endl;
    int i = 1;
    // shouldnt hard-code number
    int num_of_generations = 10;
    while(i <= num_of_generations){
        vector<string> temp_generation;

        //vector<string> temp_generation = generation_map;
        // for(size_t row = 0; row < generation_map.size(); ++row){
        //     temp_generation.push_back(generation_map[row]);
        // }
        //same as 

        temp_generation = generation_map;
        for(size_t row = 0; row < generation_map.size() ; ++row){
            for(size_t column = 0; column < generation_map[0].size() ; ++column){
                int total_neighbors = count_total_neighbors(generation_map, row, column);
                //decide to kill live cells or relive dead cells here
                decide_life(total_neighbors, temp_generation, row, column);
            }
        }
        //print out the generation
        cout << "Generation: " << i << endl;
        printGeneration(temp_generation);

        generation_map = temp_generation;

        i += 1;
    }
    
}