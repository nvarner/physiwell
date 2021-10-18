#include <iostream>
#include <limits>
#include <getopt.h>
#include <istream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#include "player.h"

// Player create_player(std::istream & in, std::ostream & out) {
//     out << "What is your name?\n> ";
    
//     std::string name;
//     in >> name;
// }

// Whenever the player needs to make a multiple choice, use this function.
// parameter is a string that is a list of all potential choices.
// E.g. "ABC" for 3 choices - A, B, or C
// Returns the character they chose.
char choose(std::string choices, std::string err = "Incorrect Input. Try Again."){
  char choice;
  while (true){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
    std::cin >> choice;
    if (choices.find(choice) != std::string::npos) break;
    else std::cout << err << std::endl;
  }
  std::cout << "You selected: " << choice << std::endl;
  return choice;
}

int main(int argc, char** argv){
  int option_index = 0, option = 0;
  struct option longOpts[] = {{"verbose", no_argument, nullptr, 'v'},
                              {"statistics", required_argument, nullptr, 's'},
                              {"median", no_argument, nullptr, 'm'},
                              {"help", no_argument, nullptr, 'h'},
                              { nullptr, 0, nullptr, '\0' }};
  while ((option = getopt_long(argc, argv, "vs:mh", longOpts, &option_index)) != -1) {
    switch (option) {
      case 'v':
        break;
      case 's':
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
  std::cout << "Test Start" << std::endl;
  std::cout << "Something " << std::endl;
  std::cin >> buffer;
  std::cout << buffer << std::endl;
  char c = choose("ABCDE");
  std::cout << "Chose: " << c << std::endl;
  c = choose("ABCDE");
  std::cout << "Chose: " << c << std::endl;
  return 0; 
}