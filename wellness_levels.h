#ifndef WELLNESS_LEVELS_H
#define WELLNESS_LEVELS_H

#include <cstdint>
#include <string>

class WellnessLevels {
public:
  WellnessLevels() : steps(0), strength(0), stress(0), relations(0), school(0), confidence(0) {}

  /**
  * End a day by updating strength based on steps and resetting steps.
  */
  void end_day();

  /**
  * Get a qualitative description of wellness.
  * - `total_num_days`: The total number of days the simulation will run for. Used to determine what high and low values
  *   are.
  */
  std::string describe(const int total_num_days) const;

  static const int HIGH_STEP_CHANGE = 20000;
  static const int LOW_STEP_CHANGE = 0;

  /**
  * Total number of steps taken in a day.
  * 0 is not a lot; 7,000-10,000 is a reasonable average; 20,000 is a lot
  */
  int steps;

  static const int STEPS_PER_STRENGTH = 1000;
  static const int HIGH_STRENGTH_CHANGE = HIGH_STEP_CHANGE / STEPS_PER_STRENGTH;
  static const int LOW_STRENGTH_CHANGE = LOW_STEP_CHANGE / STEPS_PER_STRENGTH;

  /**
  * Amount of "strength", ie general physical ability. Sort of an integral of steps.
  * Should increase by 1 for each 1,000 steps taken in a day.
  * Daily increase of 0 is not a lot; 20 is a lot
  */
  int strength;

  static const int HIGH_CHANGE = 10;

  /**
  * How stressed someone is.
  * Daily change by +-10 is a lot
  */
  int stress;
  /**
  * How strong your relationships are.
  * Daily change by +-10 is a lot
  */
  int relations;
  /**
  * How well you're doing in school.
  * Daily change by +-10 is a lot
  */
  int school;
  /**
  * How self-confident you are.
  * Daily change by +-10 is a lot
  */
  int confidence;
};

#endif