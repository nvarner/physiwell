#include "util.h"

bool is_numeric(const std::string &str) {
  for (size_t i = 0; i < str.size(); i++) {
    if (!std::isdigit(str[i])) {
      return false;
    }
  }
  return true;
}