#ifndef GAME_H
#define GAME_H

#include "manifest.h"
#include "player.h"
#include "day.h"

class Game {
public:
  Game(Player &player_in, Manifest &manifest_in,
       const Interface &interface_in, unsigned int num_weeks_in);
  
  void play();

  static const unsigned int DAYS_PER_WEEK = 2;

private:
  Player &player;
  Manifest &manifest;
  const Interface &interface;

  Day today;

  const unsigned int num_weeks;

  void play_week();
  void play_day();

  unsigned int num_days() const;
};

#endif