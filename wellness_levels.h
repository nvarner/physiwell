#include <cstdint>

class WellnessLevels {
public:
  WellnessLevels() : physical(0), mental(0), social(0), stress(0), grades(0) {}

  uint32_t physical;
  uint32_t mental;
  uint32_t social;
  uint32_t stress;
  uint32_t grades;

private:
};
