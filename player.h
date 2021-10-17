#include "appearance/appearance.h"
#include "major.h"
#include "wellness_levels.h"
#include <string>

class Player {
public:
  Player(const std::string name, const WellnessLevels wellness_levels,
         const Appearance appearance, const Major major,
         const bool has_physiwell);

private:
  std::string name;
  WellnessLevels wellness_levels;
  Appearance appearance;
  Major major;
  const bool has_physiwell;
};
