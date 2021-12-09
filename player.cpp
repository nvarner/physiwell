#include "player.h"
#include <string>

Player::Player(const std::string name_, const Appearance appearance_,
               const Major major_, const bool has_physiwell_)
    : name(name_), wellness_levels(WellnessLevels()), appearance(appearance_),
      major(major_), player_has_physiwell(has_physiwell_) {}

const std::string &Player::get_name() const { return this->name; }

WellnessLevels &Player::get_wellness_levels() { return this->wellness_levels; }

const WellnessLevels &Player::get_wellness_levels() const {
  return this->wellness_levels;
}

const Appearance &Player::get_appearance() const { return this->appearance; }

const Major &Player::get_major() const { return this->major; }

bool Player::has_physiwell() const { return this->player_has_physiwell; }

std::string Player::describe(const int total_num_days,
                             const bool include_steps) const {
  return get_wellness_levels().describe(total_num_days, include_steps);
}

std::string Player::read_watch() const {
  if (has_physiwell()) {
    return "The time is 9:00pm. You have taken " +
           std::to_string(get_wellness_levels().steps) + " steps today.";
  } else {
    return "The time is 9:00pm.";
  }
}
