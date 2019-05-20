#ifndef __Matrix_h_
#define __Matrix_h_

#include <iostream>

class Matrix {
public:
    // Constructor
    Matrix(unsigned int rows = 0,
           unsigned int cols = 0,
           double fill = 0) { create(rows, cols, fill); }
    Matrix(const Matrix& m) { copy(m); }
    Matrix& operator=(const Matrix& m);
    ~Matrix() { destroy(); }

    // Accessors
    const unsigned int& num_rows() const { return rows_; };
    const unsigned int& num_cols() const { return cols_; };
    bool get(const unsigned int& row,
             const unsigned int& col,
             double& value) const;
    double* get_row(const unsigned int& row) const;
    double* get_col(const unsigned int& col) const;

    // Operators
    bool operator== (const Matrix& m) const;
    bool operator!= (const Matrix& m) const;

    // Modifier
    bool set(const unsigned int& row, const unsigned int& col, double value);

    // Member functions
    void clear() { destroy(); }
    void multiply_by_coefficient(const double& coefficient);
    bool swap_row(const unsigned int& source, const unsigned int& target);
    void transpose();
    bool add(const Matrix& m);
    bool subtract(const Matrix& m);
    Matrix* quarter();

    // Extra Credit
    void resize(const unsigned int& new_rows,
                const unsigned int& new_cols,
                const double& value);

private:
    // Member variables
    unsigned int rows_, cols_;
    double **data_;

    // Private member functions: used for constructors or destructors
    void create(const unsigned int& rows,
                const unsigned int& cols,
                const double& fill);
    void copy(const Matrix& m);
    void destroy();
    
    // 4 implemented private member function to check:
    //     1. if a (row, col) position is valid,
    //     2. if a row number or a col number is valid for a matrix.
    //     3. if two matrices' dimension are same
    bool valid_pos(const unsigned int& row,
                   const unsigned int& col) const { return row < rows_ && col < cols_; }
    bool valid_row(const unsigned int& row) const { return row < rows_; }
    bool valid_col(const unsigned int& col) const { return col < cols_; }
    bool same_dim(const unsigned int& row,
                  const unsigned int& col) const { return row == rows_ && col == cols_; }
};

// Overloaded output operator
std::ostream& operator<< (std::ostream& out, const Matrix& m);

#endif
