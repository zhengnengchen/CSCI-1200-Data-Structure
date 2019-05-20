#include <vector>
#include <set>
#include <iostream>

// a representation for a Sudoku board

class Sudoku {
public:
    
    // Construct an empty board
    Sudoku(int s);
    
    // To construct the puzzle, set the value of a particular cell
    void Set(int i, int j, int value);
    
    // Is the puzzle solved, or impossible?
    bool KnownValue(int i, int j) const;
    bool IsSolved() const;
    bool Impossible() const;
    
    // Propagate information from this cell along columns & rows &
    // within quadrant. Return the number of cells that changed.
    int Propagate(int i, int j);
    
    bool OnlyChoiceRows(int &changed);
    bool OnlyChoiceColumns(int &changed);
    bool OnlyChoiceQuad(int &changed);
    
    // output
    void Print() const;
    
private:
    
    // representation
    // a 2D grid of cells.  Each cell is the set of the possible values for the cell.
    std::vector<std::vector<std::set<int> > > board;
    int size;  // overall board dimensions
    int quadrant_size;  // dimensions of the quadrants
};
