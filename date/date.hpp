#pragma once

#include <array>      // std::array.
#include <compare>    // std::strong_ordering.
#include <cstddef>    // std::size_t.
#include <ostream>    // std::ostream.
#include <stdexcept>  // std::invalid_argument.

namespace setm {

/**
 * @brief Represents a date with year, month, and day components.
 *
 * The Date class provides functionality for working with dates, including
 * some arithmetic (adding days) and comparison operations.
 */
class Date {
public:
    // ========= Constructors: ========= //
    /**
     * @brief Constructs a Date object with the specified year, month, and day.
     *
     * @param year The year of the date.
     * @param month The month of the date.
     * @param day The day of the date.
     * @throws std::invalid_argument if the month or day is out of valid range.
     */
    Date(int year, unsigned month, unsigned day);


    // ========= Methods: ========= //
    /**
     * @brief Modifies the date by adding a specified number of days.
     *
     * @param numDays The number of days to add to the date.
     * @note This function ensures that the date is updated correctly after adding days.
     */
    void AddDays(unsigned numDays) noexcept;


    // ========= Getters: ========= //
    [[nodiscard]] int Year() const noexcept;
    [[nodiscard]] unsigned Month() const noexcept;
    [[nodiscard]] unsigned Day() const noexcept;


    // ========= Comparison operators: ========= //
    /**
     * @brief Compares two Date objects using the spaceship operator.
     *
     * @param other The Date object to compare against.
     * @return Strong ordering result (<, ==, or >).
     */
    std::strong_ordering operator<=>(const Date& other) const noexcept = default;


    // ========= Static functions: ========= //
    /**
     * @brief Counts the number of leap years up to a given date.
     *
     * @param date The date up to which to count leap years.
     * @return The count of leap years.
     */
    static std::size_t CountLeapYears(const Date& date);

    /**
     * @brief Calculates the difference in days between two Date objects.
     *
     * @param first The first Date object.
     * @param second The second Date object.
     * @return The difference in days between the two dates.
     * @note The difference is calculated using the total number of days from year 0.
     * This means that the difference is always positive.
     */
    [[nodiscard]] static std::size_t Difference(const Date& first, const Date& second) noexcept;


    /**
     * @brief Retrieves the number of days in a specific month of a given year.
     *
     * @param year The year of the date.
     * @param month The month of the date.
     * @return The number of days in the specified month.
     */
    static unsigned DaysInMonth(int year, unsigned month);

    /**
     * @brief Checks if a given year is a leap year.
     *
     * @param year The year to check.
     * @return True if the year is a leap year, false otherwise.
     */
    static bool IsLeapYear(int year);

    /**
     * @brief Calculates the day of the year for a given date.
     *
     * @param date The Date object for which to calculate the day of the year.
     * @return The day of the year.
     */
    static unsigned DayOfYear(const Date& date);


    // ========= I/O friend operators: ========= //
    /**
     * @brief Outputs the date to the stream in the format "YYYY/MM/DD".
     *
     * @param os The output stream.
     * @param date The Date object to output.
     * @return The modified output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Date& date);


private:
    int year_;
    unsigned month_;
    unsigned day_;
};

}  // namespace setm
