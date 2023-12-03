#pragma once

#include "point/point.hpp"
#include "shape/shape.hpp"

namespace setm {

/**
 * @brief Represents a rectangle in a two-dimensional space.
 *
 * The Rectangle class is a concrete implementation of the Shape interface,
 * representing a rectangle defined by its bottom-left and top-right coordinates.
 */
class Rectangle : public Shape {
public:
    /**
     * @brief Constructs a rectangle with the specified bottom-left and top-right coordinates.
     *
     * The rectangle is defined by two points: bottom-left and top-right. The bottom-left
     * point represents the lower-left corner, and the top-right point represents the
     * upper-right corner.
     *
     * @param bottomLeft The bottom-left coordinates of the rectangle.
     * @param topRight The top-right coordinates of the rectangle.
     * @throws std::invalid_argument if the provided coordinates are not valid.
     */
    Rectangle(const Point& bottomLeft, const Point& topRight);

    /**
     * @brief Calculates and returns the area of the rectangle.
     * @return The area of the rectangle.
     */
    double getArea() const override;

    /**
     * @brief Scales the rectangle isotropically relative to its center by the specified factor.
     * @param factor The scaling factor.
     */
    void scale(double factor) override;

    /**
     * @brief Retrieves the center coordinates of the rectangle.
     *
     * The center of the rectangle is considered as the point of intersection of its diagonals.
     *
     * @return The center coordinates of the rectangle.
     */
    Point getCenter() const override;

    /**
     * @brief Gets the name of the shape (in this case, "RECTANGLE").
     * @return The name of the shape as a C-style string.
     */
    const char* getName() const override;

private:
    Point bottomLeft_;  // The bottom-left coordinates of the rectangle.
    Point topRight_;    // The top-right coordinates of the rectangle.
};

}  // namespace setm
