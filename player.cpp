#include "player.h"

Player::Player(const std::string name_, const WellnessLevels wellness_levels_,
               const Appearance appearance_, const Major major_,
               const bool has_physiwell_)
    : name(name_), wellness_levels(wellness_levels_), appearance(appearance_),
      major(major_), has_physiwell(has_physiwell_) {}