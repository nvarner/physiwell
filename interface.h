#ifndef INTERFACE_H
#define INTERFACE_H

#include <cstdint>
#include <functional>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "util.h"

#define MENU(interface, return_type, query, ...)                               \
  interface.menu(                                                              \
      query,                                                                   \
      std::vector<std::pair<std::string,                                       \
                            std::function<return_type(const Interface &)>>>{   \
          __VA_ARGS__})

#define MENU_OPTION(text, return_expression)                                   \
  {                                                                            \
    text, [&]([[maybe_unused]] const Interface &interface) {                   \
      return return_expression;                                                \
    }                                                                          \
  }

const int DEFAULT_TEXT_DELAY = 15;
const int DEFAULT_LONG_TEXT_DELAY = 100;

// // Debugging
// const int DEFAULT_TEXT_DELAY = 0;
// const int DEFAULT_LONG_TEXT_DELAY = 0;

enum FontWeight { Bold, Normal, Light };

enum Color : uint8_t {
  Black = 0,
  Red = 1,
  Green = 2,
  Yellow = 3,
  Blue = 4,
  Magenta = 5,
  Cyan = 6,
  White = 7,
  Default
};

class AnsiCode {
public:
  AnsiCode(const FontWeight font_weight, const bool emphasized,
           const bool blinking, const Color foreground = Color::Default,
           const Color background = Color::Default);

  std::string as_ascii() const;

  static const AnsiCode CLEAR;

private:
  const FontWeight font_weight;
  const bool emphasized;
  const bool blinking;
  const Color foreground;
  const Color background;
};

std::ostream &operator<<(std::ostream &out, const AnsiCode &code);

class Interface {
public:
  Interface(std::istream &in, std::ostream &out);

  void print(const std::string &to_print,
             const AnsiCode &ansi = AnsiCode::CLEAR,
             const int64_t delay = DEFAULT_TEXT_DELAY,
             const int64_t post_delay = DEFAULT_LONG_TEXT_DELAY) const;

  std::string input() const;

  // Prompt the user with a given prompt, then return their response.
  std::string prompt(const std::string &prompt) const;

  // Prompt the user to choose an option from a menu, then return the index of
  // the option they chose.
  template <typename T>
  T menu(const std::string &description,
         const std::vector<
             std::pair<std::string, std::function<T(const Interface &)>>>
             &options) const {
    while (true) {
      this->print(description + "\n", AnsiCode(FontWeight::Bold, false, false));
      for (size_t i = 0; i < options.size(); i++) {
        this->print(std::to_string(i + 1) + ". " + options[i].first + "\n",
                    AnsiCode::CLEAR);
      }
      std::string response = this->prompt("Choose an option.");
      if (is_numeric(response)) {
        size_t choice = std::stoi(response);
        if (choice > 0 && choice <= options.size()) {
          return options[choice - 1].second(*this);
        }
      }
      this->print("There is no option " + response + ".\n",
                  AnsiCode(FontWeight::Normal, false, false, Color::Red));
    }
  }

private:
  std::istream &in;
  std::ostream &out;

  void print_char(const char to_print,
                  int64_t ms_delay = DEFAULT_TEXT_DELAY) const;
  void print_ansi(const AnsiCode &ansi) const;
};

#endif
