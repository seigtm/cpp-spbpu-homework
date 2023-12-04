#include "circle/circle.hpp"

#include <numbers>      // std::numbers::pi_v.
#include <stdexcept>    // std::invalid_argument.
#include <string_view>  // std::string_view.

namespace setm {

Circle::Circle(const Point& center, double radius)
    : center_{ center }, radius_{ radius } {
    if(radius_ <= 0) {
        throw std::invalid_argument("Invalid circle radius");
    }
}

double Circle::getArea() const {
    return std::numbers::pi_v<double> * radius_ * radius_;
}

void Circle::scale(double factor) {
    if(factor == 0.0) {
        throw std::invalid_argument("Invalid scale factor. Cannot scale by a factor of 0.");
    }

    radius_ *= factor;
}

Point Circle::getCenter() const {
    return center_;
}

std::string_view Circle::getName() const {
    return "CIRCLE";
}

}  // namespace setm
