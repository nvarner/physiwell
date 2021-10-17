#include <iostream>
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

  return 0; 
}