#ifndef GENDER_H
#define GENDER_H

#include <string>

class Gender {
public:
  static const Gender MALE;
  static const Gender FEMALE;
  static const Gender NB;

  Gender(const std::string name, const std::string nom, const std::string acc,
         const std::string reflex, const std::string ind_gen,
         const std::string dep_gen);

  // Get the name of the gender.
  // Eg. "male"
  const std::string &get_name() const;

  // Get the nominative pronoun.
  // Eg. "he"
  const std::string &get_nom() const;

  // Get the accusative pronoun.
  // Eg. "him"
  const std::string &get_acc() const;

  // Get the reflexive pronoun.
  // Eg. "himself"
  const std::string &get_reflex() const;

  // Get the independent genitive pronoun.
  // Eg. "hers"
  const std::string &get_ind_gen() const;

  // Get the dependent genitive pronoun.
  // Eg. "her"
  const std::string &get_dep_gen() const;

private:
  const std::string name;
  const std::string nom;     // he, she, they
  const std::string acc;     // him, her, them
  const std::string reflex;  // himself, herself, themselves
  const std::string ind_gen; // his, hers, theirs
  const std::string dep_gen; // his, her, their
};

#endif
