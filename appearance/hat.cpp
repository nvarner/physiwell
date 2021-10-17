#include <string>

#include "hat.h"

Hat::Hat(const HatHeight height_, const std::string color_) : height(height_), color(color_) {}

const HatHeight & Hat::get_height() const {
    return this->height;
}

const std::string & Hat::get_color() const {
    return this->color;
}
