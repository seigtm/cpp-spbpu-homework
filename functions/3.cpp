// 3. Write a function to compute the value of a definite integral.
//    a. The integrand expression can be hard-coded in the code.
//    b. Use numerical integration methods like rectangle or trapezoidal rule.
//    c. Determine accuracy using the Runge's rule.

#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include <string_view>

namespace setm::math {

/**
 * Trapezoidal method for computing an integral.
 *
 * @tparam Function Type of the function to be integrated.
 * @param function The function to be integrated.
 * @param lower_limit The lower limit of the integral.
 * @param upper_limit The upper limit of the integral.
 * @param num_steps The number of integration steps.
 * @return The value of the integral.
 */
template<class Function>
double trapezoidalIntegration(const Function& function,
                              double lower_limit,
                              double upper_limit,
                              unsigned num_steps) {
    if(num_steps == 0)
        return 0.0;

    const double step_size{ (upper_limit - lower_limit) / num_steps };
    double sum{ 0.5 * (function(lower_limit) + function(upper_limit)) };

    for(unsigned step{ 1 }; step < num_steps; ++step)
        sum += function(lower_limit + step * step_size);

    return step_size * sum;
}

/**
 * Function to compute an integral with a specified tolerance using the Runge rule.
 *
 * This function numerically integrates the provided function over the specified
 * interval [lower_limit, upper_limit] using an adaptive approach based on the
 * Runge rule until the specified tolerance is met.
 *
 * @tparam Function Type of the function to be integrated.
 * @param function The function to be integrated.
 * @param lower_limit The lower limit of the integral.
 * @param upper_limit The upper limit of the integral.
 * @param tolerance The desired tolerance for the integral calculation.
 * @return The value of the integral.
 *
 * @note The function uses the trapezoidal integration method for adaptive refinement.
 */
template<class Function>
double rungeRuleIntegration(const Function& function,
                            double lower_limit,
                            double upper_limit,
                            double tolerance) {
    const double THETA{ 1.0 / 3.0 };
    unsigned num_steps{ 1 };
    double prev_integral{ trapezoidalIntegration(function, lower_limit, upper_limit, num_steps) };
    double integral{ trapezoidalIntegration(function, lower_limit, upper_limit, 2 * num_steps) };

    while(THETA * std::abs(integral - prev_integral) > tolerance) {
        num_steps *= 2;
        prev_integral = integral;
        integral = trapezoidalIntegration(function, lower_limit, upper_limit, 2 * num_steps);
    }

    return integral;
}

/**
 * Generate a string representing the integral formula.
 *
 * @param lower_limit The lower limit of the integral.
 * @param upper_limit The upper limit of the integral.
 * @param function_name The name of the function to be integrated.
 * @return The integral formula string.
 */
inline std::string integralFormula(double lower_limit, double upper_limit, std::string_view function_name) {
    return "∫[" +
           std::to_string(lower_limit) +
           "→" +
           std::to_string(upper_limit) +
           "](" +
           function_name.data() +
           "(x)dx) = ";
}

}  // namespace setm::math

double SinX(double x) { return std::sin(x); }

int main() {
    constexpr double lower_limit{ 0.0 };                       // The lower limit of the integral.
    constexpr double upper_limit{ std::numbers::pi };          // The upper limit of the integral.
    constexpr double tolerance{ 1e-12 };                       // The minimum allowable tolerance.
    const auto sin_x{ [](double x) { return std::sin(x); } };  // The function.

    std::cout << "Result of integration: "
              << setm::math::integralFormula(lower_limit, upper_limit, "sin")
              << setm::math::rungeRuleIntegration(sin_x, lower_limit, upper_limit, tolerance) << "\n";
    //          << setm::math::rungeRuleIntegration(&SinX, lower_limit, upper_limit, tolerance) << "\n";
}
