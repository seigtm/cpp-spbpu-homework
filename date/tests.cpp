#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>

#include <gtest/gtest.h>

#include "date.hpp"

namespace setm {

class DateClassTest : public ::testing::TestWithParam<std::tuple<Date, Date, int>> {
protected:
    Date date1{ std::get<0>(GetParam()) };
    Date date2{ std::get<1>(GetParam()) };
    int expectedDifference{ std::get<2>(GetParam()) };
};

// Test the difference in days between two dates.
TEST_P(DateClassTest, Difference) {
    ASSERT_EQ(Date::Difference(date1, date2), expectedDifference);
}

INSTANTIATE_TEST_SUITE_P(Dates, DateClassTest,
                         ::testing::Values(
                             // Test case 1: Difference between two equal dates should be 0.
                             std::make_tuple(Date{ 2003, 5, 17 }, Date{ 2003, 5, 17 }, 0),
                             // Test case 2: Difference between two dates in the same month.
                             std::make_tuple(Date{ 2003, 5, 17 }, Date{ 2003, 5, 20 }, 3),
                             // Test case 3: Difference between two dates in different years.
                             std::make_tuple(Date{ 2003, 5, 17 }, Date{ 2004, 2, 29 }, 288),
                             // Test case 4: Difference between two dates spanning a leap year.
                             std::make_tuple(Date{ 2004, 2, 29 }, Date{ 2005, 2, 28 }, 365),
                             // Test case 5: Difference between two dates spanning multiple years.
                             std::make_tuple(Date{ 2001, 1, 1 }, Date{ 2005, 12, 31 }, 1825),
                             // Test case 6: Difference between two dates with negative years.
                             std::make_tuple(Date{ -100, 1, 1 }, Date{ -101, 1, 2 }, 364),
                             // Test case 7: Difference between dates with positive and negative years.
                             std::make_tuple(Date{ 0, 1, 1 }, Date{ -1, 1, 1 }, 365)));

// Test the DaysInMonth function for both leap and non-leap years.
TEST(DateClass, DaysInMonth) {
    // Test case 1: Days in February of a non-leap year (2001).
    EXPECT_EQ(Date::DaysInMonth(2001, 2), 28);
    // Test case 2: Days in February of a leap year (2000).
    EXPECT_EQ(Date::DaysInMonth(2000, 2), 29);
    // Test case 3: Days in January of a non-leap year (2001).
    EXPECT_EQ(Date::DaysInMonth(2001, 1), 31);
}

// Test the IsLeapYear function for both leap and non-leap years.
TEST(DateClass, IsLeapYear) {
    // Test case 1: Non-leap year (2001).
    EXPECT_FALSE(Date::IsLeapYear(2001));
    // Test case 2: Leap year (2000).
    EXPECT_TRUE(Date::IsLeapYear(2000));
}

// Test the DayOfYear function for various dates.
TEST(DateClass, DayOfYear) {
    // Test case 1: Day of the year for January 1st.
    EXPECT_EQ(Date::DayOfYear(Date{ 2001, 1, 1 }), 1);
    // Test case 2: Day of the year for February 1st.
    EXPECT_EQ(Date::DayOfYear(Date{ 2001, 2, 1 }), 32);
    // Test case 3: Day of the year for December 31st.
    EXPECT_EQ(Date::DayOfYear(Date{ 2000, 12, 31 }), 366);

    // Add more test cases for other dates...
}

TEST(DateClass, ConstructValidObject) {
    Date date{ 2002, 5, 14 };

    for(int year{ -2000 }; year < 3000; ++year) {
        for(int month{ 1 }; month < 12; ++month) {
            for(int day{ 1 }; day < Date::DaysInMonth(year, month); ++day) {
                EXPECT_NO_THROW(date = Date(year, month, day));

                EXPECT_EQ(date.Year(), year);
                EXPECT_EQ(date.Month(), month);
                EXPECT_EQ(date.Day(), day);
            }
        }
    }
}

TEST(DateClass, ConstructInvalidObject) {
    EXPECT_THROW(Date(0, 0, 0), std::invalid_argument);       // 0 is not a valid month or day.
    EXPECT_THROW(Date(2001, 13, 20), std::invalid_argument);  // 13 is not a valid month.
    EXPECT_THROW(Date(2001, 2, 29), std::invalid_argument);   // 2001 is not a leap year.
    EXPECT_THROW(Date(2023, 12, 32), std::invalid_argument);  // 32 is not a valid day in December.
}

TEST(DateClass, Compare) {
    const Date eq1{ 2004, 5, 4 };  // Equal dates.
    const Date eq2{ 2004, 5, 4 };  // Equal dates.
    const Date gt{ 2004, 5, 5 };   // Greater date.
    const Date le{ 2004, 5, 3 };   // Lesser date.

    EXPECT_EQ(eq1, eq2);
    EXPECT_LE(eq1, eq2);
    EXPECT_GE(eq2, eq1);

    EXPECT_NE(eq1, gt);
    EXPECT_NE(eq2, le);

    EXPECT_LT(eq1, gt);
    EXPECT_LE(eq1, gt);

    EXPECT_GT(eq2, le);
    EXPECT_GE(eq2, le);
}

TEST(DateClass, AddDays) {
    Date date(2002, 5, 14);
    date.AddDays(3);
    EXPECT_EQ(date, Date(2002, 5, 17));
    EXPECT_EQ(date.Day(), 17);

    date.AddDays(365);
    EXPECT_EQ(date, Date(2003, 5, 17));

    // Test AddDays with leap year.
    date.AddDays(288);
    EXPECT_EQ(date, Date(2004, 2, 29));

    // Test AddDays with zero days (should not change the date).
    date.AddDays(0);
    EXPECT_EQ(date, Date(2004, 2, 29));

    // Test adding a large number of days.
    date.AddDays(10'000'000);
    EXPECT_EQ(date, Date(29383, 3, 26));
}

TEST(DateClass, IO) {
    std::stringstream ss;

    ss << Date{ 2002, 5, 14 };
    EXPECT_EQ(ss.str(), "2002/5/14");

    ss.str("");
    ss << Date{ 150, 3, 25 };
    EXPECT_EQ(ss.str(), "150/3/25");
}

}  // namespace setm
