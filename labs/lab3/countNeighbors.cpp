//the default value of size_t is very big, probably the largest.


/*
int countTotalNeighbors(vector<vector<Tile>> msBoard, int row, int column){
        int total_neighbors = 0;
        bool left_column = false;
        bool right_column = false;
        bool up_row = false;
        bool down_row = false;

        if(column - 1 >= 0){
            left_column = true;
        }
        if(column + 1 < msBoard[0].size()){
            right_column = true;
        }
        if(row - 1 >= 0){
            up_row = true;
        }
        if(row + 1 < msBoard.size()){
            down_row = true;
        }

    //adding up the neighbors 
        if(left_column){
            if(msBoard[row][column-1].isBomb){
                total_neighbors += 1;
            }
            if(up_row){
                if(msBoard[row-1][column].isBomb){
                    total_neighbors += 1;
                }
                if(msBoard[row-1][column-1].isBomb){
                    total_neighbors += 1;
                }
            }
            if(down_row){
                if(msBoard[row+1][column].isBomb){
                    total_neighbors += 1;
                }
                if(msBoard[row+1][column-1].isBomb){
                    total_neighbors += 1;
                }
            }
        }
        if(right_column){
            if(msBoard[row][column+1].isBomb){
                total_neighbors += 1;
            }
            if(up_row){
                if(!left_column){
                    if(msBoard[row-1][column].isBomb){
                        total_neighbors += 1;
                    }
                }
                if(msBoard[row-1][column+1].isBomb){
                    total_neighbors += 1;
                }
            }
            if(down_row){
                if(!left_column){
                    if(msBoard[row+1][column].isBomb){
                        total_neighbors += 1;
                    }
                }
                
                if(msBoard[row+1][column+1].isBomb){
                    total_neighbors += 1;
                }
            }
        }
        return total_neighbors;
    }

*/