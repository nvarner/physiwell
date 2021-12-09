#ifndef MONTH_H
#define MONTH_H

#include <string>
#include <vector>

class Month {
public:
  Month(const unsigned int num_days_in, const unsigned int next_month_index_in,
        const std::string name_in);

  unsigned int get_num_days() const;
  Month get_next() const;
  const std::string &get_name() const;

  static const Month JANUARY;
  static const Month FEBRUARY;
  static const Month MARCH;
  static const Month APRIL;
  static const Month MAY;
  static const Month JUNE;
  static const Month JULY;
  static const Month AUGUST;
  static const Month SEPTEMBER;
  static const Month OCTOBER;
  static const Month NOVEMBER;
  static const Month DECEMBER;
  static const std::vector<Month> MONTHS;

private:
  unsigned int num_days;
  unsigned int next_month_index;
  std::string name;
};

#endif