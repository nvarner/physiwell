#ifndef SCENARIO_H
#define SCENARIO_H

#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <ratio>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <functional>
#include <utility>

#include "interface.h"
#include "player.h"

class Scenario {
public:
    Scenario(std::string path);
    void play(Player & player, const Interface & interface);

private:
    std::string title;
    std::ifstream file;

    class Command {
    public:
        virtual void run_command(
            Player & player,
            std::unordered_set<int> & choices_made,
            const Interface & interface
        ) const = 0;
    };

    class TextCommand : public Command {
    public:
        TextCommand(std::string & command) {
            size_t header_end_index = command.find_first_of("\n");
            size_t choice_start_index = 3; // Right after "~t "
            std::string choice_str = command.substr(choice_start_index, header_end_index - choice_start_index);

            choice = std::stoi(choice_str);
            text = command.substr(header_end_index + 1);
        }

        virtual void run_command(
            [[maybe_unused]] Player & player,
            std::unordered_set<int> & choices_made,
            const Interface & interface
        ) const override {
            if (choice == 0 || choices_made.find(choice) != choices_made.end()) {
                interface.print(text);
            }
        }

    private:
        int choice;
        std::string text;
    };

    class WatchCommand : public Command {
    public:
        WatchCommand(std::string & command) {
            size_t header_end_index = command.find_first_of("\n");
            size_t choice_start_index = 3; // Right after "~t "
            std::string choice_str = command.substr(choice_start_index, header_end_index - choice_start_index);

            choice = std::stoi(choice_str);
            text = command.substr(header_end_index + 1);
        }

        virtual void run_command(
            [[maybe_unused]] Player & player,
            std::unordered_set<int> & choices_made,
            const Interface & interface
        ) const override {
            if (player.has_physiwell() && (choice == 0 || choices_made.find(choice) != choices_made.end())) {
                interface.print(text);
            }
        }

    private:
        int choice;
        std::string text;
    };

    class ChoiceCommand : public Command {
    public:
        ChoiceCommand(std::string & command) : choices() {
            std::istringstream command_stream(command);
            std::string _;
            std::getline(command_stream, _); // Ignore the ~c line

            for (std::string line; std::getline(command_stream, line);) {
                choices.push_back(create_choice(line));
            }
        }

        virtual void run_command(
            [[maybe_unused]] Player & player,
            std::unordered_set<int> & choices_made,
            const Interface & interface
        ) const override {
            std::vector<std::pair<std::string, std::function<std::pair<int, std::string>(const Interface &)>>> options;
            for (size_t i = 0; i < choices.size(); i++) {
                const Choice & choice = choices[i];
                options.push_back(MENU_OPTION(choice.description, std::make_pair(choice.id, choice.confirmation)));
            }
            std::pair<int, std::string> choice = interface.menu("", options);
            choices_made.insert(choice.first);
            interface.print(choice.second + '\n');
        }
    
    private:
        struct Choice {
            int id;
            std::string description;
            std::string confirmation;
        };

        std::vector<Choice> choices;

        Choice create_choice(std::string & line) {
            Choice choice;
            size_t after_id;

            choice.id = std::stoi(line, &after_id);

            size_t desc_confirm_split = line.find_first_of('|');

            choice.description = line.substr(after_id + 1, desc_confirm_split - after_id - 1);
            choice.confirmation = line.substr(desc_confirm_split + 1);

            return choice;
        }
    };

    class AspectCommand : public Command {
    public:
        AspectCommand(std::string & command) {
            std::stringstream command_stream(command);
            std::string _;
            command_stream >> _; // throw away "~a"

            command_stream >> choice;
            command_stream >> aspect;
            command_stream >> delta;
        }

        virtual void run_command(
            Player & player,
            std::unordered_set<int> & choices_made,
            [[maybe_unused]] const Interface & interface
        ) const override {
            if (choice == 0 || choices_made.find(choice) != choices_made.end()) {
                 WellnessLevels & levels = player.get_wellness_levels();
                 if (aspect == "steps") {
                     levels.steps += delta;
                 } else if (aspect == "strength") {
                     levels.strength += delta;
                 } else if (aspect == "stress") {
                     levels.stress += delta;
                 } else if (aspect == "relations") {
                     levels.relations += delta;
                 } else if (aspect == "school") {
                     levels.school += delta;
                 } else if (aspect == "confidence") {
                     levels.confidence += delta;
                 }
            }
        }
    
    private:
        int choice;
        std::string aspect;
        int delta;
    };

    std::vector<std::unique_ptr<Command>> commands;
};

#endif
