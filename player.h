#ifndef PLAYER_H
#define PLAYER_H

#include "appearance/appearance.h"
#include "major.h"
#include "wellness_levels.h"
#include <string>

class Player {
public:
  Player(const std::string name, const Appearance appearance, const Major major,
         const bool has_physiwell);

  const std::string &get_name() const;
  WellnessLevels &get_wellness_levels();
  const WellnessLevels &get_wellness_levels() const;
  const Appearance &get_appearance() const;
  const Major &get_major() const;
  bool has_physiwell() const;

  std::string describe() const;
  std::string read_watch() const;

private:
  const std::string name;
  WellnessLevels wellness_levels;
  const Appearance appearance;
  const Major major;
  const bool player_has_physiwell;
};

#endif
