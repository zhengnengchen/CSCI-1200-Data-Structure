#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>

// Global constant
const std::string ship_list[] = {"tanker", "cargo", "carrier", "battleship", "cruiser", "destroyer", "submarine"};

// 2 Helper classes to contain information about constraints and results
class Constraint {
public:
    Constraint(unsigned int r, unsigned int c, char c0) : row(r), col(c), cell(c0) {}
    unsigned int row, col;
    char cell;
};

class Result {
public:
    Result(unsigned int r, unsigned int c, unsigned int l, std::string s, bool h) : row(r), col(c), length(l), ship(s), horizontal(h) {}
    unsigned int row, col, length;
    std::string ship;
    bool horizontal;
};

// Helper function used to read in data from file
void read_input(std::istream& input,
                std::vector<std::string>& board,
                unsigned int& row_num,
                unsigned int& col_num,
                std::vector<unsigned int>& row_sum,
                std::vector<unsigned int>& col_sum,
                std::vector<bool>& inv_row_sum,
                std::vector<bool>& inv_col_sum,
                std::list<std::string>& ships,
                std::vector<Constraint>& constraints,
                bool& unknown_sum,
                bool& unknown_ship) {
    std::string tmp;
    while (input >> tmp) {
        if (tmp == std::string("board")) {
            input >> tmp;
            row_num = atoi(tmp.c_str());
            input >> tmp;
            col_num = atoi(tmp.c_str());
            
            std::string line(col_num, ' ');
            for (unsigned int i = 0; i < row_num; ++i) board.push_back(line);
        } else if (tmp == std::string("rows")) {
            for (unsigned int i = 0; i < row_num; ++i) {
                input >> tmp;
                if (tmp == std::string("?")) {
                    row_sum.push_back(col_num);
                    unknown_sum = true;
                    inv_row_sum.push_back(false);
                } else {
                    row_sum.push_back(atoi(tmp.c_str()));
                    inv_row_sum.push_back(true);
                }
            }
        } else if (tmp == std::string("cols")) {
            for (unsigned int i = 0; i < col_num; ++i) {
                input >> tmp;
                if (tmp == std::string("?")) {
                    col_sum.push_back(row_num);
                    unknown_sum = true;
                    inv_col_sum.push_back(false);
                } else {
                    col_sum.push_back(atoi(tmp.c_str()));
                    inv_col_sum.push_back(true);
                }
            }
        } else if (tmp == std::string("constraint")) {
            input >> tmp;
            unsigned int row = atoi(tmp.c_str());
            input >> tmp;
            unsigned int col = atoi(tmp.c_str());
            input >> tmp;
            char cell = tmp.c_str()[0];
            Constraint constraint(row, col, cell);
            constraints.push_back(constraint);
        } else {
            if (tmp == std::string("unknown")) unknown_ship = true;
            ships.push_back(tmp);
        }
    }
}

// Helper function used to return the length of ships
unsigned int find_length(const std::string& ship) {
    if (ship == std::string("tanker")) return 7;
    else if (ship == std::string("cargo")) return 6;
    else if (ship == std::string("carrier")) return 5;
    else if (ship == std::string("battleship")) return 4;
    else if (ship == std::string("cruiser")) return 3;
    else if (ship == std::string("destroyer")) return 2;
    else if (ship == std::string("submarine")) return 1;
    else return 0;
}

// Check if ship can be added on the location of board[i][j]
bool ship_addable(const std::vector<std::string>& board,
                  const unsigned int& row_num,
                  const unsigned int& col_num,
                  const std::vector<unsigned int>& row_sum,
                  const std::vector<unsigned int>& col_sum,
                  const std::vector<Constraint>& constraints,
                  const unsigned int& row,
                  const unsigned int& col,
                  const unsigned int& length,
                  bool horizontal) {
    // Find start positions of ship itself
    unsigned int row_start = row, col_start = col, row_end, col_end;
    // Find end positions of ship itself
    if (horizontal) {
        row_end = row + 1;
        col_end = col + length;
    } else {
        row_end = row + length;
        col_end = col + 1;
    }
    // Find adjacent cells' positions
    if (row_start > 0) row_start -= 1;
    if (row_end < row_num) row_end += 1;
    if (col_start > 0) col_start -= 1;
    if (col_end < col_num) col_end += 1;
    // Check ship and adjacent cells
    for (unsigned int i = row_start; i < row_end; ++i) {
        for (unsigned int j = col_start; j < col_end; ++j) {
            if (board[i][j] != ' ') return false;
        }
    }
    // Check if it meets the constraints
    if (constraints.size() != 0) {
        for (unsigned int i = 0; i < constraints.size(); ++i) {
            // constraint's point is located within adjacent cells
            if (row_start <= constraints[i].row &&
                constraints[i].row < row_end &&
                col_start <= constraints[i].col &&
                constraints[i].col < col_end) {
                if (horizontal &&
                    constraints[i].row == row &&
                    col <= constraints[i].col &&
                    constraints[i].col < col + length) {
                    // Right on the ship; ship is put into board horizontally
                    if (length == 1 && constraints[i].cell == 'o') return true;
                    else if (length > 1 &&
                             constraints[i].col == col &&
                             constraints[i].cell == '<') return true;
                    else if (length > 1 &&
                             constraints[i].col == col + length - 1 &&
                             constraints[i].cell == '>') return true;
                    else if (length > 1 &&
                             constraints[i].cell == 'X') return true;
                    else return false;
                } else if (!horizontal &&
                           row <= constraints[i].row &&
                           constraints[i].row < row + length &&
                           constraints[i].col == col) {
                    // Right on the ship; ship is put into board vertically
                    if (constraints[i].row == row &&
                        constraints[i].cell == '^') return true;
                    else if (constraints[i].row == row + length - 1 &&
                             constraints[i].cell == 'v') return true;
                    else if (constraints[i].cell == 'X') return true;
                    else return false;
                    // Check adjacent cells for open water
                } else if (constraints[i].cell == '_') return true;
                else return false;
            }
        }
    }
    return true;
}

// Helper function to add ship on board
void add_ship(std::vector<std::string>& board,
              std::vector<unsigned int>& row_sum,
              std::vector<unsigned int>& col_sum,
              std::vector<Result>& results,
              const unsigned int& row,
              const unsigned int& col,
              const std::string& ship,
              const unsigned int& length,
              bool horizontal) {
    if (horizontal) {
        // submarine
        if (length == 1) {
            board[row][col] = 'o';
            col_sum[col] -= 1;
        } else {
            // Ship that is longer than 1
            board[row][col] = '<';
            col_sum[col] -= 1;
            for (unsigned int i = 1; i < length - 1; ++i) {
                board[row][col + i] = 'X';
                col_sum[col + i] -= 1;
            }
            board[row][col + length - 1] = '>';
            col_sum[col + length - 1] -= 1;
        }
        row_sum[row] -= length;
    } else {
        // Ship that is longer than 1
        board[row][col] = '^';
        row_sum[row] -= 1;
        for (unsigned int i = 1; i < length - 1; ++i) {
            board[row + i][col] = 'X';
            row_sum[row + i] -= 1;
        }
        board[row + length - 1][col] = 'v';
        row_sum[row + length - 1] -= 1;
        col_sum[col] -= length;
    }
    results.push_back(Result(row, col, length, ship, horizontal));
}

// Helper function that remove last added ship from board. This function is
// added because I changed my algorithm from passing by value to passing by
// reference. Hence after calling a deeper recursive function, I need to remove
// what recursive function did to board and other variables.
void remove_ship(std::vector<std::string>& board,
                 std::vector<unsigned int>& row_sum,
                 std::vector<unsigned int>& col_sum,
                 std::vector<Result>& results,
                 const unsigned int& row,
                 const unsigned int& col,
                 const unsigned int& length,
                 bool horizontal,
                 std::list<std::string>& ships,
                 std::string& next_ship) {
    if (horizontal) {
        // last ship was added horizontally
        for (unsigned int i = 0; i < length; ++i) {
            board[row][col + i] = ' ';
            col_sum[col + i] += 1;
        }
        row_sum[row] += length;
    } else {
        // last ship was added vertically
        for (unsigned int i = 0; i < length; ++i) {
            board[row + i][col] = ' ';
            row_sum[row + i] += 1;
        }
        col_sum[col] += length;
    }
    // Update results and ships vectors
    results.pop_back();
    if (next_ship != std::string("")) ships.push_front(next_ship);
}

// Helper function to print solution.
void print_solution(const std::vector<std::string>& board,
                    const unsigned int& row_num,
                    const unsigned int& col_num,
                    const std::vector<unsigned int>& row_sum,
                    const std::vector<unsigned int>& col_sum,
                    const std::vector<unsigned int>& print_row_sum,
                    const std::vector<unsigned int>& print_col_sum,
                    const std::vector<Result>& results) {
    // Location and direction of each ship
    std::cout << "Solution:" << std::endl;
    for (unsigned int i = 0; i < results.size(); ++i) {
        std::cout.width(11); std::cout << std::left << results[i].ship;
        std::cout << results[i].row << ' ' << results[i].col;
        if (results[i].length > 1) {
            if (results[i].horizontal) std::cout << ' ' << "horizontal";
            else std::cout << ' ' << "vertical";
        }
        std::cout << std::endl;
    }
    // Print board
    std::cout << "+" << std::string(col_num, '-') << "+" << std::endl;
    for (unsigned int i = 0; i < row_num; ++i) {
        std::cout << "|" << board[i] << "|" << print_row_sum[i] - row_sum[i] << std::endl;
    }
    std::cout << "+" << std::string(col_num, '-') << "+" << std::endl;
    std::cout << " ";
    for (unsigned int i = 0; i < col_num; ++i) std::cout << print_col_sum[i] - col_sum[i];
    std::cout << std::endl << std::endl;
}

// Since not all repeating solutions can be excluded during recursion, this
// helper function is used to check if current solution is unique from existing
// solutions saved in global variable previous_solutions.
bool solution_existed(const std::vector<std::string>& board,
                      const std::vector<std::vector<std::string> >& previous_solutions) {
    for (unsigned int i = 0; i < previous_solutions.size(); ++i) {
        bool existed = true;
        for (unsigned int j = 0; j < board.size(); ++j) {
            if (board[j] != previous_solutions[i][j]) {
                existed = false;
                break;
            }
        }
        if (existed) return true;
    }
    return false;
}

// Declaration of recursive function
void find_solution(std::vector<std::string>& board,
                   const unsigned int& row_num,
                   const unsigned int& col_num,
                   std::vector<unsigned int>& row_sum,
                   std::vector<unsigned int>& col_sum,
                   const std::vector<bool>& inv_row_sum,
                   const std::vector<bool>& inv_col_sum,
                   const std::vector<unsigned int>& print_row_sum,
                   const std::vector<unsigned int>& print_col_sum,
                   std::list<std::string>& ships,
                   std::vector<Result>& results,
                   const std::vector<Constraint>& constraints,
                   std::vector<std::vector<std::string> >& previous_solutions,
                   const unsigned int& last_length,
                   bool& found,
                   bool find_all_solutions,
                   unsigned int& found_count,
                   bool unknown_sum,
                   bool unknown_ship);

// Each time processing only one ship. This helper function is extracted from
// main recursive function to reduce repeating work.
void process_one_ship(std::vector<std::string>& board,
                      const unsigned int& row_num,
                      const unsigned int& col_num,
                      std::vector<unsigned int>& row_sum,
                      std::vector<unsigned int>& col_sum,
                      const std::vector<bool>& inv_row_sum,
                      const std::vector<bool>& inv_col_sum,
                      const std::vector<unsigned int>& print_row_sum,
                      const std::vector<unsigned int>& print_col_sum,
                      std::list<std::string>& ships,
                      std::vector<Result>& results,
                      const std::vector<Constraint>& constraints,
                      std::vector<std::vector<std::string> >& previous_solutions,
                      bool& found,
                      bool find_all_solutions,
                      unsigned int& found_count,
                      bool unknown_sum,
                      bool unknown_ship,
                      const std::string& ship) {
    unsigned int length = find_length(ship);
    // Find in horizontal direction
    for (unsigned int i = 0; i < row_num; ++i) {
        // Skip those rows that don't have enough spaces
        if (length > row_sum[i]) continue;
        // Omit last few columns that don't have enough spaces
        for (unsigned int j = 0; j < col_num - length + 1; ++j) {
            unsigned int k = 0;
            for (; k < length; ++k) if (col_sum[j + k] < 1) break;
            if (k != length) {
                // Find next non-zero position
                j += k;
                continue;
            }
            if (ship_addable(board, row_num, col_num, row_sum, col_sum,
                             constraints, i, j, length, true)) {
                add_ship(board, row_sum, col_sum, results, i, j, ship,
                         length, true);
                std::string next_ship;
                if (ships.size() != 0) next_ship = ships.front();
                else next_ship = "";
                find_solution(board, row_num, col_num, row_sum, col_sum,
                              inv_row_sum, inv_col_sum, print_row_sum,
                              print_col_sum, ships, results, constraints,
                              previous_solutions, length, found,
                              find_all_solutions, found_count, unknown_sum,
                              unknown_ship);
                remove_ship(board, row_sum, col_sum, results, i, j,
                            length, true, ships, next_ship);
            }
            if (found && !find_all_solutions) break;
        }
        if (found && !find_all_solutions) break;
    }
    // Find in vertical direction
    if (length > 1 && (!found || find_all_solutions)) {
        for (unsigned int j = 0; j < col_num; ++j) {
            // Skip those columns that don't have enough spaces
            if (length > col_sum[j]) continue;
            // Omit last few rows that don't have enough spaces
            for (unsigned int i = 0; i < row_num - length + 1; ++i) {
                unsigned int k = 0;
                for (; k < length; ++k) if (row_sum[i + k] < 1) break;
                if (k != length) {
                    // Find next non-zero position
                    i += k;
                    continue;
                }
                if (ship_addable(board, row_num, col_num, row_sum,
                                 col_sum, constraints, i, j, length,
                                 false)) {
                    add_ship(board, row_sum, col_sum, results, i, j,
                             ship, length, false);
                    std::string next_ship;
                    if (ships.size() != 0) next_ship = ships.front();
                    else next_ship = "";
                    find_solution(board, row_num, col_num, row_sum, col_sum,
                                  inv_row_sum, inv_col_sum, print_row_sum,
                                  print_col_sum, ships, results, constraints,
                                  previous_solutions, length, found,
                                  find_all_solutions, found_count, unknown_sum,
                                  unknown_ship);
                    remove_ship(board, row_sum, col_sum, results, i, j,
                                length, false, ships, next_ship);
                }
                if (found && !find_all_solutions) break;
            }
            if (found && !find_all_solutions) break;
        }
    }
}

// Main recursion function that are similar to those code in main function. The
// only difference is that at the start of this function, we firstly add ship to
// board.
void find_solution(std::vector<std::string>& board,
                   const unsigned int& row_num,
                   const unsigned int& col_num,
                   std::vector<unsigned int>& row_sum,
                   std::vector<unsigned int>& col_sum,
                   const std::vector<bool>& inv_row_sum,
                   const std::vector<bool>& inv_col_sum,
                   const std::vector<unsigned int>& print_row_sum,
                   const std::vector<unsigned int>& print_col_sum,
                   std::list<std::string>& ships,
                   std::vector<Result>& results,
                   const std::vector<Constraint>& constraints,
                   std::vector<std::vector<std::string> >& previous_solutions,
                   const unsigned int& last_length,
                   bool& found,
                   bool find_all_solutions,
                   unsigned int& found_count,
                   bool unknown_sum,
                   bool unknown_ship) {
    if (ships.size() == 0) {
        // Excluding those solutions that are identical to previous ones. Ships
        // with the same length cause identical solutions. Also, excluding those
        // solutions that cannot satidfy constraints if there exists any
        // constraint. Further more, if there are unknown things, checking if
        // known row_sum and col_sum is satisfied.
        if (previous_solutions.size() != 0 &&
            solution_existed(board, previous_solutions)) return;
        if (constraints.size() != 0) {
            for (unsigned int i = 0; i < constraints.size(); ++i) {
                if (board[constraints[i].row][constraints[i].col] != constraints[i].cell)
                    return;
            }
        }
        if (unknown_sum || unknown_ship) {
            for (unsigned int i = 0; i < row_num; ++i) {
                if (inv_row_sum[i] && row_sum[i] != 0) return;
            }
            for (unsigned int i = 0; i < col_num; ++i) {
                if (inv_col_sum[i] && col_sum[i] != 0) return;
            }
        }
        found = true;
        found_count += 1;
        previous_solutions.push_back(board);
        print_solution(board, row_num, col_num, row_sum, col_sum, print_row_sum,
                       print_col_sum, results);
    } else {
        // Remove and take the first element of ships as current node
        std::string ship(ships.front());
        ships.pop_front();
        if (ship == std::string("unknown")) {
            // If we meet a unknown ship, check if we can pruning some choices
            unsigned int designated_length = 0;
            if (*std::max_element(row_sum.begin(), row_sum.end()) > row_num / 2 + row_num % 2)
                designated_length = *std::max_element(row_sum.begin(), row_sum.end());
            else if (*std::max_element(col_sum.begin(), col_sum.end()) > col_num / 2 + col_num % 2)
                designated_length = *std::max_element(col_sum.begin(), col_sum.end());
            // Find in horizontal direction
            for (unsigned int u = 0; u < 7; ++u) {
                if (designated_length != 0) {
                    // Pruning irrelevent solutions
                    while (find_length(ship_list[u]) > designated_length) u += 1;
                } else {
                    // If there are multiple unknown ships, suppose they are in
                    // decreasing order
                    while (find_length(ship_list[u]) > last_length) u += 1;
                }
                ship = ship_list[u];
                process_one_ship(board, row_num, col_num, row_sum, col_sum,
                                 inv_row_sum, inv_col_sum, print_row_sum,
                                 print_col_sum, ships, results, constraints,
                                 previous_solutions, found,
                                 find_all_solutions, found_count, unknown_sum,
                                 unknown_ship, ship);
                if (found && !find_all_solutions) break;
                if (designated_length != 0) break;
            }
        } else {
            process_one_ship(board, row_num, col_num, row_sum, col_sum,
                             inv_row_sum, inv_col_sum, print_row_sum,
                             print_col_sum, ships, results, constraints,
                             previous_solutions, found,
                             find_all_solutions, found_count, unknown_sum,
                             unknown_ship, ship);
        }
    }
}

// Helper funciton used to sort ships list
bool longer_ship(const std::string& ship1, const std::string& ship2) {
    return find_length(ship1) > find_length(ship2) && ship1 != std::string("unknown");
}

int main(int argc, char* argv[]) {
    // check command-line argument and open file
    if (argc != 2 && argc != 3) {
        std::cerr << "Usage ./hw6 [INPUT-FILE] [OPTIONAL: find_all_solutions]" << std::endl;
        return 1;
    }
    std::ifstream input_file(argv[1]);
    if (!input_file.good()) {
        std::cerr << "Can't open " << argv[1] << " to read." << std::endl;
        return 1;
    }
    bool find_all_solutions = false;
    if (argc == 3) {
        if (argv[2] != std::string("find_all_solutions")) {
            std::cerr << "Usage ./hw6 [INPUT-FILE] [OPTIONAL: find_all_solutions]" << std::endl;
            return 1;
        } else find_all_solutions = true;
    }
    
    // Useful variables
    bool found = false, unknown_sum = false, unknown_ship = false;
    unsigned int row_num = 0, col_num = 0, found_count = 0;
    
    // initialize a series of containers and read in data from file
    std::vector<std::string> board;
    std::vector<unsigned int> row_sum, col_sum;
    std::vector<bool> inv_row_sum, inv_col_sum;
    std::vector<unsigned int> print_row_sum, print_col_sum;
    std::list<std::string> ships;
    std::vector<Result> results;
    std::vector<Constraint> constraints;
    std::vector<std::vector<std::string> > previous_solutions;
    
    read_input(input_file, board, row_num, col_num, row_sum, col_sum,
               inv_row_sum, inv_col_sum, ships, constraints, unknown_sum,
               unknown_ship);
    print_row_sum = row_sum;
    print_col_sum = col_sum;
    
    ships.sort(longer_ship); // sort ships vector from longest ships to shortest
    
    // Call recursive function to find results and print necessary information
    find_solution(board, row_num, col_num, row_sum, col_sum, inv_row_sum,
                  inv_col_sum, print_row_sum, print_col_sum, ships, results,
                  constraints, previous_solutions, 7, found, find_all_solutions,
                  found_count, unknown_sum, unknown_ship);
    if (found_count == 0) std::cout << "No solution" << std::endl;
    else if (find_all_solutions ||
             (find_all_solutions && (unknown_ship || unknown_sum)))
        std::cout << "Found " << found_count << " solution(s)" << std::endl;
    
    return 0;
}
