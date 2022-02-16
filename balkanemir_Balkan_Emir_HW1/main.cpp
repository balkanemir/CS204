#include <vector>
#include <iostream>
#include <iomanip>
#include <cctype>
#include "randgen.h"

/*
--------INTRODUCTION--------
 
-> This code is made to introduce basic game of mineswepper in C++. In this code, 2 functions, 3 matrixes are used.

-> The aim of the program is creating an environment which provides to opening cells in matrixes by asking which function that player chooses to win.
 
-> Flow of the program:
 1. Creating a mineswepper board with using matrix.
 2. Ask player his/her choice.
 3. With respect to choice; cell can be opened, cell can be displayed, or player can quit from game.
 
-----------------------------
*/

using namespace std;

void Printmatrix(vector<vector<char>> & matrix) {
    for (int a = 0; a < matrix.size(); a++) {
        for (int b = 0; b < matrix[0].size(); b++) {
            cout << setw(4) << matrix[a][b];
        }
        cout << endl;
    }
}

void bomb(vector<vector<char>> & matrix, vector<vector<char>> & matrix_w_nums, int & coor_row, int & coor_col) {
    
    cout << "Unfortunately, you stepped on a mine" << endl;
    cout << "Arrangement of mines:" << endl;
    Printmatrix(matrix_w_nums);
    cout << ">>>>> Game Over! <<<<<" << endl;
    cin.ignore();
}


int main() {
    int cols, rows ,bombs;
    
    cout << "Give the dimensions of the matrix: ";
    cin >> rows >> cols; // bring number of rows and cols.
    
    cout << "How many bombs: ";
    cin >> bombs; // bring number of bombs.
    
    while (bombs > cols * rows - 1) { // check number of bombs.
        cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
        cin >> bombs; // while it is wrong, bring nummber of bombs.
    }
    
    while (bombs < 1) {  // check bombs.
        cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
        cin >> bombs;
    }
    
    vector<vector<char>> matrix(rows, vector<char>(cols)); // matrix for displaying matrix with "x"s.
    
    for (int c = 0; c < rows; c++) { // for loop: placing 'x's into matrix.
        for (int d = 0; d < cols; d++) {
            matrix [c][d] = 'x';
        }
    }
    
    Printmatrix(matrix); // function for printing matrix.
    
    vector<vector<char>> matrix_w_nums(rows, vector<char>(cols)); // matrix for actual numbers and bombs.

    vector<vector<int>> matrix_for_indexes(bombs, vector<int>(2)); // matrix for storing the index of the bombs.
    
    RandGen rand; // Random number class: required for taking random number (for placing the bombs to matrix_w_num.
    
    int counter_bombs = 0;
    
    while (bombs != counter_bombs) { // while loop: it lasts until all bombs that are wanted are equal to counter_bomb which determines repetition of the loop.
        int random_cols = rand.RandInt(0, cols - 1); // taking random number and assign it to random_cols(this is going to belong bomb's index.)
        int random_rows = rand.RandInt(0, rows - 1); // taking random number and assign it to random_rows(this is going to belong bomb's index.)
        for (int c = 0; c < matrix_w_nums.size(); c++) {
            for (int d = 0; d < matrix_w_nums[0].size(); d++) {
                matrix_w_nums[c][d] = 48;  // firstly, matrix_w_nums(actual matrix) is assigned with 0(zero)'s. 0 corrosponds to 48 in ASCII table.
            }
        }
        
        for (int b = 0; b < 2; b++) { //for loop: it is for storing bomb's indexes which are determined randomly (random_rows, random_cols).
            if (b == 0) {
                matrix_for_indexes[counter_bombs][b] = random_rows; // it assigned.
            }
            if (b == 1) {
                matrix_for_indexes[counter_bombs][b] = random_cols; // it assigned.
            }
        }
        counter_bombs++;
    }
    

    
    for (int j = 0; j < matrix_for_indexes.size(); j++) {  // for loop: it is for placing bombs by taking their indexes from matrix which is created to store indexes (matrix_for_indexes).
        
        int random_rows = matrix_for_indexes[j][0]; // taking the index of row of bomb.
        int random_cols = matrix_for_indexes[j][1]; // taking the index of col of bomb.
        if (matrix_w_nums[random_rows][random_cols] != 66) { // if in this coordinates there is no bomb, assign there a bomb.
            matrix_w_nums[random_rows][random_cols] = 66;
        }
        else { // if in this coordinates there is already a bomb, do this:
            while (matrix_w_nums[random_rows][random_cols] == 'B') { // while loop: this is for preventing bombs to place the same coordinates because their coordinates are determined by random generator.
                random_cols = rand.RandInt(0, cols - 1); // take again new coordinate.
                random_rows = rand.RandInt(0, rows - 1); // take again new coordinate.
                
            }
            matrix_w_nums[random_rows][random_cols] = 66; // if the compiler reach here, it means all bombs successfully placed to matrix without any coincidence of indexes.
            matrix_for_indexes[j][0] = random_rows;
            matrix_for_indexes[j][1] = random_cols;
            
        }
        if (random_rows < rows - 1) { // line 121-164: these if conditions firstly determine whether there is a place surrounding of the bombs, and if there is, it increase the number of the place by 1. For example if (0,0) have a bomb, they detect that there are placements at right, bottom and right-cross. And increment their number by 1.
            if (matrix_w_nums[random_rows + 1][random_cols] != 66) {
                matrix_w_nums[random_rows + 1][random_cols]++;
            }
        }
        if (random_rows > 0) {
            if (matrix_w_nums[random_rows - 1][random_cols] != 66) {
                matrix_w_nums[random_rows - 1][random_cols]++;
            }
        }
        if (random_cols < cols - 1) {
            if (matrix_w_nums[random_rows][random_cols + 1] != 66) {
                matrix_w_nums[random_rows][random_cols + 1]++;
            }
        }
        if (random_cols > 0) {
            if (matrix_w_nums[random_rows][random_cols - 1] != 66) {
                matrix_w_nums[random_rows][random_cols - 1]++;
            }
        }
        if (random_rows < rows - 1 && random_cols < cols - 1) {
            if (matrix_w_nums[random_rows + 1][random_cols + 1] != 66) {
                matrix_w_nums[random_rows + 1][random_cols + 1]++;
            }
        }
        
        if (random_rows < rows - 1 && random_cols > 0) {
            if (matrix_w_nums[random_rows + 1][random_cols - 1] != 66) {
                matrix_w_nums[random_rows + 1][random_cols - 1]++;
            }
        }
        
        if (random_rows > 0 && random_cols < cols - 1) {
            if (matrix_w_nums[random_rows - 1][random_cols + 1] != 66) {
                matrix_w_nums[random_rows - 1][random_cols + 1]++;
            }
        }
        
        if (random_rows > 0 && random_cols > 0) {
            if (matrix_w_nums[random_rows - 1][random_cols - 1] != 66) {
                matrix_w_nums[random_rows - 1][random_cols - 1]++;
            }
        }
    }
    

    
    string choice;
    
    cout << "Press: " << endl;
    cout << "1. If you want to find out the surrounding of a cell" << endl;
    cout << "2. If you want to open the cell" << endl;
    cout << "3. If you want to exit." << endl;
    cin >> choice;  // taking choice as usual.
    
    while (choice != "1" && choice != "2" && choice != "3") { // check whether it is wrong or correct.
        cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
        cin >> choice;
    }
    
    bool found_bomb = true;
    
    int win = 0;
    
    int total_place = rows*cols;
    
    while (found_bomb) { // while loop: this is for lasting the program until player lost.
        if (choice == "1" ) {
            int coor_row, coor_col;
            cout << "Give the coordinates: ";
            cin >> coor_row >> coor_col;
            
            while (coor_row > rows - 1 || coor_col > cols - 1) {
                cout << "It is out of range. Please give a valid coordinates: " << endl;
                cin >> coor_row >> coor_col;
            }
            
            cout << "Displaying the surrounding of (" << coor_row << "," << coor_col << "):" << endl;
            
           
            
            char bomb_counter = '0'; // this is for counting if there is a bomb in demanding placement (for only choice 1), checking surrounding of the placement and counting the number of bombs.
            
            if (matrix_w_nums[coor_row][coor_col] == 'B') {
                if (coor_row < rows - 1) {
                    if (matrix_w_nums[coor_row + 1][coor_col] == 66) {
                        bomb_counter++;
                    }
                }
                if (coor_row > 0) {
                    if (matrix_w_nums[coor_row - 1][coor_col] == 66) {
                        bomb_counter++;
                    }
                }
                if (coor_row < cols - 1) {
                    if (matrix_w_nums[coor_row][coor_col + 1] == 66) {
                        bomb_counter++;
                    }
                }
                if (coor_row > 0) {
                    if (matrix_w_nums[coor_row][coor_col - 1] == 66) {
                        bomb_counter++;
                    }
                }
                if (coor_row < rows - 1 && coor_row < cols - 1) {
                    if (matrix_w_nums[coor_row + 1][coor_col + 1] == 66) {
                        bomb_counter++;
                    }
                }
                
                if (coor_row < rows - 1 && coor_col > 0) {
                    if (matrix_w_nums[coor_row + 1][coor_col - 1] == 66) {
                        bomb_counter++;
                    }
                }
                
                if (coor_row > 0 && coor_col < cols - 1) {
                    if (matrix_w_nums[coor_row - 1][coor_col + 1] == 66) {
                        bomb_counter++;
                    }
                }
                
                if (coor_row > 0 && coor_col > 0) {
                    if (matrix_w_nums[coor_row - 1][coor_col - 1] == 66) {
                        bomb_counter++;
                    }
                }
                matrix[coor_row][coor_col] = bomb_counter; // In here, it assigned the number of bombs surrounding of demanding placement even though there is a bomb in the placement.
            }
            else{
                matrix[coor_row][coor_col] = matrix_w_nums[coor_row][coor_col]; // if there is no bomb, replace the placement from 'x' to actual number which is assigned in actual matrix beforehand.
                cout << "Around (" << coor_row << "," << coor_col << ") you have " << matrix_w_nums[coor_row][coor_col] << " bomb(s)" << endl;
                
            }
            
            Printmatrix(matrix); // display matrix.
            
            matrix[coor_row][coor_col] = 'x'; // after displaying it, matrix should close the displaying because it is choice 1.
            
            
            
            cout << "Press: " << endl;
            cout << "1. If you want to find out the surrounding of a cell" << endl;
            cout << "2. If you want to open the cell" << endl;
            cout << "3. If you want to exit." << endl;
            cin >> choice;
            
            
            
        }
        
        if (choice == "2" ) { // same codes with choice 1. Only difference is there is no closing the replacements after opening and win and lose functions are added.
            int coor_row, coor_col;
            cout << "Give the coordinates: ";
            cin >> coor_row >> coor_col;
            
            while (coor_row > rows - 1 || coor_col > cols - 1) {
                cout << "It is out of range. Please give a valid coordinates: " << endl;
                cin >> coor_row >> coor_col;
            }
            
            cout << "Opening cell (" << coor_row << "," << coor_col << "):" << endl;
            
            matrix[coor_row][coor_col] = matrix_w_nums[coor_row][coor_col];
            
            Printmatrix(matrix);
            
            if (matrix_w_nums[coor_row][coor_col] == 'B') { // if player found a bomb, program ends with "lose" message.
                bomb(matrix, matrix_w_nums, coor_row, coor_col);
                found_bomb = false;
                break;
            }
            
            win++;
            
            if (total_place - win == bombs) { //if player found all placements without founding a bomb, program ends with "win" message.
                cout << "Congratulations! All the non-mined cells opened successfully" << endl;
                cout << "You won!" << endl;
                cout << ">>>>> Game Over! <<<<<" << endl;
                found_bomb = false;
                break;
            }
            
            cout << "Press: " << endl;
            cout << "1. If you want to find out the surrounding of a cell" << endl;
            cout << "2. If you want to open the cell" << endl;
            cout << "3. If you want to exit." << endl;
            cin >> choice;
        }
        if (choice == "3" ) { // ends the program.
            cout << "Program exiting ..." << endl;
            found_bomb = false;
            break;
        }
    }
    return 0;
}
