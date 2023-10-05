#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

namespace bla
{
    enum ORDERING { ColMajor, RowMajor };
    template <typename T, ORDERING ORD>
    class Matrix {
        private:
        size_t rows_;
        size_t columns_;
        T * data_;
        
        public:
        Matrix (size_t rows, size_t columns) : rows_(rows), columns_(columns), data_(new T[rows*columns]) {}

        Matrix (const Matrix& m) : Matrix(m.rows_, m.columns_) {
            *this = m;
        }

        Matrix (Matrix&& m) : rows_(0), columns_(0), data_(nullptr) {
            std::swap(rows_, m.rows_);
            std::swap(columns_, m.columns_);
            std::swap(data_, m.data_);
        }

        ~Matrix () { 
            delete [] data_; 
        }
    
        Matrix& operator=(const Matrix& m2)
        {
            for (size_t i = 0; i < rows_*columns_; i++) {
                data_[i] = m2(i);
            }
            return *this;
        }

        Matrix& operator=(Matrix&& m2)
        {
            for (size_t i = 0; i < rows_*columns_; i++) {
                data_[i] = m2(i);
            }
            return *this;
        }
    
        size_t Rows() const {
            return rows_;
        }
    
        size_t Columns() const {
            return columns_;
        }

        T & operator()(size_t row, size_t column) {
            if (ORD == ColMajor) {
                return data_[row + column * rows_];
            } else {
                return data_[column + row * columns_];
            }
            
        }

        const T & operator()(size_t row, size_t column) const {
            if (ORD == ColMajor) {
                return data_[row + column * rows_];
            } else {
                return data_[column + row * columns_];
            }
        }
    };
}

#endif