#include <algorithm>  // std::sort.
#include <cstddef>    // std::size_t.
#include <numbers>    // std::numbers::pi_v.
#include <vector>     // std::vector.

#include "point/point.hpp"          // setm::Point.
#include "shape/shape.hpp"          // setm::Shape.
#include "rectangle/rectangle.hpp"  // setm::Rectangle.
#include "circle/circle.hpp"        // setm::Circle.

#include <gtest/gtest.h>  // Google Test.

TEST(RectangleTest, ConstructorAndMethods) {
    // Test valid construction.
    setm::Rectangle rectangle({ 0, 0 }, { 2, 3 });

    // Test invalid construction.
    EXPECT_THROW(setm::Rectangle({ 0, 0 }, { 2, 0 }), std::invalid_argument);

    // Test area = a * b = 2 * 3 = 6.
    EXPECT_DOUBLE_EQ(rectangle.getArea(), 6.0);
    // Test center = { 1.0, 1.5 }.
    EXPECT_DOUBLE_EQ(rectangle.getCenter().x, 1.0);
    EXPECT_DOUBLE_EQ(rectangle.getCenter().y, 1.5);

    // Test scale with factor = 2.0.
    rectangle.scale(2.0);
    // Test area after scaling = a * b = 4 * 6 = 24.
    EXPECT_DOUBLE_EQ(rectangle.getArea(), 24.0);

    // After scaling the center should still be = { 1.0, 1.5 }.
    EXPECT_DOUBLE_EQ(rectangle.getCenter().x, 1.0);
    EXPECT_DOUBLE_EQ(rectangle.getCenter().y, 1.5);

    // Test getName().
    EXPECT_STREQ(rectangle.getName(), "RECTANGLE");
}

TEST(CircleTest, ConstructorAndMethods) {
    // Test valid construction.
    setm::Circle circle({ 5, 5 }, 2.0);

    // Test invalid construction.
    EXPECT_THROW(setm::Circle({ 5, 5 }, 0.0), std::invalid_argument);

    // Test area = pi * r^2 = pi * 2^2.
    EXPECT_DOUBLE_EQ(circle.getArea(), std::numbers::pi_v<double> * 2.0 * 2.0);
    // Test center = { 5.0, 5.0 }.
    EXPECT_DOUBLE_EQ(circle.getCenter().x, 5.0);
    EXPECT_DOUBLE_EQ(circle.getCenter().y, 5.0);

    // Test scale with factor = 3.0.
    circle.scale(3.0);
    // Test area after scaling = pi * r^2 = pi * 6^2.
    EXPECT_DOUBLE_EQ(circle.getArea(), std::numbers::pi_v<double> * 6.0 * 6.0);

    // After scaling the center should still be = { 5.0, 5.0 }.
    EXPECT_DOUBLE_EQ(circle.getCenter().x, 5.0);
    EXPECT_DOUBLE_EQ(circle.getCenter().y, 5.0);

    // Test getName().
    EXPECT_STREQ(circle.getName(), "CIRCLE");
}

TEST(SortingTest, CompareShapes) {
    std::vector<setm::Shape*> shapes{
        new setm::Rectangle({ 0, 0 }, { 2, 3 }),
        new setm::Rectangle({ 1, 1 }, { 4, 4 }),
        new setm::Rectangle({ -1, -1 }, { 1, 1 }),
        new setm::Circle({ 5, 5 }, 2.0),
        new setm::Circle({ 2, 2 }, 3.0)
    };

    // Vector of expected areas.
    const std::vector<double> expected_areas{
        4.0,
        6.0,
        9.0,
        std::numbers::pi_v<double> * 2.0 * 2.0,
        std::numbers::pi_v<double> * 3.0 * 3.0
    };

    // Sort shapes by area in ascending order.
    std::sort(shapes.begin(), shapes.end(),
              [](const setm::Shape* a, const setm::Shape* b) { return *a < *b; });

    // Check sorting order.
    for(std::size_t i{}; i < shapes.size(); ++i) {
        EXPECT_DOUBLE_EQ(shapes[i]->getArea(), expected_areas[i]);
    }

    // Clean up.
    for(std::size_t i{}; i < shapes.size(); ++i) {
        delete shapes[i];
    }
}
