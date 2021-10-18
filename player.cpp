#include "player.h"

Player::Player(const std::string name_, const Appearance appearance_,
               const Major major_, const bool has_physiwell_)
    : name(name_), wellness_levels(WellnessLevels()), appearance(appearance_),
      major(major_), has_physiwell(has_physiwell_) {}

const std::string &Player::get_name() const { return this->name; }

const WellnessLevels &Player::get_wellness_levels() const {
  return this->wellness_levels;
}

const Appearance &Player::get_appearance() const { return this->appearance; }

const Major &Player::get_major() const { return this->major; }

bool Player::get_has_physiwell() const { return this->has_physiwell; }
