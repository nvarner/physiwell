#include <iostream>
#include <limits>
#include <algorithm>
#include <cassert>
#include <getopt.h>
#include <iostream>
#include <istream>
#include <queue>
#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "interface.h"
#include "player.h"

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
  size_t choice =
      interface.menu("What are your pronouns?",
                     std::vector<std::string>{"he/him", "she/her", "they/them",
                                              "Something else"});
  switch (choice) {
  case 0:
    return Gender::MALE;
  case 1:
    return Gender::FEMALE;
  case 2:
    return Gender::NB;
  default:
    return prompt_pronouns(interface);
  }
}

Hat create_hat(const Interface &interface) {
  size_t choice = interface.menu("What is the height of your hat?",
                                 std::vector<std::string>{"tall", "short"});
  HatHeight height = choice == 0 ? HatHeight::Tall : HatHeight::Short;

  std::string color = interface.prompt("What color is your hat?");

  return Hat(height, color);
}

Appearance create_appearance(const Interface &interface) {
  Gender gender = create_gender(interface);
  Hat hat = create_hat(interface);
  return Appearance(gender, hat);
}

Major create_major(const Interface &interface) {
  size_t choice =
      interface.menu("What is your major?",
                     std::vector<std::string>{
                         "Computer Science", "Political Science", "Undecided"});
  switch (choice) {
  case 0:
    return Major::CS;
  case 1:
    return Major::PoliSci;
  default:
    return Major::Undecided;
  }
}

bool ask_has_physiwell(const Interface &interface) {
  interface.print(
      "Congratulations! You have been selected as the winner of one PhysiWell "
      "fitness tracker watch, or another product of lesser value!\n");
  size_t choice = interface.menu(
      "What would you like to choose?",
      std::vector<std::string>{
          "PhysiWell fitness tracker (allows you to see fitness data and "
          "curent time)",
          "Cheap analog watch (allows you to see the current time)"});
  return choice == 0;
}

Player create_player(const Interface &interface) {
  std::string name = interface.prompt("What is your name?");
  Appearance appearance = create_appearance(interface);
  Major major = create_major(interface);
  bool has_physiwell = ask_has_physiwell(interface);
  return Player(name, appearance, major, has_physiwell);
}

// Whenever the player needs to make a multiple choice, use this function.
// parameter is a string that is a list of all potential choices.
// E.g. "ABC" for 3 choices - A, B, or C
// Returns the character they chose.

// Can be improved? Only accept single chars, maybe.
// Bug?: just be sure to ask for input once before using this function.
char choose(std::string choices, std::string err = "Incorrect Input. Try Again."){
  std::string choice;
  while (true){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
    std::cin >> choice;
    if (choice == "QUIT") return '~'; // using this char for quits.
    if (choices.find(choice[0]) != std::string::npos) break;
    else std::cout << err << std::endl;
  }
  std::cout << "You selected: " << choice[0] << std::endl;
  return choice[0];
}

int main(int argc, char **argv) {
  int option_index = 0, option = 0;
  struct option longOpts[] = {{"sleep", required_argument, nullptr, 's'}, // set sleep times between text prints. Default 1 second.
                              {"median", no_argument, nullptr, 'm'},
                              {"help", no_argument, nullptr, 'h'},
                              { nullptr, 0, nullptr, '\0' }};
  int slp = 1;
  while ((option = getopt_long(argc, argv, "vs:mh", longOpts, &option_index)) != -1) {
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
  std::string buffer;
  // Testing
  sleep(slp);
  std::cout << "Test Start" << std::endl;
  std::cout << "Something " << std::endl;
  std::cin >> buffer;
  std::cout << buffer << std::endl;
  char c = choose("ABCDE");
  std::cout << "Chose: " << c << std::endl;
  c = choose("ABCDE");
  std::cout << "Chose: " << c << std::endl;

  Interface interface(std::cin, std::cout);
  Player player = create_player(interface);

  return 0;
}