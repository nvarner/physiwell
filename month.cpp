#include "month.h"

Month::Month(const unsigned int num_days_in,
             const unsigned int next_month_index_in, const std::string name_in)
    : num_days(num_days_in), next_month_index(next_month_index_in),
      name(name_in) {}

unsigned int Month::get_num_days() const { return num_days; }

Month Month::get_next() const { return Month::MONTHS[next_month_index]; }

const std::string &Month::get_name() const { return name; }

const Month Month::JANUARY(31, 1, "January");
const Month Month::FEBRUARY(28, 2, "February");
const Month Month::MARCH(31, 3, "March");
const Month Month::APRIL(30, 4, "April");
const Month Month::MAY(31, 5, "May");
const Month Month::JUNE(30, 6, "June");
const Month Month::JULY(31, 7, "July");
const Month Month::AUGUST(31, 8, "August");
const Month Month::SEPTEMBER(30, 9, "September");
const Month Month::OCTOBER(31, 10, "October");
const Month Month::NOVEMBER(30, 11, "November");
const Month Month::DECEMBER(31, 0, "December");

const std::vector<Month> Month::MONTHS = {
    Month::JANUARY,   Month::FEBRUARY, Month::MARCH,    Month::APRIL,
    Month::MAY,       Month::JUNE,     Month::JULY,     Month::AUGUST,
    Month::SEPTEMBER, Month::OCTOBER,  Month::NOVEMBER, Month::DECEMBER};