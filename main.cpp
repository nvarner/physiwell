#include <iostream>
#include <limits>
#include <getopt.h>
#include <istream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

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

int main(int argc, char** argv){
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
  return 0; 
}