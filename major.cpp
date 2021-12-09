#include "major.h"

Major::Major(std::string name_in) : name(name_in) {}

const std::string &Major::get_name() const {
    return name;
}

const Major Major::CS = Major("Computer Science");
const Major Major::PoliSci = Major("Political Science");
const Major Major::Undecided = Major("Undeclared");
