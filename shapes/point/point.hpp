#pragma once

namespace setm {

/**
 * @brief Represents a point in a two-dimensional space with coordinates (x, y).
 *
 * The Point struct defines a simple data structure for storing coordinates of a point
 * in a Cartesian plane. It has members x and y representing the horizontal and vertical
 * coordinates, respectively.
 */
struct Point {
    double x{};  // The horizontal coordinate (x) of the point.
    double y{};  // The vertical coordinate (y) of the point.
};

}  // namespace setm
