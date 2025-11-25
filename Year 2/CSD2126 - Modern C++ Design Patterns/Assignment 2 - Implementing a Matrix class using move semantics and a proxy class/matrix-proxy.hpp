// Don't forget file-header and function-level Doxygen documentation blocks!!!

// First, define the class template. Then, define the member functions of the class template
// OUTSIDE the class definition. The automatic grader will not be able to check for this - 
// however, the manual grader can. Occurrences of EACH such function defined in the class definition
//  will result in a deduction of ONE LETTER GRADE!!! You're forewarned!!!

// This is how you should implement the assignment:

#ifndef MATRIX_PROXY_HPP
#define MATRIX_PROXY_HPP

// include necessary headers ...
#include <initializer_list>
#include <algorithm>

namespace HLP3
{
    template <typename T>
    class Matrix
    {
    public:
        using size_type = size_t;
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;

        class RowProxy
        {
        public:
            RowProxy(pointer row, size_type cols);
            reference operator[](size_type col);
        private:
            pointer row_;
            size_type cols_;
        };

        class ConstRowProxy
        {
        public:
            ConstRowProxy(const_pointer row, size_type cols);
            const_reference operator[](size_type col) const;
        private:
            const_pointer row_;
            size_type cols_;
        };

    public:
        Matrix(size_type nr, size_type nc);
        Matrix(Matrix const& rhs);
        Matrix(Matrix&& rhs) noexcept;
        Matrix(std::initializer_list<std::initializer_list<value_type>> list);
        ~Matrix() noexcept;
        Matrix& operator=(Matrix const& rhs);
        Matrix& operator=(Matrix&& rhs) noexcept;

        size_type get_rows() const noexcept;
        size_type get_cols() const noexcept;

        RowProxy operator[](size_type r);
        ConstRowProxy operator[](size_type r) const;

    private:
        size_type rows;
        size_type cols;
        pointer data;
    };
    
    // RowProxy member functions
    template <typename T>
    Matrix<T>::RowProxy::RowProxy(pointer row, size_type cols)
        : row_(row), cols_(cols) {}

    template <typename T>
    typename Matrix<T>::reference Matrix<T>::RowProxy::operator[](size_type c)
    {
        if (c >= cols_)
        {
            throw std::out_of_range("Column index out of range");
        }
        return row_[c];
    }

    // ConstRowProxy member functions
    template <typename T>
    Matrix<T>::ConstRowProxy::ConstRowProxy(const_pointer row, size_type cols)
        : row_(row), cols_(cols) {}

    template <typename T>
    typename Matrix<T>::const_reference Matrix<T>::ConstRowProxy::operator[](size_type c) const
    {
        if (c >= cols_)
        {
            throw std::out_of_range("Column index out of range");
        }
        return row_[c];
    }

    // Matrix member functions
    template <typename T>
    Matrix<T>::Matrix(size_type nr, size_type nc)
    : rows(nr), cols(nc), data(new value_type[rows * cols]) {}

    template <typename T>
    Matrix<T>::Matrix(Matrix<T> const& rhs)
    : rows(rhs.rows), cols(rhs.cols), data(new value_type[rows * cols])
    {
        std::copy(rhs.data, rhs.data + (rows * cols), data);
    }

    template <typename T>
    Matrix<T>::Matrix(Matrix<T>&& rhs) noexcept
    : rows(rhs.rows), cols(rhs.cols), data(rhs.data)
    {
        rhs.rows = 0;
        rhs.cols = 0;
        rhs.data = nullptr;
    }

    template <typename T>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<value_type>> list)
    : rows(list.size()), cols(list.begin()->size()), data(new value_type[rows * cols])
    {
        size_type r = 0;
        for (const auto& row : list)
        {
            if (row.size() != cols)
            {
                delete[] data;
                throw std::runtime_error("bad initializer list");
            }
            std::copy(row.begin(), row.end(), data + r * cols);
            ++r;
        }
    }

    template <typename T>
    Matrix<T>::~Matrix() noexcept
    {
        delete[] data;
    }

    template <typename T>
    typename Matrix<T>::Matrix& Matrix<T>::operator=(Matrix<T> const& rhs)
    {
        Matrix tmp(rhs);
        std::swap(rows, tmp.rows);
        std::swap(cols, tmp.cols);
        std::swap(data, tmp.data);

        return *this;
    }

    template <typename T>
    typename Matrix<T>::Matrix& Matrix<T>::operator=(Matrix<T>&& rhs) noexcept
    {
        delete[] data;
        rows = rhs.rows;
        cols = rhs.cols;
        data = rhs.data;
        rhs.rows = 0;
        rhs.cols = 0;
        rhs.data = nullptr;

        return *this;
    }

    template <typename T>
    typename Matrix<T>::size_type Matrix<T>::get_rows() const noexcept
    {
        return rows;
    }

    template <typename T>
    typename Matrix<T>::size_type Matrix<T>::get_cols() const noexcept
    {
        return cols;
    }

    template <typename T>
    typename Matrix<T>::RowProxy Matrix<T>::operator[](size_type r)
    {
        if (r >= rows)
        {
            throw std::out_of_range("Row index out of range");
        }
        
        return RowProxy(data + r * cols, cols);
    }

    template <typename T>
    typename Matrix<T>::ConstRowProxy Matrix<T>::operator[](size_type r) const
    {
        if (r >= rows)
        {
            throw std::out_of_range("Row index out of range");
        }
        
        return ConstRowProxy(data + r * cols, cols);
    }

    // Global functions of Matrix API
    template <typename T>
    Matrix<T> operator+(const Matrix<T>& M, const Matrix<T>& N)
    {
        if (M.get_rows() != N.get_rows() || M.get_cols() != N.get_cols())
        {
            throw std::runtime_error("operands for matrix addition must have same dimensions");
        }

        Matrix<T> result(M.get_rows(), M.get_cols());
        for (typename Matrix<T>::size_type i = 0; i < M.get_rows(); ++i)
        {
            for (typename Matrix<T>::size_type j = 0; j < M.get_cols(); ++j)
            {
                result[i][j] = M[i][j] + N[i][j];
            }
        }
        return result;
    }

    template <typename T>
    Matrix<T> operator-(const Matrix<T>& M, const Matrix<T>& N)
    {
        if (M.get_rows() != N.get_rows() || M.get_cols() != N.get_cols())
        {
            throw std::runtime_error("operands for matrix subtraction must have same dimensions");
        }

        Matrix<T> result(M.get_rows(), M.get_cols());
        for (typename Matrix<T>::size_type i = 0; i < M.get_rows(); ++i)
        {
            for (typename Matrix<T>::size_type j = 0; j < M.get_cols(); ++j)
            {
                result[i][j] = M[i][j] - N[i][j];
            }
        }
        return result;
    }

    template <typename T>
    Matrix<T> operator*(const Matrix<T>& M, const Matrix<T>& N)
    {
        if (M.get_cols() != N.get_rows())
        {
            throw std::runtime_error("number of columns in left operand must match number of rows in right operand");
        }

        Matrix<T> result(M.get_rows(), N.get_cols());
        for (typename Matrix<T>::size_type i = 0; i < M.get_rows(); ++i)
        {
            for (typename Matrix<T>::size_type j = 0; j < N.get_cols(); ++j)
            {
                T sum = T();
                for (typename Matrix<T>::size_type k = 0; k < M.get_cols(); ++k)
                {
                    sum += M[i][k] * N[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    template <typename T>
    Matrix<T> operator*(const T& r, const Matrix<T>& M)
    {
        Matrix<T> result(M.get_rows(), M.get_cols());
        for (typename Matrix<T>::size_type i = 0; i < M.get_rows(); ++i)
        {
            for (typename Matrix<T>::size_type j = 0; j < M.get_cols(); ++j)
            {
                result[i][j] = r * M[i][j];
            }
        }
        return result;
    }

    template <typename T>
    bool operator==(const Matrix<T>& M, const Matrix<T>& N)
    {
        if (M.get_rows() != N.get_rows() || M.get_cols() != N.get_cols())
        {
            return false;
        }

        for (typename Matrix<T>::size_type i = 0; i < M.get_rows(); ++i)
        {
            for (typename Matrix<T>::size_type j = 0; j < M.get_cols(); ++j)
            {
                if (M[i][j] != N[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    template <typename T>
    bool operator!=(const Matrix<T>& M, const Matrix<T>& N)
    {
        return !(M == N);
    }
}
#endif