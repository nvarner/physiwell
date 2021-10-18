#ifndef INTERFACE_H
#define INTERFACE_H

#include <ostream>
#include <string>

enum FontWeight { Bold, Normal, Light };

enum Color {
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
             const AnsiCode &ansi = AnsiCode::CLEAR) const;

  // Prompt the user with a given prompt, then return their response. The
  // response can take on any type the extraction operator `>>` supports.
  std::string prompt(const std::string &prompt) const;

private:
  std::istream &in;
  std::ostream &out;
};

#endif
