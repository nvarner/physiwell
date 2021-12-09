#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <getopt.h>
#include <iostream>
#include <istream>
#include <limits>
#include <queue>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "game.h"
#include "interface.h"
#include "player.h"
#include "scenario.h"
#include "manifest.h"

Gender prompt_pronouns(const Interface &interface) {
  std::string nom = interface.prompt(
      "What is your nominative pronoun (analogous to he or she)?");
  std::string acc = interface.prompt("Accusative (like him or her)?");
  std::string reflexive =
      interface.prompt("Reflexive (like himself or herself)?");
  std::string ind_gen = interface.prompt("Independent genitive (like hers)?");
  std::string dep_gen = interface.prompt("Dependent genitive (like her)?");
  return Gender(nom, acc, reflexive, ind_gen, dep_gen);
}

Gender create_gender(const Interface &interface) {
  return MENU(interface, Gender, "What are your pronouns?",
          MENU_OPTION("he/him", Gender::MALE),
          MENU_OPTION("she/her", Gender::FEMALE),
          MENU_OPTION("they/them", Gender::NB),
          MENU_OPTION("Something else", prompt_pronouns(interface))
      );
}

Hat create_hat(const Interface &interface) {
  HatHeight height = MENU(interface, HatHeight, "What is the height of your hat?",
    MENU_OPTION("tall", HatHeight::Tall),
    MENU_OPTION("short", HatHeight::Short)
  );

  std::string color = interface.prompt("What color is your hat?");

  return Hat(height, color);
}

Appearance create_appearance(const Interface &interface) {
  Gender gender = create_gender(interface);
  Hat hat = create_hat(interface);
  return Appearance(gender, hat);
}

Major create_major(const Interface &interface) {
  return MENU(interface, Major, "What is your major?",
    MENU_OPTION("Computer Science", Major::CS),
    MENU_OPTION("Political Science", Major::PoliSci),
    MENU_OPTION("Undecided", Major::Undecided)
  );
}

bool ask_has_physiwell(const Interface &interface) {
  interface.print(
      "Congratulations! You have been selected as the winner of one PhysiWell "
      "fitness tracker watch, or another product of lesser value!\n");
  return MENU(interface, bool, "What would you like to choose?",
    MENU_OPTION("PhysiWell fitness tracker (allows you to see fitness data and current time)", true),
    MENU_OPTION("Cheap analog watch (allows you to see the current time)", false)
  );
}

Player create_player(const Interface &interface) {
  std::string name = interface.prompt("What is your name?");
  Appearance appearance = create_appearance(interface);
  Major major = create_major(interface);
  bool has_physiwell = ask_has_physiwell(interface);
  return Player(name, appearance, major, has_physiwell);
}

Player create_nathan() {
  return Player("Nathan", Appearance(Gender::MALE, Hat(HatHeight::Short, "blue")), Major::CS, false);
}

int main(int argc, char **argv) {
  std::srand((unsigned int)std::time(0));

  int option_index = 0, option = 0;
  struct option longOpts[] = {
      {"sleep", required_argument, nullptr,
       's'}, // set sleep times between text prints. Default 1 second.
      {"median", no_argument, nullptr, 'm'},
      {"help", no_argument, nullptr, 'h'},
      {nullptr, 0, nullptr, '\0'}};
  int slp = 1;
  while ((option = getopt_long(argc, argv, "vs:mh", longOpts, &option_index)) !=
         -1) {
    switch (option) {
    case 's':
      slp = std::atoi(optarg);
      break;
    case 'm':
      break;
    case 'h':
      std::cout << "Help Message\n";
      exit(0);
    }
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(slp));

  Interface interface(std::cin, std::cout);
  // Player player = create_player(interface);
  // For debugging
  Player player = create_nathan();

  Manifest manifest("data/manifest.txt");

  Game game(player, manifest, interface, 3);
  game.play();

  return 0;
}