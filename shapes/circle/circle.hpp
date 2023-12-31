#pragma once

#include <string_view>  // std::string_view.

#include "point/point.hpp"  // setm::Point.
#include "shape/shape.hpp"  // setm::Shape.

namespace setm {

/**
 * @brief Represents a circle in a two-dimensional space.
 *
 * The Circle class is a concrete implementation of the Shape interface,
 * representing a circle defined by its center and radius.
 */
class Circle : public Shape {
public:
    /**
     * @brief Constructs a circle with the specified center and radius.
     *
     * @param center The center coordinates of the circle.
     * @param radius The radius of the circle.
     * @throws std::invalid_argument if the provided radius is not valid (not greater than 0).
     */
    Circle(const Point& center, double radius);

    /**
     * @brief Calculates and returns the area of the circle.
     * @return The area of the circle.
     */
    double getArea() const override;

    /**
     * @brief Scales the circle isotropically relative to its center by the specified factor.
     * @param factor The scaling factor.
     * @throws std::invalid_argument if the provided factor is not valid (is equal to 0).
     */
    void scale(double factor) override;

    /**
     * @brief Retrieves the center coordinates of the circle.
     * @return The center coordinates of the circle.
     */
    Point getCenter() const override;

    /**
     * @brief Gets the name of the shape (in this case, "CIRCLE").
     * @return The name of the shape as a C-style string.
     */
    std::string_view getName() const override;

private:
    Point center_;   // The center coordinates of the circle.
    double radius_;  // The radius of the circle.
};

}  // namespace setm
