#include "Matrix.h"

// Constructor
Matrix& Matrix::operator=(const Matrix& m) {
    if (*this != m) destroy();
    copy(m);
    return *this;
}

// 3 Accessors
bool Matrix::get(const unsigned int& row,
                        const unsigned int& col,
                        double& value) const {
    if (!valid_pos(row, col)) return false;
    value = data_[row][col];
    return true;
}

double* Matrix::get_row(const unsigned int& row) const {
    if (!valid_row(row)) return NULL;
    double *row_ptr = new double[cols_];
    for (unsigned int i = 0; i < cols_; ++i) row_ptr[i] = data_[row][i];
    return row_ptr;
}

double* Matrix::get_col(const unsigned int& col) const {
    if (!valid_col(col)) return NULL;
    double *col_ptr = new double[rows_];
    for (unsigned int i = 0; i < rows_; ++i) col_ptr[i] = *(data_[i]+col);
    return col_ptr;
}

// 2 Operators
bool Matrix::operator== (const Matrix& m) const {
    if (!same_dim(m.num_rows(), m.num_cols())) return false;
    for (unsigned int i = 0; i < rows_; ++i) {
        for (unsigned int j = 0; j < cols_; ++j) {
            double value;
            m.get(i, j, value);
            if (value != data_[i][j]) return false;
        }
    }
    return true;
}

bool Matrix::operator!= (const Matrix& m) const {
    if (*this == m) return false;
    else return true;
}

// Modifier
bool Matrix::set(const unsigned int& row,
                 const unsigned int& col,
                 double value) {
    if (!valid_pos(row, col)) return false;
    data_[row][col] = value;
    return true;
}

// 6 Member functions
void Matrix::multiply_by_coefficient(const double& coefficient) {
    for (unsigned int i = 0; i < rows_; ++i) {
        for (unsigned int j = 0; j < cols_; ++j) data_[i][j] *= coefficient;
    }
}

bool Matrix::swap_row(const unsigned int& source, const unsigned int& target) {
    if (!valid_row(source) || !valid_row(target)) return false;
    double *tmp_row = new double[cols_];
    for (unsigned int i = 0; i < cols_; ++i) {
        tmp_row[i] = data_[target][i];
        data_[source][i] = data_[target][i];
    }
    for (unsigned int i = 0; i < cols_; ++i) data_[target][i] = tmp_row[i];
    delete [] tmp_row;
    return true;
}

void Matrix::transpose() {
    unsigned int trows_ = cols_, tcols_ = rows_;
    if (data_ != NULL) {
        double **tdata_ = new double*[trows_];
        for (unsigned int i = 0; i < trows_; ++i) {
            tdata_[i] = new double[tcols_];
            for (unsigned int j = 0; j < tcols_; ++j) tdata_[i][j] = data_[j][i];
        }
        destroy();
        data_ = tdata_;
    }
    rows_ = trows_;
    cols_ = tcols_;
}

bool Matrix::add(const Matrix& m) {
    if (!same_dim(m.num_rows(), m.num_cols())) return false;
    for (unsigned int i = 0; i < rows_; ++i) {
        for (unsigned int j = 0; j < cols_; ++j) {
            double value;
            m.get(i, j, value);
            data_[i][j] += value;
        }
    }
    return true;
}

bool Matrix::subtract(const Matrix& m) {
    Matrix tmp_m(m);
    tmp_m.multiply_by_coefficient(-1);
    return add(tmp_m);
}

Matrix* Matrix::quarter() {
    Matrix *m_ptr = new Matrix[4];
    unsigned int add_rows = rows_ / 2;
    unsigned int rows = add_rows + rows_ % 2;
    unsigned int add_cols = cols_ / 2;
    unsigned int cols = add_cols + cols_ % 2;
    for (int k = 0; k < 4; ++k) {
        m_ptr[k].create(rows, cols, 0);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                if (k == 0) m_ptr[k].set(i, j, data_[i][j]);
                else if (k == 1) m_ptr[k].set(i, j, data_[i][j + add_cols]);
                else if (k == 2) m_ptr[k].set(i, j, data_[i + add_rows][j]);
                else m_ptr[3].set(i, j, data_[i + add_rows][j + add_cols]);
            }
        }
    }
    return m_ptr;
}

// 3 Private member functions
void Matrix::create(const unsigned int& rows,
            const unsigned int& cols,
            const double& fill) {
    rows_ = rows;
    cols_ = cols;
    if (rows_ == 0 || cols_ == 0) data_ = NULL;
    else {
        data_ = new double*[rows_];
        for (unsigned int i = 0; i < rows_; ++i) {
            data_[i] = new double[cols_];
            for (unsigned int j = 0; j < cols_; ++j) data_[i][j] = fill;
        }
    }
}

void Matrix::copy(const Matrix& m) {
    create(m.num_rows(), m.num_cols(), 0);
    for (unsigned int i = 0; i < rows_; ++i) {
        for (unsigned int j = 0; j < cols_; ++j) m.get(i, j, data_[i][j]);
    }
}

void Matrix::destroy() {
    if (data_ != NULL) {
        for (unsigned int i = 0; i < rows_; ++i) delete [] data_[i];
        delete [] data_;
        data_ = NULL;
    }
    rows_ = 0;
    cols_ = 0;
}

// Overloaded output operator
std::ostream& operator<< (std::ostream& out, const Matrix& m) {
    unsigned int rows = m.num_rows();
    unsigned int cols = m.num_cols();
    out << std::endl << rows << " x " << cols << " matrix:" << std::endl << "[ ";
    // Condition of outer for loop along with 1st line in this for loop makes
    // sure that if either dimension of matrix is 0, matrix will be printed out
    // as a empty matrix.
    for (unsigned int i = 0; i < rows; ++i) {
        if (cols == 0) break;
        if (i != 0) out << "  ";
        for (unsigned int j = 0; j < cols; ++j) {
            double value;
            m.get(i, j, value);
            out << value << " ";
        }
        if (i != rows - 1) out << std::endl;
    }
    out << "]" << std::endl;
    return out;
}

// Extra credit
void Matrix::resize(const unsigned int& new_rows,
            const unsigned int& new_cols,
            const double& value) {
    double **tdata_;
    // If either dimension of new matrix is 0, assign NULL pointer to data_.
    // Otherwise, create (dynamically allocate) new data_.
    if (new_rows == 0 || new_cols == 0) tdata_ = NULL;
    else {
        tdata_ = new double*[new_rows];
        for (unsigned int i = 0; i < new_rows; ++i) {
            tdata_[i] = new double[new_cols];
            for (unsigned int j = 0; j < new_cols; ++j) {
                if (i < rows_ && j < cols_) tdata_[i][j] = data_[i][j];
                else tdata_[i][j] = value;
            }
        }
    }
    
    // Deallocate old dynamically allocated data before assign new one
    destroy();
    
    data_ = tdata_;
    rows_ = new_rows;
    cols_ = new_cols;
}
