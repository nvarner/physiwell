#ifndef DAY_H
#define DAY_H

#include "month.h"

class Day {
public:
    Day(const Month month_in, const unsigned int day_in);

    void advance_to_tomorrow();
    std::string get_name() const;

private:
    Month month;
    unsigned int day;
};

#endif