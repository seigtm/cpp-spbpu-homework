#include "circle/circle.hpp"

#include <numbers>
#include <stdexcept>

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
    radius_ *= factor;
}

Point Circle::getCenter() const {
    return center_;
}

const char* Circle::getName() const {
    return "CIRCLE";
}

}  // namespace setm
