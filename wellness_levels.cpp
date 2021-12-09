#include "wellness_levels.h"

#include <algorithm>
#include <optional>
#include <vector>

void WellnessLevels::end_day() {
  strength += steps / STEPS_PER_STRENGTH;
  steps = 0;
}

int average(const int low, const int high) { return (low + high) / 2; }

int low_quartile(const int low, const int high) {
  return average(low, average(low, high));
}

int high_quartile(const int low, const int high) {
  return average(high, average(low, high));
}

std::string choose(const std::vector<std::string> &choices) {
  return choices[rand() % choices.size()];
}

std::optional<std::string>
describe_trait(const int value, const int low, const int high,
               const std::vector<std::string> lows,
               const std::vector<std::string> mid_lows,
               const std::vector<std::string> mid_highs,
               const std::vector<std::string> highs) {
  if (value >= high) {
    return choose(highs);
  } else if (value >= high_quartile(low, high)) {
    return choose(mid_highs);
  } else if (value <= low) {
    return choose(lows);
  } else if (value <= low_quartile(low, high)) {
    return choose(mid_lows);
  }
  return {};
}

std::string WellnessLevels::describe(const int total_num_days,
                                     const bool include_steps) const {
  std::vector<std::string> descriptions;

  if (include_steps) {
    auto steps_description = describe_trait(
        steps, LOW_STEP_CHANGE, HIGH_STEP_CHANGE, {"You feel limp."},
        {"You feel restless."}, {"You feel energized."}, {"You feel tired."});
    if (steps_description) {
      descriptions.push_back(*steps_description);
    }
  }

  auto stress_description = describe_trait(
      stress, -HIGH_CHANGE * total_num_days, HIGH_CHANGE * total_num_days,
      {"You're super relaxed."}, {"You are calm."},
      {"You're stressed out.", "You wish you had less on your plate."},
      {"You feel extremely stressed.", "You're overwhelmed."});
  if (stress_description) {
    descriptions.push_back(*stress_description);
  }

  auto relations_description = describe_trait(
      relations, -HIGH_CHANGE * total_num_days, HIGH_CHANGE * total_num_days,
      {"You're happy with your friends."}, {"You like having friends."},
      {"You feel alone."}, {"You feel isolated."});
  if (stress_description) {
    descriptions.push_back(*stress_description);
  }

  auto school_description = describe_trait(
      school, -HIGH_CHANGE * total_num_days, HIGH_CHANGE * total_num_days,
      {"You love your classes."}, {"You feel confident in your classes."},
      {"You're confused about what you're learning."},
      {"You will probably get some failing grades."});
  if (school_description) {
    descriptions.push_back(*school_description);
  }

  auto confidence_description = describe_trait(
      confidence, -HIGH_CHANGE * total_num_days, HIGH_CHANGE * total_num_days,
      {"You're confident in yourself."}, {"You have pretty good self esteem."},
      {"You wish you were different."}, {"You hate yourself."});
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
