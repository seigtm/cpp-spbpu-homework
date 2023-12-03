#include "shape/shape.hpp"

#include <compare>  // std::partial_ordering.

namespace setm {

std::partial_ordering Shape::operator<=>(const Shape& other) const {
    return getArea() <=> other.getArea();
}

}  // namespace setm
