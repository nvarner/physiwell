#ifndef MAJOR_H
#define MAJOR_H

#include <string>

class Major {
public:
  Major(const std::string name_in);

  const std::string &get_name() const;

  static const Major CS;
  static const Major PoliSci;
  static const Major Undecided;
private:
  std::string name;
};

#endif