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

  // // Debug
  // std::cout << "steps: " << steps << ", stress: " << stress
  //           << ", strength: " << strength << ", relations: " << relations
  //           << ", school: " << school << ", confidence: " << confidence << "\n";

  auto strength_description =
      describe_trait(stress, LOW_STRENGTH_CHANGE, HIGH_STRENGTH_CHANGE,
                     {"You feel physically strong."},
                     {"You notice that you have more endurance than before."},
                     {"Walking across campus feels hard."},
                     {"Walking short distances is hard."});
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
    descriptions.push_back(*relations_description);
  }

  auto school_description = describe_trait(
      school, -HIGH_CHANGE, HIGH_CHANGE,
      {"You will probably get some failing grades."},
      {"You're confused about what you're learning."},
      {"You feel confident in your classes."}, {"You love your classes."});
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

std::string WellnessLevels::detailed_describe() const {
  std::string description;

  if (stress > 5) {
    description += "You wish you weren't so stressed.\n";
  }

  if (relations < -5) {
    description += "You feel isolated. If only you'd spent more time with friends.\n";
  } else if (relations < 5) {
    description += "You feel isolated. You have some friends, but don't know them that well.\n";
  }

  if (school < -5) {
    description += "You're on the path to failing your classes. Studying would have helped a lot.\n";
  } else if (school > 5) {
    description += "Your grades are looking incredible.\n";
  }

  if (confidence < -5) {
    description += "Your self-esteem is low. You're not confident in yourself.\n";
  } else if (confidence > 5) {
    description += "Your self-esteem is very strong. You're full of confidence.\n";
  }

  return description;
}
