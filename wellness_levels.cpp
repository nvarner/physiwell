#include "wellness_levels.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

void WellnessLevels::end_day() {
  strength += steps / STEPS_PER_STRENGTH;
  steps = 0;
}

int double_high(const int low, const int high) { return high + (high - low); }
int double_low(const int low, const int high) { return low + (low - high); }

std::string choose(const std::vector<std::string> &choices) {
  return choices[rand() % choices.size()];
}

std::optional<std::string>
describe_trait(const int value, const int low, const int high,
               const std::vector<std::string> lows,
               const std::vector<std::string> mid_lows,
               const std::vector<std::string> mid_highs,
               const std::vector<std::string> highs) {
  if (value >= double_high(low, high)) {
    return choose(highs);
  } else if (value >= high) {
    return choose(mid_highs);
  } else if (value <= double_low(low, high)) {
    return choose(lows);
  } else if (value <= low) {
    return choose(mid_lows);
  }
  return {};
}

std::string WellnessLevels::describe() const {
  std::vector<std::string> descriptions;

  std::cout << "steps: " << steps << ", stress: " << stress
            << ", strength: " << strength << "\n";

  auto strength_description =
      describe_trait(stress, LOW_STRENGTH_CHANGE, HIGH_STRENGTH_CHANGE,
                     {"You regularly throw boulders."},
                     {"You can move things around with ease."},
                     {"You have trouble moving things around."},
                     {"You could be crushed by a feather."});
  if (strength_description) {
    descriptions.push_back(*strength_description);
  }

  auto stress_description = describe_trait(
      stress, -HIGH_CHANGE, HIGH_CHANGE, {"You're super relaxed."},
      {"You are calm."},
      {"You're stressed out.", "You wish you had less on your plate."},
      {"You feel extremely stressed.", "You're overwhelmed."});
  if (stress_description) {
    descriptions.push_back(*stress_description);
  }

  auto relations_description = describe_trait(
      relations, -HIGH_CHANGE, HIGH_CHANGE, {"You're happy with your friends."},
      {"You like having friends."}, {"You feel alone."},
      {"You feel isolated."});
  if (stress_description) {
    descriptions.push_back(*stress_description);
  }

  auto school_description = describe_trait(
      school, -HIGH_CHANGE, HIGH_CHANGE, {"You love your classes."},
      {"You feel confident in your classes."},
      {"You're confused about what you're learning."},
      {"You will probably get some failing grades."});
  if (school_description) {
    descriptions.push_back(*school_description);
  }

  auto confidence_description = describe_trait(
      confidence, -HIGH_CHANGE, HIGH_CHANGE, {"You're confident in yourself."},
      {"You have pretty good self esteem."}, {"You wish you were different."},
      {"You hate yourself."});
  if (confidence_description) {
    descriptions.push_back(*confidence_description);
  }

  std::random_shuffle(descriptions.begin(), descriptions.end());
  std::string description;
  for (std::string desc : descriptions) {
    description += desc + "\n";
  }

  return description;
}
