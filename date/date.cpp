#include "date.hpp"

#include <array>      // std::array.
#include <cstddef>    // std::size_t.
#include <ostream>    // std::ostream.
#include <stdexcept>  // std::invalid_argument.

namespace setm {

Date::Date(int year, unsigned month, unsigned day)
    : year_{ year }, month_{ month }, day_{ day } {
    if(month_ < 1 || month_ > 12)
        throw std::invalid_argument("Invalid month.");
    if(day_ < 1 || day_ > DaysInMonth(year_, month_))
        throw std::invalid_argument("Invalid day.");
}

void Date::AddDays(unsigned numDays) noexcept {
    while(numDays > 0) {
        const unsigned daysInMonth{ DaysInMonth(year_, month_) };
        const unsigned daysRemaining{ daysInMonth - day_ + 1 };
        if(numDays >= daysRemaining) {
            // Move to the next month
            numDays -= daysRemaining;
            day_ = 1;

            if(++month_ > 12) {
                month_ = 1;
                ++year_;
            }
        } else {
            // Stay in the current month.
            day_ += numDays;
            numDays = 0;
        }
    }
}

[[nodiscard]] int Date::Year() const noexcept {
    return year_;
}

[[nodiscard]] unsigned Date::Month() const noexcept {
    return month_;
}

[[nodiscard]] unsigned Date::Day() const noexcept {
    return day_;
}

std::size_t Date::CountLeapYears(const Date& date) {
    std::size_t years{ static_cast<std::size_t>(date.Year()) };
    if(date.Month() <= 2)
        years--;

    // An year is a leap year if it is:
    // 1. a multiple of 4,
    // 2. multiple of 400
    // 3. and not a multiple of 100.
    return years / 4 - years / 100 + years / 400;
}

std::size_t Date::Difference(const Date& first, const Date& second) noexcept {
    // Calculate total days from year 0 to the given date, including leap years.
    auto TotalDaysUpToYear{ [](const Date& date) {
        // Account for leap years in the total day count.
        return date.Year() * 365 + CountLeapYears(date) + DayOfYear(date);
    } };

    const auto daysInFirstDate{ TotalDaysUpToYear(first) };
    const auto daysInSecondDate{ TotalDaysUpToYear(second) };

    // Calculate the difference in days between the two dates.
    return std::max(daysInFirstDate, daysInSecondDate) - std::min(daysInFirstDate, daysInSecondDate);
}

unsigned Date::DaysInMonth(int year, unsigned month) {
    static const std::array<unsigned, 12> DAYS_IN_MONTH_ = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // It it's February, check if it's a leap year.
    if(month == 2)
        return IsLeapYear(year) ? 29 : 28;

    return DAYS_IN_MONTH_[month - 1];
}

bool Date::IsLeapYear(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

unsigned Date::DayOfYear(const Date& date) {
    unsigned dayOfYear{ date.day_ };

    for(unsigned m{ 1 }; m < date.month_; ++m)
        dayOfYear += DaysInMonth(date.year_, m);

    return dayOfYear;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    return os << date.Year() << '/' << date.Month() << '/' << date.Day();
}

}  // namespace setm
