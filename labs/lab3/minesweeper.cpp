/*
Ly Cao
Minesweeper game
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

class Minesweeper{
    const int SIZE_OF_ROWS = 10;
    const int SIZE_OF_COLS = 10;
    const int BOMB_PROBABILITY = 10;

    struct Tile{
        bool isBomb;
        size_t numOfBombs;
        bool madeVisible;
    };    
public:
    Minesweeper(){
        fillInBombs();
        updateBoardConditions();
        totalVisibleCells = 0; 
    };
    /*
    This method initialize the vector of Tile by adding bombs to random positions
    */
    void fillInBombs(){
        for(size_t row = 0; row < SIZE_OF_ROWS; ++row){
            vector<Tile> vTiles;
            for(size_t col = 0; col < SIZE_OF_COLS; ++col){
                Tile tile;
                tile.madeVisible =  false;
                if(rand() % 100 < BOMB_PROBABILITY){
                    tile.isBomb = true;
                    totalBombs += 1;
                }
                else{
                    tile.isBomb = false;
                }
                vTiles.push_back(tile);
            }
            msBoard.push_back(vTiles);
        }
    };

    /*
    This method takes in the row and column, 
    returns an integer of total number of neighbors of a cell that are bombs
    */
    int countTotalNeighbors(int row, int column){
        size_t totalNeighbors = 0;
        for(int changeInRow = -1; changeInRow <= 1; ++ changeInRow){
            for(int changeInCol = -1; changeInCol <= 1; ++ changeInCol){
                if(0 <= row + changeInRow && row +changeInRow < SIZE_OF_ROWS 
                && 0 <= column + changeInCol && column + changeInCol < SIZE_OF_COLS 
                && !(changeInCol == 0 && changeInRow == 0)){
                    if(msBoard[row + changeInRow][column + changeInCol].isBomb){
                        totalNeighbors += 1;
                    }
                }
                
            }
        }
        return totalNeighbors;
    };

    /*
    This method initialize each property numOfBombs of Tile of the vector of Tiles 
    with a number of bombs around it.
    */
    void updateBoardConditions(){
        for(size_t r = 0; r < SIZE_OF_ROWS; ++r){
            for(size_t c = 0; c < SIZE_OF_COLS; ++c){
                if(!msBoard[r][c].isBomb){
                    msBoard[r][c].numOfBombs = countTotalNeighbors(r, c);
                }
            }
        }
    };
     
    /*
    This method takes in the bool of whether or not to dispaly bombs 
    and prints out the cells that are visible and bombs if the bool
    argument is true. If the argument is false, the bombs are not printed out. 
    */
    void display(bool displayWithBombs){
        for(size_t row = 0; row < SIZE_OF_ROWS; ++row){
            for(size_t col = 0; col < SIZE_OF_COLS; ++col){
                if(msBoard[row][col].isBomb && displayWithBombs){
                    cout << "*";
                }
                else if(msBoard[row][col].madeVisible){
                    cout << msBoard[row][col].numOfBombs;
                }
                else{
                    cout << "-";
                }
            }
            cout << endl;
        }
    };

    bool done(){
        if(totalBombs + totalVisibleCells == SIZE_OF_ROWS * SIZE_OF_COLS){
            return true;
        }
        else{
            return false;
        }
    };
    bool validRow(int row){
        return 0 <= row && row < SIZE_OF_ROWS;
    };
    bool validCol(int col){
        return 0 <= col && col < SIZE_OF_COLS;
    };

    //if the cell is visible or not
    // access madeVisible
    bool isVisible(int row, int col){
        return msBoard[row][col].madeVisible;
    }; 

    
    //change the board conditions when a user enter a cell that they "click" on
    //Returns false if the move results in an explosion.
    bool play(int row, int col){
        if(!validRow(row)){
            cout<< "Please enter a valid row" << endl;
        }
        if(!validCol(col)){
            cout<< "Please enter a valid column" << endl;
        }
        if(msBoard[row][col].isBomb){
            done();
            return false;
        }
        vector<vector<int>> todos;
        todos.push_back({row, col});
        
        while(todos.size() != 0){
            vector<int> current = todos.back();
            todos.pop_back();
            if(!msBoard[current[0]][current[1]].madeVisible){
                msBoard[current[0]][current[1]].madeVisible = true;
                totalVisibleCells += 1;
            }
            for(int changeInRow = -1; changeInRow <= 1; ++ changeInRow){
                for(int changeInCol = -1; changeInCol <=1; ++ changeInCol){
                    if(0 <= current[0]+changeInRow && current[0]+changeInRow < SIZE_OF_ROWS 
                    && 0 <= current[1]+changeInCol && current[1]+changeInCol< SIZE_OF_COLS){

                        if(!msBoard[current[0] + changeInRow][current[1] + changeInCol].isBomb 
                        && !msBoard[current[0] + changeInRow][current[1] + changeInCol].madeVisible
                        && msBoard[current[0]][current[1]].numOfBombs == 0){

                        todos.push_back({current[0] + changeInRow, current[1] + changeInCol});
                        }
                    }
                    
                }
            }
            
        }
        return true;
    };
private: 
    vector<vector<Tile>> msBoard;  
    size_t totalBombs;
    size_t totalVisibleCells;
};
int main(){
    Minesweeper sweeper;
    sweeper.display(true);
    //Continue until only invisible cells are bombs
    while(!sweeper.done()){
        sweeper.display(false); //display board without bomb

        int row_sel = -1, col_sel = -1;
        //until row_sel is not -1
        while(row_sel == -1){
            //Get a valid move
            int r, c;
            cout << "row? ";
            cin >> r;
            if(!sweeper.validRow(r)){
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> c;
            if(!sweeper.validCol(c)){
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        //Set selected square to be visible. May effect other cells.
        if(!sweeper.play(row_sel,col_sel)){
            cout << "Sorry, you died..\n";
            sweeper.display(true);// Final board with bombs shown
            exit(0);
        }
    };

    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown
}
