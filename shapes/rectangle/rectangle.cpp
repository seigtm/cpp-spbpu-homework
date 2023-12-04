#include "rectangle/rectangle.hpp"

#include <stdexcept>    // std::invalid_argument.
#include <string_view>  // std::string_view.

#include "point/point.hpp"  // setm::Point.
#include "shape/shape.hpp"  // setm::Shape.

namespace setm {

Rectangle::Rectangle(const Point& bottomLeft, const Point& topRight)
    : bottomLeft_{ bottomLeft }, topRight_{ topRight } {
    if(bottomLeft_.x >= topRight_.x || bottomLeft_.y >= topRight_.y) {
        throw std::invalid_argument("Invalid rectangle coordinates");
    }
}

double Rectangle::getArea() const {
    const double width{ topRight_.x - bottomLeft_.x };
    const double height{ topRight_.y - bottomLeft_.y };
    return width * height;
}

void Rectangle::scale(double factor) {
    const Point center{ getCenter() };
    bottomLeft_.x = center.x + (bottomLeft_.x - center.x) * factor;
    bottomLeft_.y = center.y + (bottomLeft_.y - center.y) * factor;
    topRight_.x = center.x + (topRight_.x - center.x) * factor;
    topRight_.y = center.y + (topRight_.y - center.y) * factor;
}

Point Rectangle::getCenter() const {
    return { (bottomLeft_.x + topRight_.x) / 2, (bottomLeft_.y + topRight_.y) / 2 };
}

std::string_view Rectangle::getName() const {
    return "RECTANGLE";
}

}  // namespace setm
