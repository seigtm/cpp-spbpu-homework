// 4. Write a function to calculate the value of the given sum
//    at a specified point (x) with a specified absolute calculation error
//    (absError) and a maximum number of terms (nMax).

//    1/(sqrt(1+x)) = 1 - x/2 + (1*3*x^2)/(2*4) - (1*3*5*x^3)/(2*4*6) + ...,
//      where x belongs to the interval (-1, 1).

//    a. Absolute calculation error (absError) represents the modulus
//       of the first discarded term in the series.
//    b. If the term number exceeds nMax and the desired accuracy is not reached,
//       or if x does not fall within the specified interval (-1, 1),
//       the function should throw an exception.
//    c. Each subsequent term should be derived from the previous term;
//       the use of std::pow function is not allowed.

//    Write a program to output a table of calculated values
//    of the function within the specified interval (input the interval, step, and accuracy
//    from the STDIN), as well as the values obtained using
//    standard C++ functions. Add the <cmath> header for standard functions.

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

namespace setm::math {

/**
 * @brief Calculate the inverse square root of (1 + x) using a series expansion.
 *
 * This function approximates the inverse square root of (1 + x) using a series
 * expansion, where 'x' belongs to the interval (-1, 1).
 *
 * @param x The input value for which the inverse square root is to be calculated.
 * @param abs_error The absolute error to control the accuracy of the approximation.
 * @param n_max The maximum number of terms to use in the series expansion.
 * @return The calculated inverse square root of (1 + x).
 *
 * @throw std::runtime_error If 'x' is outside the valid range (-1.0 < x < 1.0),
 * or if the desired accuracy is not reached within the specified maximum number of terms.
 *
 * @details The series expansion used for the calculation is:
 *   1/(sqrt(1+x)) = 1 - x/2 + (1*3*x^2)/(2*4) - (1*3*5*x^3)/(2*4*6) + ...
 * @details This function iterates through the series until either the desired accuracy
 * is achieved or the maximum number of terms 'n_max' is reached.
 */
double inverseSqrtOfOnePlusX(double x, double abs_error, int n_max) {
    if(x <= -1.0 || x >= 1.0)
        throw std::runtime_error("Error: x is out of the valid range (-1.0 < x < 1.0).");

    double result{ 1.0 };  // First term in the series.
    double term{ 1.0 };    // Current term in the series.

    for(int i{ 1 }; i <= n_max; i += 2) {
        term *= -((x * i) / (i + 1));
        result += term;

        if(std::abs(term) < abs_error)
            return result;  // Reached the desired accuracy.
    }

    throw std::runtime_error("Error: the desired accurancy was not reached.");
}

}  // namespace setm::math

int main() {
    double interval_start{};
    double interval_end{};
    double step{};
    double abs_error{};
    int n_max{};

    std::cout << "Enter the start of the interval (-1 < x < 1): ";
    std::cin >> interval_start;
    std::cout << "Enter the end of the interval (-1 < x < 1): ";
    std::cin >> interval_end;
    std::cout << "Enter the step size: ";
    std::cin >> step;
    std::cout << "Enter the absolute error: ";
    std::cin >> abs_error;
    std::cout << "Enter the maximum number of terms (n_max): ";
    std::cin >> n_max;

    std::cout << "x\tCustom\tStandard\n";

    const int numSteps{ static_cast<int>((interval_end - interval_start) / step) };
    for(int i{}; i < numSteps; ++i) {
        try {
            const double x{ interval_start + i * step };
            const double customResult{ setm::math::inverseSqrtOfOnePlusX(x, abs_error, n_max) };
            const double stdResult{ 1.0 / std::sqrt(1 + x) };

            std::cout << std::fixed << std::setprecision(3)
                      << x << '\t' << customResult << '\t' << stdResult << '\n';
        } catch(const std::runtime_error &e) {
            std::cerr << e.what() << '\n';
        }
    }
}
