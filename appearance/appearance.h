#include "gender.h"
#include "hat.h"

class Appearance {
public:
  Appearance(const Gender gender, const Hat hat);

  const Gender & get_gender() const;

  const Hat & get_hat() const;

private:
  Gender gender;
  Hat hat;
};