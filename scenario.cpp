#include "scenario.h"
#include <memory>

Scenario::Scenario(std::string path) : title(""), file(std::ifstream(path)), commands() {
    std::getline(file, title);

    std::string lines;
    for (std::string line; std::getline(file, line);) {
        if (line[0] == '~') {
            // TODO: Could not figure out how to refactor this into a function due to privacy rules with Command
            switch (lines[1]) {
                case 't':
                    commands.push_back(std::make_unique<TextCommand>(lines));
                    break;
                case 'w':
                    commands.push_back(std::make_unique<WatchCommand>(lines));
                    break;
                case 'c':
                    commands.push_back(std::make_unique<ChoiceCommand>(lines));
                    break;
                case 'a':
                    commands.push_back(std::make_unique<AspectCommand>(lines));
                    break;
            }
            lines = "";
        }
        lines += line + '\n';
    }
    switch (lines[1]) {
        case 't':
            commands.push_back(std::make_unique<TextCommand>(lines));
            break;
        case 'w':
            commands.push_back(std::make_unique<WatchCommand>(lines));
            break;
        case 'c':
            commands.push_back(std::make_unique<ChoiceCommand>(lines));
            break;
        case 'a':
            commands.push_back(std::make_unique<AspectCommand>(lines));
            break;
    }
}

void Scenario::play(Player & player, const Interface & interface) {
    interface.print(title + "\n\n");

    std::unordered_set<int> choices_made;

    for (std::unique_ptr<Command> & command : commands) {
        command->run_command(player, choices_made, interface);
    }
}
