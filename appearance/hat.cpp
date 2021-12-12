#include <string>

#include "hat.h"

Hat::Hat(const HatHeight height_, const std::string color_) : height(height_), color(color_) {}

const HatHeight & Hat::get_height() const {
    return this->height;
}

const std::string & Hat::get_color() const {
    return this->color;
}

std::string Hat::get_description() const {
    std::string height_description = (height == HatHeight::Short) ? "short" : "tall";
    return height_description + ", " + get_color() + " hat";
}
