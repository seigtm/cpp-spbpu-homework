#pragma once

#include <compare>  // std::partial_ordering.

#include "point/point.hpp"

namespace setm {

/**
 * @brief Abstract base class representing a geometric shape.
 *
 * This class defines the interface for geometric shapes, providing methods
 * to retrieve the area, scale the shape, obtain the center coordinates, and
 * get the name of the shape.
 *
 * Shapes can be compared based on their areas using the spaceship operator (<=>).
 * The spaceship operator performs a three-way comparison, allowing shapes to be
 * easily sorted or compared in a meaningful way based on their areas.
 */
class Shape {
public:
    /**
     * @brief Virtual destructor for proper polymorphic destruction.
     */
    virtual ~Shape() = default;

    /**
     * @brief Pure virtual function to calculate the area of the shape.
     * @return The area of the shape.
     */
    virtual double getArea() const = 0;

    /**
     * @brief Pure virtual function to scale the shape by a specified factor.
     *
     * The scale method performs isotropic scaling of the shape relative to its center,
     * using the specified scaling factor.
     *
     * @param factor The scaling factor.
     */
    virtual void scale(double factor) = 0;

    /**
     * @brief Pure virtual function to retrieve the center coordinates of the shape.
     * @return The center coordinates of the shape.
     */
    virtual Point getCenter() const = 0;

    /**
     * @brief Pure virtual function to get the name of the shape.
     * @return The name of the shape as a C-style string.
     */
    virtual const char* getName() const = 0;

    /**
     * @brief Spaceship operator to compare shapes based on their areas.
     *
     * Compares two shapes based on their areas, returning a three-way comparison result.
     *
     * @param other The shape to compare to.
     * @return A three-way comparison result.
     */
    std::partial_ordering operator<=>(const Shape& other) const;
};

}  // namespace setm
