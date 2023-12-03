/**
 * @file matrix.hpp
 * @brief Implementation of the Matrix class.
 *
 * Develop the specified classes.
 * - Prohibited to use STL containers and algorithms.
 * - Implement necessary constructors.
 * - Implement destructor, copy constructors, move constructors, copy assignment operators,
 *   and move assignment operators.
 * - Memory should be allocated and deallocated correctly.
 * - Implement methods for working with objects (consider how objects will be used).
 * - Some methods can be implemented as overloaded operators (if suitable in meaning).
 * - Implement the << operator for printing information to the stream.
 * - The class declaration should be in the header file (.hpp), and method definitions in
 *   the implementation file (.cpp). The class template is fully described in the header file.
 * - Demonstrate the functionality of all methods, operators, and constructors.
 *
 *  Task: Develop the class for working with matrices. Methods for addition, multiplication, transposition
 *    of matrices. Methods for getting and setting arbitrary matrix elements (with arbitrary indices).
 */

#pragma once

#include <cstddef>    // std::size_t.
#include <ostream>    // std::ostream.
#include <stdexcept>  // std::runtime_error, std::invalid_argument, std::bad_alloc, std::out_of_range.

namespace setm {

/**
 * @brief A class for working with matrices.
 *
 * This class provides functionality for creating, manipulating, and performing operations on matrices.
 * The matrices can be of different types, specified by the template parameter T.
 */
template<typename T>
class Matrix {
public:
    /**
     * @brief Default constructor.
     * @param rows The number of rows in the matrix.
     * @param cols The number of columns in the matrix.
     * @param defaultValue The default value for matrix elements.
     * @details Initializes the matrix with the specified number of rows and columns,
     *          setting each element to the provided default value.
     *          If the dimensions are {0, 0}, the matrix is initialized as empty (nullptr).
     * @throw std::bad_alloc If memory allocation fails for a non-empty matrix.
     */
    Matrix(std::size_t rows = {}, std::size_t cols = {}, T defaultValue = T{});

    /**
     * @brief Constructor to initialize the matrix with an array.
     * @param array Pointer to the array representing the matrix data.
     * @param rows The number of rows in the matrix.
     * @param cols The number of columns in the matrix.
     * @throw std::invalid_argument If the input array is nullptr or the dimensions are zero.
     */
    Matrix(const T* const array, std::size_t rows, std::size_t cols);

    /**
     * @brief Copy constructor.
     * @param other The matrix to be copied.
     * @throw std::bad_alloc If memory allocation for the copy fails.
     */
    Matrix(const Matrix& other);

    /**
     * @brief Move constructor.
     * @param other The matrix to be moved.
     */
    Matrix(Matrix&& other) noexcept;

    /**
     * @brief Destructor.
     */
    ~Matrix();

    /**
     * @brief Copy assignment operator.
     * @param other The matrix to be copied.
     * @return Reference to the assigned matrix.
     * @throw std::bad_alloc If memory allocation for the copy fails.
     */
    Matrix& operator=(const Matrix& other);

    /**
     * @brief Move assignment operator.
     * @param other The matrix to be moved.
     * @return Reference to the assigned matrix.
     */
    Matrix& operator=(Matrix&& other) noexcept;

    /**
     * @brief Get the number of rows in the matrix.
     * @return The number of rows.
     */
    std::size_t getRows() const;

    /**
     * @brief Get the number of columns in the matrix.
     * @return The number of columns.
     */
    std::size_t getCols() const;

    /**
     * @brief Get the element at the specified row and column.
     * @param row The row index.
     * @param col The column index.
     * @return The value of the element.
     * @throws std::out_of_range If the provided indices are out of bounds.
     */
    T getElement(std::size_t row, std::size_t col) const;

    /**
     * @brief Set the element at the specified row and column.
     * @param row The row index.
     * @param col The column index.
     * @param value The value to set.
     * @throws std::out_of_range If the provided indices are out of bounds.
     */
    void setElement(std::size_t row, std::size_t col, T value);

    /**
     * @brief Transpose the matrix.
     * @return The transposed matrix.
     */
    Matrix transpose() const;

    /**
     * @brief Perform matrix addition.
     * @param other The matrix to be added.
     * @return The result of the addition.
     * @throw std::runtime_error If matrix dimensions do not match for addition.
     */
    Matrix operator+(const Matrix& other) const;

    /**
     * @brief Perform matrix multiplication.
     * @param other The matrix to be multiplied.
     * @return The result of the multiplication.
     * @throw std::runtime_error If matrix dimensions do not match for multiplication.
     */
    Matrix operator*(const Matrix& other) const;

    /**
     * @brief Equality comparison operator.
     * @param other The matrix to be compared.
     * @return True if matrices are equal, false otherwise.
     */
    bool operator==(const Matrix& other) const;

    /**
     * @brief Inequality comparison operator.
     * @param other The matrix to be compared.
     * @return True if matrices are not equal, false otherwise.
     */
    bool operator!=(const Matrix& other) const;

    /**
     * @brief Overloaded stream output operator to print the matrix.
     * @param os The output stream.
     * @param matrix The matrix to be printed.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        for(std::size_t i{}; i < matrix.getRows(); ++i) {
            for(std::size_t j{}; j < matrix.getCols(); ++j) {
                os << matrix.getElement(i, j) << ' ';
            }
            os << '\n';
        }
        return os;
    }

private:
    /**
     * @brief Helper function for comparing data.
     * @param other The matrix to be compared.
     * @return True if data is equal, false otherwise.
     */
    bool compareData(const Matrix& other) const;

    std::size_t rows{};  // Number of rows in the matrix.
    std::size_t cols{};  // Number of columns in the matrix.
    T* data{ nullptr };  // Pointer to the dynamically allocated matrix data.
};


template<typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols, T defaultValue)
    : rows{ rows }, cols{ cols } {
    if(rows > 0 && cols > 0) {
        try {
            data = new T[rows * cols];
        } catch(const std::bad_alloc&) {
            delete[] data;
            throw;  // Rethrow the exception.
        }

        for(std::size_t i{}; i < rows * cols; ++i) {
            data[i] = defaultValue;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(const T* const array, std::size_t rows, std::size_t cols)
    : rows{ rows }, cols{ cols } {
    if(array == nullptr || rows * cols == 0) {
        throw std::invalid_argument("Invalid input array or dimensions");
    }

    try {
        data = new T[rows * cols];
    } catch(const std::bad_alloc&) {
        delete[] data;
        throw;  // Rethrow the exception.
    }

    for(std::size_t i{}; i < rows * cols; ++i) {
        data[i] = array[i];
    }
}

template<typename T>
Matrix<T>::~Matrix() {
    delete[] data;
}

template<typename T>
Matrix<T>::Matrix(const Matrix& other)
    : rows{ other.rows }, cols{ other.cols } {
    try {
        data = new T[rows * cols];
    } catch(const std::bad_alloc&) {
        delete[] data;
        throw;  // Rethrow the exception.
    }

    for(std::size_t i{}; i < rows * cols; ++i) {
        data[i] = other.data[i];
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : rows{ other.rows }, cols{ other.cols }, data{ other.data } {
    other.rows = 0;
    other.cols = 0;
    other.data = nullptr;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    if(this != &other) {
        delete[] data;

        rows = other.rows;
        cols = other.cols;

        try {
            data = new T[rows * cols];
        } catch(const std::bad_alloc&) {
            delete[] data;
            throw;  // Rethrow the exception.
        }

        for(std::size_t i = 0; i < rows * cols; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
    if(this != &other) {
        delete[] data;

        rows = other.rows;
        cols = other.cols;
        data = other.data;

        other.rows = 0;
        other.cols = 0;
        other.data = nullptr;
    }
    return *this;
}

template<typename T>
std::size_t Matrix<T>::getRows() const {
    return rows;
}

template<typename T>
std::size_t Matrix<T>::getCols() const {
    return cols;
}

template<typename T>
T Matrix<T>::getElement(std::size_t row, std::size_t col) const {
    if(row < rows && col < cols) {
        return data[row * cols + col];
    } else {
        // Handle out-of-bounds error (throw an exception).
        throw std::out_of_range("Matrix indices out of bounds");
    }
}

template<typename T>
void Matrix<T>::setElement(std::size_t row, std::size_t col, T value) {
    if(row < rows && col < cols) {
        data[row * cols + col] = value;
    } else {
        // Handle out-of-bounds error (throw an exception).
        throw std::out_of_range("Matrix indices out of bounds");
    }
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result{ cols, rows };
    for(std::size_t i{}; i < rows; ++i) {
        for(std::size_t j{}; j < cols; ++j) {
            result.data[j * rows + i] = data[i * cols + j];
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
    if(rows != other.rows || cols != other.cols) {
        throw std::runtime_error("Matrix dimensions do not match for addition (" +
                                 std::to_string(rows) +
                                 "x" +
                                 std::to_string(cols) +
                                 " and " +
                                 std::to_string(other.rows) +
                                 "x" +
                                 std::to_string(other.cols) +
                                 ")");
    }

    Matrix<T> result{ rows, cols };
    for(std::size_t i{}; i < rows * cols; ++i) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const {
    if(cols != other.rows) {
        throw std::runtime_error("Matrix dimensions do not match for multiplication (" +
                                 std::to_string(rows) +
                                 "x" +
                                 std::to_string(cols) +
                                 " and " +
                                 std::to_string(other.rows) +
                                 "x" +
                                 std::to_string(other.cols) +
                                 ")");
    }

    Matrix<T> result{ rows, other.cols };
    for(std::size_t i{}; i < rows; ++i) {
        for(std::size_t j{}; j < other.cols; ++j) {
            result.data[i * other.cols + j] = 0;
            for(std::size_t k{}; k < cols; ++k) {
                result.data[i * other.cols + j] += data[i * cols + k] * other.data[k * other.cols + j];
            }
        }
    }
    return result;
}

template<typename T>
bool Matrix<T>::compareData(const Matrix& other) const {
    for(std::size_t i{}; i < rows * cols; ++i) {
        if(data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix& other) const {
    return rows == other.rows && cols == other.cols && compareData(other);
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix& other) const {
    return !(*this == other);
}

}  // namespace setm
