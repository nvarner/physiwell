#include "interface.h"

#include <cassert>
#include <cctype>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <istream>
#include <ostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

uint8_t font_weight_code(const FontWeight &font_weight) {
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

const AnsiCode AnsiCode::CLEAR = AnsiCode(FontWeight::Normal, false, false);

std::ostream &operator<<(std::ostream &out, const AnsiCode &code) {
  return out << code.as_ascii();
}

Interface::Interface(std::istream &in_, std::ostream &out_)
    : in(in_), out(out_) {}

void sleep(const int64_t delay) {
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void Interface::print(const std::string &to_print, const AnsiCode &ansi,
                      const int64_t delay, const int64_t post_delay) const {
  this->print_ansi(ansi);
  for (size_t i = 0; i < to_print.size(); i++) {
    this->print_char(to_print[i], delay);
  }
  this->print_ansi(AnsiCode::CLEAR);
  sleep(post_delay);
}

void Interface::print_char(const char to_print, int64_t delay) const {
  this->out << to_print;
  this->out.flush();
  sleep(delay);
}

void Interface::print_ansi(const AnsiCode &ansi) const { this->out << ansi; }

std::string Interface::input() const {
  this->in.clear();
  std::string response;
  this->out << AnsiCode(FontWeight::Normal, true, false);
  std::getline(this->in, response);
  this->out << AnsiCode::CLEAR;
  return response;
}

std::string Interface::prompt(const std::string &prompt) const {
  this->print(prompt, AnsiCode(FontWeight::Bold, false, false));
  this->print("\n> ", AnsiCode(FontWeight::Normal, false, true));
  std::string result = this->input();
  this->print("\n", AnsiCode::CLEAR);
  return result;
}


