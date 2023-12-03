#include <cstddef>    // std::size_t.
#include <stdexcept>  // std::runtime_error, std::invalid_argument, std::out_of_range.

#include <gtest/gtest.h>  // Google Test.

#include "matrix.hpp"  // setm::Matrix.

using namespace setm;

// Test fixture for Matrix class.
template<typename T>
class MatrixTest : public ::testing::Test {
protected:
    Matrix<T> createSampleMatrix() const {
        Matrix<T> matrix{ 3, 3 };
        for(std::size_t i{}; i < 3; ++i) {
            for(std::size_t j{}; j < 3; ++j) {
                matrix.setElement(i, j, static_cast<T>(i * 3 + j + 1));
            }
        }
        return matrix;
    }
};

// Tests for Matrix constructors and basic methods.
TYPED_TEST_SUITE_P(MatrixTest);

TYPED_TEST_P(MatrixTest, DefaultConstructor) {
    const Matrix<TypeParam> matrix{ 2, 2 };
    const Matrix<TypeParam> matrixWithDefault{ 2, 2, TypeParam{ 5 } };

    EXPECT_EQ(matrix.getRows(), 2);
    EXPECT_EQ(matrix.getCols(), 2);

    EXPECT_EQ(matrix.getElement(0, 0), TypeParam{});
    EXPECT_EQ(matrix.getElement(0, 1), TypeParam{});
    EXPECT_EQ(matrix.getElement(1, 0), TypeParam{});
    EXPECT_EQ(matrix.getElement(1, 1), TypeParam{});

    EXPECT_EQ(matrixWithDefault.getRows(), 2);
    EXPECT_EQ(matrixWithDefault.getCols(), 2);

    EXPECT_EQ(matrixWithDefault.getElement(0, 0), TypeParam{ 5 });
    EXPECT_EQ(matrixWithDefault.getElement(0, 1), TypeParam{ 5 });
    EXPECT_EQ(matrixWithDefault.getElement(1, 0), TypeParam{ 5 });
    EXPECT_EQ(matrixWithDefault.getElement(1, 1), TypeParam{ 5 });
}

TYPED_TEST_P(MatrixTest, ArrayConstructor) {
    const TypeParam array[4] = { 1, 2, 3, 4 };
    const Matrix<TypeParam> matrix{ array, 2, 2 };

    EXPECT_EQ(matrix.getElement(0, 0), 1);
    EXPECT_EQ(matrix.getElement(0, 1), 2);
    EXPECT_EQ(matrix.getElement(1, 0), 3);
    EXPECT_EQ(matrix.getElement(1, 1), 4);
}

TYPED_TEST_P(MatrixTest, CopyConstructor) {
    const Matrix<TypeParam> original{ this->createSampleMatrix() };
    const Matrix<TypeParam> copy{ original };

    EXPECT_EQ(copy, original);
}

TYPED_TEST_P(MatrixTest, MoveConstructor) {
    Matrix<TypeParam> original{ this->createSampleMatrix() };
    Matrix<TypeParam> moved{ std::move(original) };

    EXPECT_EQ(moved.getRows(), 3);
    EXPECT_EQ(moved.getCols(), 3);

    EXPECT_EQ(moved.getElement(0, 0), 1);
    EXPECT_EQ(moved.getElement(0, 1), 2);
    EXPECT_EQ(moved.getElement(0, 2), 3);
    EXPECT_EQ(moved.getElement(1, 0), 4);
    EXPECT_EQ(moved.getElement(1, 1), 5);
    EXPECT_EQ(moved.getElement(1, 2), 6);
    EXPECT_EQ(moved.getElement(2, 0), 7);
    EXPECT_EQ(moved.getElement(2, 1), 8);
    EXPECT_EQ(moved.getElement(2, 2), 9);
}

TYPED_TEST_P(MatrixTest, CopyAssignment) {
    const Matrix<TypeParam> original{ this->createSampleMatrix() };
    Matrix<TypeParam> copy;
    copy = original;

    EXPECT_EQ(copy, original);
}

TYPED_TEST_P(MatrixTest, MoveAssignment) {
    const Matrix<TypeParam> original{ this->createSampleMatrix() };
    Matrix<TypeParam> moved;

    moved = std::move(original);

    EXPECT_EQ(moved.getRows(), 3);
    EXPECT_EQ(moved.getCols(), 3);

    EXPECT_EQ(moved.getElement(0, 0), 1);
    EXPECT_EQ(moved.getElement(0, 1), 2);
    EXPECT_EQ(moved.getElement(0, 2), 3);
    EXPECT_EQ(moved.getElement(1, 0), 4);
    EXPECT_EQ(moved.getElement(1, 1), 5);
    EXPECT_EQ(moved.getElement(1, 2), 6);
    EXPECT_EQ(moved.getElement(2, 0), 7);
    EXPECT_EQ(moved.getElement(2, 1), 8);
    EXPECT_EQ(moved.getElement(2, 2), 9);
}

TYPED_TEST_P(MatrixTest, GetSetElement) {
    Matrix<TypeParam> matrix{ 2, 2 };

    matrix.setElement(0, 0, 1);
    matrix.setElement(0, 1, 2);
    matrix.setElement(1, 0, 3);
    matrix.setElement(1, 1, 4);

    EXPECT_EQ(matrix.getElement(0, 0), 1);
    EXPECT_EQ(matrix.getElement(0, 1), 2);
    EXPECT_EQ(matrix.getElement(1, 0), 3);
    EXPECT_EQ(matrix.getElement(1, 1), 4);
}

TYPED_TEST_P(MatrixTest, Transpose) {
    const Matrix<TypeParam> original{ this->createSampleMatrix() };
    Matrix<TypeParam> transposed = original.transpose();

    EXPECT_EQ(transposed.getRows(), original.getCols());
    EXPECT_EQ(transposed.getCols(), original.getRows());

    for(std::size_t i{}; i < original.getRows(); ++i) {
        for(std::size_t j{}; j < original.getCols(); ++j) {
            EXPECT_EQ(transposed.getElement(j, i), original.getElement(i, j));
        }
    }
}

TYPED_TEST_P(MatrixTest, Addition) {
    const Matrix<TypeParam> matrix1{ this->createSampleMatrix() };
    const Matrix<TypeParam> matrix2{ this->createSampleMatrix() };
    const Matrix<TypeParam> sum{ matrix1 + matrix2 };

    for(std::size_t i{}; i < matrix1.getRows(); ++i) {
        for(std::size_t j{}; j < matrix1.getCols(); ++j) {
            EXPECT_EQ(sum.getElement(i, j), matrix1.getElement(i, j) + matrix2.getElement(i, j));
        }
    }
}

TYPED_TEST_P(MatrixTest, Multiplication) {
    Matrix<TypeParam> matrix1{ 2, 3 };
    Matrix<TypeParam> matrix2{ 3, 2 };

    matrix1.setElement(0, 0, 1);
    matrix1.setElement(0, 1, 2);
    matrix1.setElement(0, 2, 3);
    matrix1.setElement(1, 0, 4);
    matrix1.setElement(1, 1, 5);
    matrix1.setElement(1, 2, 6);

    matrix2.setElement(0, 0, 7);
    matrix2.setElement(0, 1, 8);
    matrix2.setElement(1, 0, 9);
    matrix2.setElement(1, 1, 10);
    matrix2.setElement(2, 0, 11);
    matrix2.setElement(2, 1, 12);

    const Matrix<TypeParam> result{ matrix1 * matrix2 };

    EXPECT_EQ(result.getRows(), 2);
    EXPECT_EQ(result.getCols(), 2);

    EXPECT_EQ(result.getElement(0, 0), 58);
    EXPECT_EQ(result.getElement(0, 1), 64);
    EXPECT_EQ(result.getElement(1, 0), 139);
    EXPECT_EQ(result.getElement(1, 1), 154);
}

TYPED_TEST_P(MatrixTest, OutputOperator) {
    const Matrix<TypeParam> matrix{ this->createSampleMatrix() };

    testing::internal::CaptureStdout();
    std::cout << matrix;
    const std::string output{ testing::internal::GetCapturedStdout() };

    // Verify the output format based on the matrix elements.
    EXPECT_EQ(output, "1 2 3 \n4 5 6 \n7 8 9 \n");
}

TYPED_TEST_P(MatrixTest, InvalidConstruction) {
    EXPECT_THROW(Matrix<TypeParam>(nullptr, 2, 2), std::invalid_argument);
}

TYPED_TEST_P(MatrixTest, OutOfBoundsAccess) {
    Matrix<TypeParam> matrix{ 2, 2 };

    EXPECT_NO_THROW(matrix.setElement(1, 1, 42));
    EXPECT_THROW(matrix.setElement(2, 2, 42), std::out_of_range);
    EXPECT_THROW(matrix.getElement(2, 2), std::out_of_range);
}

TYPED_TEST_P(MatrixTest, EqualityOperator) {
    const Matrix<TypeParam> matrix1{ this->createSampleMatrix() };
    const Matrix<TypeParam> matrix2{ this->createSampleMatrix() };
    EXPECT_EQ(matrix1, matrix2);
}

TYPED_TEST_P(MatrixTest, InequalityOperator) {
    const Matrix<TypeParam> matrix1{ this->createSampleMatrix() };
    const Matrix<TypeParam> matrix2{ 4, 2 };  // Different dimensions.
    const Matrix<TypeParam> matrix3{ 3, 3 };  // Same dimensions but different data.

    EXPECT_NE(matrix1, matrix2);
    EXPECT_NE(matrix1, matrix3);
    EXPECT_NE(matrix2, matrix3);
}

TYPED_TEST_P(MatrixTest, MultiplicationWithEmptyMatrix) {
    const Matrix<TypeParam> emptyMatrix{ 0, 0 };
    const Matrix<TypeParam> matrix{ 2, 2 };

    EXPECT_THROW(matrix * emptyMatrix, std::runtime_error);
}


REGISTER_TYPED_TEST_SUITE_P(MatrixTest,
                            DefaultConstructor,
                            ArrayConstructor,
                            CopyConstructor,
                            MoveConstructor,
                            CopyAssignment,
                            MoveAssignment,
                            GetSetElement,
                            Transpose,
                            Addition,
                            Multiplication,
                            OutputOperator,
                            InvalidConstruction,
                            OutOfBoundsAccess,
                            EqualityOperator,
                            InequalityOperator,
                            MultiplicationWithEmptyMatrix);

// Register types for testing (e.g., int, double, float).
using TestTypes = ::testing::Types<int, double, float>;
INSTANTIATE_TYPED_TEST_SUITE_P(MatrixTests, MatrixTest, TestTypes);
