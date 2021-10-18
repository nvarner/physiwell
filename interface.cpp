#include "interface.h"
#include <cstdint>
#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <cassert>

Interface::Interface(std::istream &in_, std::ostream &out_)
    : in(in_), out(out_) {}

void Interface::print(const std::string &to_print, const AnsiCode &ansi) const {
    this->out << ansi << to_print << AnsiCode::CLEAR;
}

std::string Interface::prompt(const std::string &prompt) const {
  this->print(prompt, AnsiCode(FontWeight::Bold, false, false));
  this->print("\n> ", AnsiCode(FontWeight::Normal, false, true));

  std::string response;

  this->out << AnsiCode(FontWeight::Normal, true, false);
  this->in >> response;
  this->out << AnsiCode::CLEAR;

  return response;
}

uint8_t font_weight_code(const FontWeight & font_weight) {
    switch (font_weight) {
        case FontWeight::Bold:
            return 1;
        case FontWeight::Light:
            return 2;
        case FontWeight::Normal:
            return 0;
    }
    assert(false);
    return -1;
}

AnsiCode::AnsiCode(const FontWeight font_weight_, const bool emphasized_,
                   const bool blinking_, const Color foreground_,
                   const Color background_)
    : font_weight(font_weight_), emphasized(emphasized_), blinking(blinking_),
      foreground(foreground_), background(background_) {}

std::string AnsiCode::as_ascii() const {
    std::vector<uint8_t> args;

    uint8_t font_weight_arg = font_weight_code(this->font_weight);
    if (font_weight_arg != 0) {
        args.push_back(font_weight_arg);
    }

    if (this->emphasized) {
        args.push_back(4);
    }

    if (this->blinking) {
        args.push_back(5);
    }

    if (this->foreground != Color::Default) {
      args.push_back(this->foreground + 30);
    }
    if (this->background != Color::Default) {
      args.push_back(this->background + 40);
    }

    std::string ascii = "\x1b[0";
    for (size_t i = 0; i < args.size(); i++) {
        ascii += ";" + std::to_string(args[i]);
    }
    ascii += "m";


    return ascii;
}

const AnsiCode AnsiCode::CLEAR = AnsiCode(FontWeight::Normal, false, false, Color::White, Color::Black);

std::ostream & operator<<(std::ostream & out, const AnsiCode & code) {
    return out << code.as_ascii();
}
