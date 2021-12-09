#include "game.h"

Game::Game(Player &player_in, Manifest &manifest_in,
           const Interface &interface_in, const unsigned int num_weeks_in)
    : player(player_in), manifest(manifest_in), interface(interface_in),
      today(Day(Month::SEPTEMBER, 20)), num_weeks(num_weeks_in) {}

void Game::play_day() {
  interface.print("Today is " + today.get_name() + "\n\n");

  const Scenario &scenario = manifest.random_scenario();
  scenario.play(player, interface);

  interface.print("\n");
  interface.print("Your watch says: " + player.read_watch() + "\n");
  player.get_wellness_levels().end_day();
  today.advance_to_tomorrow();

  interface.print("--------------\n\n");
  interface.prompt("Press enter to continue...");
}

void Game::play_week() {
  for (unsigned int i = 0; i < DAYS_PER_WEEK; i++) {
    play_day();
  }

  interface.print("End of the week\n");
  interface.print(player.describe(num_days(), false));
  interface.print("--------------\n\n");
  interface.prompt("Press enter to continue...");
}

void Game::play() {
  for (unsigned int i = 0; i < num_weeks; i++) {
    play_week();
  }
  interface.print(player.describe(num_days(), false));
}

unsigned int Game::num_days() const { return DAYS_PER_WEEK * num_weeks; }
