#include <vector>
#include <set>
#include <iostream>
#include <math.h>
#include <cassert>
#include "sudoku.h"

using std::set;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

// ======================================================
// A program to solve very simple Sudoku puzzles
// ======================================================

int main() {
    
    int size;
    while (cin >> size) {
        // Read in the board size and create an empty board
        Sudoku board(size);
        
        // Read in and set the known positions in the board
        char c;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cin >> c;
                if (c != '.') {
                    board.Set(i,j,c-'0');
                }
            }
        }
        
        // The iterative solving routine
        while (1) {
            
            // Is the puzzle is already solved?
            if (board.IsSolved()) {
                cout << "\nPuzzle is solved:" << endl;
                board.Print();
                break;
            }
            
            // Is the puzzle impossible?
            if (board.Impossible()) {
                cout << "\nCannot solve this puzzle:" << endl;
                board.Print();
                break;
            }
            
            // Try to reduce the number of choices in one or more board cells
            // by propagating known values within each row, column, and quadrant
            int changed = 0;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (board.KnownValue(i,j))
                        changed += board.Propagate(i,j);
                }
            }
            
            // If nothing changed this iteration, give up
            if (changed == 0) {
                cout << "\nPuzzle is too difficult for this solver!" << endl;
                board.Print();
                break;
            }
        }
    }
}

// ======================================================

// Construct an empty board
Sudoku::Sudoku(int s) {
    // set the size
    size = s;
    quadrant_size = (int)sqrt(size);
    assert (quadrant_size*quadrant_size == s);
    
    // set the board
    set<int> set_tmp;
    for (int i = 1; i <= size; ++i) set_tmp.insert(i);
    for (unsigned int i = 0; i < size; ++i) {
        vector<set<int> > row_tmp;
        for (unsigned int j = 0; j < size; ++j) row_tmp.push_back(set_tmp);
        board.push_back(row_tmp);
    }
}

// To construct the puzzle, set the value of a particular cell
void Sudoku::Set(int i, int j, int value) {
    // make sure the value is one of the legal values
    assert (board[i][j].find(value) != board[i][j].end());
    board[i][j].clear();
    board[i][j].insert(value);
}

// Does the cell have exactly one legal value?
bool Sudoku::KnownValue(int i, int j) const {
    return (board[i][j].size() == 1);
}

// If there is exactly one number in each cell of the grid, the puzzle is solved!
bool Sudoku::IsSolved() const {
    for (unsigned int i = 0; i < board.size(); ++i) {
        for (unsigned int j = 0; j < board[i].size(); ++j) {
            if (!KnownValue(i, j)) return false;
        }
    }
    return true;
}

// If there are no legal choices in one or more cells of the grid, the puzzle is impossible
bool Sudoku::Impossible() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j].size() == 0) return true;
        }
    }
    return false;
}

// print out the solution
void Sudoku::Print() const {
    int solved = IsSolved();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int count = size+1;
            for (set<int>::iterator itr = board[i][j].begin(); itr != board[i][j].end(); itr++) {
                count--;
                cout << *itr;
            }
            if (!solved) {
                // if it's not solved, print out spaces to separate the values
                for (int k = 0; k < count; k++) cout << " ";
            }
        }
        cout << endl;
    }
}


// Propagate information from this cell along columns & rows &
// within quadrant. Return the number of cells that changed.
int Sudoku::Propagate(int i, int j) {
    int count = 0, value = *board[i][j].begin();
    // Check columns & rows
    for (int row = 0; row < size; ++row) {
        if (row != i) count += board[row][j].erase(value);
    }
    for (int col = 0; col < size; ++col) {
        if (col != j) count += board[i][col].erase(value);
    }
    // Check quadrant
    int row_block = i / quadrant_size;
    int col_block = j / quadrant_size;
    for (int row = row_block * quadrant_size;
         row < (row_block + 1) * quadrant_size;
         ++row) {
        for (int col = col_block * quadrant_size;
             col < (col_block + 1) * quadrant_size;
             ++col) {
            if (row != i && col != j) count += board[row][col].erase(value);
        }
    }
    
    return count;
    
}
