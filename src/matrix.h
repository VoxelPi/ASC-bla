#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>
#include <vector.h>

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

        Matrix transpose () {
            Matrix Mt (this->columns_, this->rows_);
            for (size_t i = 0; i < this->rows_; i++) {
                for (size_t j = 0; j < this->columns_; j++) {
                    Mt(j, i) = (*this)(i, j);
                }
            }
            return Mt;
        }

    };

    template <typename T, ORDERING ORD>
    Matrix<T, ORD> operator+(const Matrix<T, ORD> & a, const Matrix<T, ORD> & b)
    {
        Matrix<T, ORD> sum(a.Rows(), a.Columns());
        for (size_t i = 0; i < a.Rows(); i++) {
            for (size_t j = 0; j < a.Rows(); j++) {
                sum(i, j) = a(i, j) + b(i, j);
            }
        }
        return sum;
    }

    template <typename T, ORDERING ORD>
    Vector<T> operator*(const Matrix<T, ORD>& a, const Vector<T>& v)
    {
        Vector<T> result(a.Rows());
        for (size_t i = 0; i < a.Rows(); i++) {
            result(i) = 0;
            for (size_t j = 0; j < a.Columns(); j++) {
                result(i) += a(i, j) * v(j);
            }
        }
        return result;
    }

    template <typename T, ORDERING ORD>
    Matrix<T, ORD> operator*(const Matrix<T, ORD>& a, const Matrix<T, ORD>& b)
    {
        Matrix<T, ORD> result(a.Rows(), b.Columns());
        for (size_t i = 0; i < a.Rows(); i++) {
            for (size_t j = 0; j < b.Columns(); j++) {
                result(i, j) = 0;
                for (size_t k = 0; k < a.Columns(); ++k) {
                    result(i, j) += a(i, k) * b(k, j);
                }
            }
        }
        return result;
    }
  
    template <typename T, ORDERING ORD>
    std::ostream& operator<<(std::ostream& ost, const Matrix<T, ORD>& m)
    {
        for (size_t i = 0; i < m.Rows(); i++) {
            if (m.Columns() > 0) {
                ost << std::endl << m(i, 0);
            }
            for (size_t j = 1; j < m.Columns(); j++) {
                ost << ", " << m(i, j);
            }
        }
        return ost;
    }
}

#endif