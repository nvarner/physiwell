#include "day.h"

#include <string>

Day::Day(const Month month_in, const unsigned int day_in)
    : month(month_in), day(day_in) {}

void Day::advance_to_tomorrow() {
  if (day == month.get_num_days()) {
      day = 0;
      month = month.get_next();
  } else {
      day++;
  }
}

std::string Day::get_name() const {
    return month.get_name() + " " + std::to_string(day);
}
