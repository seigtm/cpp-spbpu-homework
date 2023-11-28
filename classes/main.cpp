// Develop a class for storing dates. Implement methods to retrieve date components
// (day, month, year), compare two dates, calculate the difference in days between two dates,
// and modify the date by a specified number of days.

#include <chrono>
#include <iostream>

#include "date.hpp"

int main() {
    // 1. Read date from stdin and print to stdout.
    {
        setm::Date dateFromStdin;
        std::cout << "[1]: Enter a date (YYYY/MM/DD): ";
        std::cin >> dateFromStdin;
        std::cout << '\t' << dateFromStdin << '\n';
    }

    // 2. Date constructed from (unsigned) ints.
    {
        constexpr setm::Date date{ 2002, 5, 14 };
        std::cout << "[2]: " << date << '\n';
    }

    // 3. Date constructed from (std::chrono::*).
    {
        constexpr setm::Date date{ std::chrono::year(2002), std::chrono::month(5), std::chrono::day(14) };
        std::cout << "[3]: " << date << '\n';
    }

    // 4. Date getters and setters.
    {
        setm::Date date;
        date.setYear(2002);
        date.setMonth(5);
        date.setDay(14);
        std::cout << "[4 setters]: " << date << '\n'
                  << "[4 getters]: " << date.getYear() << ' ' << date.getMonth() << ' ' << date.getDay() << '\n';
    }

    // 5. Test arithmetic operators.
    {
        constexpr setm::Date date{ 2002, 5, 4 };
        constexpr auto newDate{ date + std::chrono::days(10) };
        std::cout << "[5]: " << date << " + 10 days = " << newDate << '\n'
                  << "\tdate + new date = " << date + newDate << '\n';
    }

    // 6. Test comparison operators.
    {
        constexpr setm::Date eq1{ 2004, 5, 4 };  // Equal dates.
        constexpr setm::Date eq2{ 2004, 5, 4 };  // Equal dates.
        constexpr setm::Date gt{ 2004, 5, 5 };   // Greater date.
        constexpr setm::Date le{ 2004, 5, 3 };   // Lesser date.
        std::cout << std::boolalpha << "[6]: "
                  << (eq1 == eq2) << ' '
                  << (eq1 != gt) << ' '
                  << (eq1 < gt) << ' '
                  << (eq1 <= gt) << ' '
                  << (eq2 >= le) << '\n';
    }

    // 7. Test isValid().
    {
        setm::Date date{ 2002, 5, 14 };
        std::cout << "[7 valid]: " << date.isValid() << "\n\t" << date << '\n';
        date.setDay(32);
        date.setMonth(13);
        std::cout << "[7 invalid]: " << date.isValid() << "\n\t" << date << '\n';
    }

    // 8. Test overloaded operators.
    {
        constexpr setm::Date date{ 2005, 3, 13 };
        constexpr setm::Date newDate{ date + std::chrono::days(1) };
        setm::Date newDate2{ std::chrono::months(2) + newDate };
        std::cout << "[8]: "
                  << date
                  << " + 1 day = " << newDate
                  << " + 2 months = " << newDate2;
        newDate2 -= std::chrono::years(3);
        std::cout << " - 3 years = " << newDate2 << '\n';
    }

    // 9. Test static Difference function.
    {
        setm::Date date{ 2005, 5, 14 };
        std::cout << "[9]: "
                  << "Difference between " << date << " and " << date - std::chrono::days(5) << " is "
                  << setm::Date::Difference<std::chrono::days>(date, date - std::chrono::days(5)).count() << " days"
                  << "\n\tDifference between " << date << " and " << date - std::chrono::months(2) << " is "
                  << setm::Date::Difference<std::chrono::months>(date, date - std::chrono::months(2)).count() << " months"
                  << "\n\tDifference between " << date << " and " << date - std::chrono::years(100) << " is "
                  << setm::Date::Difference<std::chrono::years>(date, date - std::chrono::years(100)).count() << " years\n";
    }
}
