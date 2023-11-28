#pragma once

#include <compare>
#include <chrono>
#include <sstream>
#include <string>

namespace setm {

/**
 * @brief Represents a date with year, month, and day components.
 *
 * The Date class provides functionality for working with dates, including
 * arithmetic and comparison operations.
 */
class Date {
public:
    // ========= Constructors: ========= //
    /**
     * @brief Constructor for Date with specified year, month, and day.
     *
     * Constructs a Date object with the specified year, month, and day components.
     * If no arguments are provided, the default values are used, resulting in an unspecified date.
     *
     * @param year The year of the date. Defaults to the default-constructed std::chrono::year.
     * @param month The month of the date. Defaults to the default-constructed std::chrono::month.
     * @param day The day of the date. Defaults to the default-constructed std::chrono::day.
     */
    constexpr Date(const std::chrono::year& year = {},
                   const std::chrono::month& month = {},
                   const std::chrono::day& day = {}) noexcept;


    /**
     * @brief Constructor for Date with specified year, month, and day.
     *
     * @param year The year of the date.
     * @param month The month of the date.
     * @param day The day of the date.
     */
    constexpr Date(unsigned year, unsigned month, unsigned day) noexcept;


    // ========= Member functions: ========= //
    /**
     * @brief Checks if the date is valid.
     *
     * A date is considered valid if the year, month, and day components are valid.
     *
     * @return True if the date is valid, false otherwise.
     */
    constexpr bool isValid() const noexcept;


    // ========= Getters: ========= //
    constexpr std::chrono::year getYear() const noexcept;
    constexpr std::chrono::month getMonth() const noexcept;
    constexpr std::chrono::day getDay() const noexcept;


    // ========= Setters: ========= //
    constexpr void setYear(const std::chrono::year& year) noexcept;
    constexpr void setMonth(const std::chrono::month& month) noexcept;
    constexpr void setDay(const std::chrono::day& day) noexcept;
    constexpr void setYear(unsigned year) noexcept;
    constexpr void setMonth(unsigned month) noexcept;
    constexpr void setDay(unsigned day) noexcept;


    // ========= Comparison operators: ========= //
    constexpr std::strong_ordering operator<=>(const Date& other) const noexcept = default;


    // ========= Arithmetic operators: ========= //
    constexpr Date operator+(const Date& date) const noexcept;
    constexpr Date operator-(const Date& date) const noexcept;

    constexpr Date operator+(const std::chrono::years& years) const noexcept;
    constexpr Date operator-(const std::chrono::years& years) const noexcept;
    constexpr Date operator-(const std::chrono::months& months) const noexcept;
    constexpr Date operator+(const std::chrono::months& months) const noexcept;
    constexpr Date operator+(const std::chrono::days& days) const noexcept;
    constexpr Date operator-(const std::chrono::days& days) const noexcept;

    constexpr Date& operator+=(const std::chrono::years& years) noexcept;
    constexpr Date& operator-=(const std::chrono::years& years) noexcept;
    constexpr Date& operator+=(const std::chrono::months& months) noexcept;
    constexpr Date& operator-=(const std::chrono::months& months) noexcept;
    constexpr Date& operator+=(const std::chrono::days& days) noexcept;
    constexpr Date& operator-=(const std::chrono::days& days) noexcept;


    // ========= Friend operators: ========= //
    friend constexpr Date operator+(const std::chrono::years& years, const Date& date) noexcept;
    friend constexpr Date operator+(const std::chrono::months& months, const Date& date) noexcept;
    friend constexpr Date operator+(const std::chrono::days& days, const Date& date) noexcept;
    friend constexpr Date operator-(const std::chrono::years& years, const Date& date) noexcept;
    friend constexpr Date operator-(const std::chrono::months& months, const Date& date) noexcept;
    friend constexpr Date operator-(const std::chrono::days& days, const Date& date) noexcept;


    // ========= I/O operators: ========= //
    /**
     * @brief Outputs the date to the stream.
     *
     * If the date is invalid, it outputs "Invalid date: ".
     *
     * @param os The output stream.
     * @param date The date to output.
     * @return The modified output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Date& date);

    /**
     * @brief Inputs the date from the stream.
     *
     * The expected input format is "YYYY/MM/DD".
     * If the input is not in the expected format, it sets the failbit.
     *
     * @param is The input stream.
     * @param date The date to input.
     * @return The modified input stream.
     */
    friend std::istream& operator>>(std::istream& is, Date& date);


    // ========= Static functions: ========= //
    /**
     * @brief Computes the difference between two dates.
     *
     * @tparam YMD The type of the difference (years, months, or days).
     * @param first The first date.
     * @param second The second date.
     * @return The duration between the two dates.
     */
    template<class YMD>
    static constexpr auto Difference(const Date& first, const Date& second) noexcept {
        static_assert(std::is_same_v<YMD, std::chrono::years> || std::is_same_v<YMD, std::chrono::months> || std::is_same_v<YMD, std::chrono::days>,
                      "Invalid type for Difference function");

        if constexpr(std::is_same_v<YMD, std::chrono::years>) {
            return std::chrono::duration_cast<YMD>(first.getYear() - second.getYear());
        } else if constexpr(std::is_same_v<YMD, std::chrono::months>) {
            return std::chrono::duration_cast<YMD>(first.getMonth() - second.getMonth());
        } else if constexpr(std::is_same_v<YMD, std::chrono::days>) {
            return std::chrono::duration_cast<YMD>(first.getDay() - second.getDay());
        }
    }


private:
    // ========= Fields: ========= //
    std::chrono::year year_;    // The year of the date.
    std::chrono::month month_;  // The month of the date.
    std::chrono::day day_;      // The day of the date.
};


// ========= Definitions: ========= //
// Definitions are inside header file because of:
//  -- [dcl.constexpr] §7.1.5/2
//     constexpr functions and constexpr constructors are implicitly inline.
//  -- [basic.def.odr] §3.2/4
//     An inline function shall be defined in every translation unit in which it is odr-used.

// ========= Constructors: ========= //
constexpr Date::Date(const std::chrono::year& year,
                     const std::chrono::month& month,
                     const std::chrono::day& day) noexcept
    : year_{ year }, month_{ month }, day_{ day } {}

constexpr Date::Date(unsigned year, unsigned month, unsigned day) noexcept
    : year_{ static_cast<int>(year) }, month_{ month }, day_{ day } {}


// ========= Member functions: ========= //
constexpr bool Date::isValid() const noexcept {
    return year_.ok() && month_.ok() && day_.ok();
}


// ========= Getters: ========= //
constexpr std::chrono::year Date::getYear() const noexcept {
    return year_;
}

constexpr std::chrono::month Date::getMonth() const noexcept {
    return month_;
}

constexpr std::chrono::day Date::getDay() const noexcept {
    return day_;
}


// ========= Setters: ========= //
constexpr void Date::setYear(const std::chrono::year& year) noexcept {
    year_ = year;
}

constexpr void Date::setMonth(const std::chrono::month& month) noexcept {
    month_ = month;
}

constexpr void Date::setDay(const std::chrono::day& day) noexcept {
    day_ = day;
}

constexpr void Date::setYear(unsigned year) noexcept {
    setYear(std::chrono::year(year));
}

constexpr void Date::setMonth(unsigned month) noexcept {
    setMonth(std::chrono::month(month));
}

constexpr void Date::setDay(unsigned day) noexcept {
    setDay(std::chrono::day(day));
}


// ========= Arithmetic operators: ========= //
constexpr Date Date::operator+(const Date& other) const noexcept {
    return {
        year_ + std::chrono::years(static_cast<int>(other.getYear())),
        month_ + std::chrono::months(static_cast<unsigned>(other.getMonth())),
        day_ + std::chrono::days(static_cast<unsigned>(other.getDay()))
    };
}

constexpr Date Date::operator-(const Date& other) const noexcept {
    return {
        year_ - std::chrono::years(static_cast<int>(other.getYear())),
        month_ - std::chrono::months(static_cast<unsigned>(other.getMonth())),
        day_ - std::chrono::days(static_cast<unsigned>(other.getDay()))
    };
}

constexpr Date Date::operator+(const std::chrono::days& days) const noexcept {
    return { year_, month_, day_ + days };
}

constexpr Date Date::operator-(const std::chrono::days& days) const noexcept {
    return { year_, month_, day_ - days };
}

constexpr Date Date::operator-(const std::chrono::months& months) const noexcept {
    return { year_, month_ - months, day_ };
}

constexpr Date Date::operator+(const std::chrono::months& months) const noexcept {
    return { year_, month_ + months, day_ };
}

constexpr Date Date::operator+(const std::chrono::years& years) const noexcept {
    return { year_ + years, month_, day_ };
}

constexpr Date Date::operator-(const std::chrono::years& years) const noexcept {
    return { year_ - years, month_, day_ };
}

constexpr Date& Date::operator+=(const std::chrono::years& years) noexcept {
    *this = *this + years;
    return *this;
}

constexpr Date& Date::operator-=(const std::chrono::years& years) noexcept {
    *this = *this - years;
    return *this;
}

constexpr Date& Date::operator+=(const std::chrono::months& months) noexcept {
    *this = *this + months;
    return *this;
}

constexpr Date& Date::operator-=(const std::chrono::months& months) noexcept {
    *this = *this - months;
    return *this;
}

constexpr Date& Date::operator+=(const std::chrono::days& days) noexcept {
    *this = *this + days;
    return *this;
}

constexpr Date& Date::operator-=(const std::chrono::days& days) noexcept {
    *this = *this - days;
    return *this;
}


// ========= Friend operators: ========= //
constexpr Date operator+(const std::chrono::years& years, const Date& date) noexcept {
    return date + years;
}

constexpr Date operator+(const std::chrono::months& months, const Date& date) noexcept {
    return date + months;
}

constexpr Date operator+(const std::chrono::days& days, const Date& date) noexcept {
    return date + days;
}

constexpr Date operator-(const std::chrono::years& years, const Date& date) noexcept {
    return date - years;
}

constexpr Date operator-(const std::chrono::months& months, const Date& date) noexcept {
    return date - months;
}

constexpr Date operator-(const std::chrono::days& days, const Date& date) noexcept {
    return date - days;
}


// ========= I/O operators: ========= //
std::ostream& operator<<(std::ostream& os, const Date& date) {
    if(!date.isValid())
        os << "Invalid date: ";
    return os << date.getYear() << '/' << date.getMonth() << '/' << date.getDay();
}

std::istream& operator>>(std::istream& is, Date& date) {
    std::string input;
    is >> input;

    // Assuming the input format is "YYYY/MM/DD".
    std::istringstream iss{ input };
    int year;
    int month;
    int day;
    char delimiter1;
    char delimiter2;

    if(iss >> year >> delimiter1 >> month >> delimiter2 >> day && delimiter1 == '/' && delimiter2 == '/') {
        date.setYear(std::chrono::year(year));
        date.setMonth(std::chrono::month(month));
        date.setDay(std::chrono::day(day));
    } else {
        // If the input is not in the expected format, set the failbit.
        is.setstate(std::ios::failbit);
    }

    return is;
}

}  // namespace setm
