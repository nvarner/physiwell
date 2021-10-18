#include "appearance.h"

Appearance::Appearance(const Gender gender_, const Hat hat_)
    : gender(gender_), hat(hat_) {}

const Gender &Appearance::get_gender() const {
    return this->gender;
}

const Hat &Appearance::get_hat() const {
    return this->hat;
}
