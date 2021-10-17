#include "gender.h"
#include <string.h>

Gender::Gender(const std::string name_, const std::string nom_,
               const std::string acc_, const std::string reflex_,
               const std::string ind_gen_, const std::string dep_gen_)
    : name(name_), nom(nom_), acc(acc_), reflex(reflex_), ind_gen(ind_gen_),
      dep_gen(dep_gen_) {}

const Gender Gender::MALE =
    Gender("male", "he", "him", "himself", "his", "his");
const Gender Gender::FEMALE =
    Gender("female", "she", "her", "herself", "hers", "her");
const Gender Gender::NB =
    Gender("nonbinary", "they", "them", "themselves", "theirs", "their");

const std::string &Gender::get_name() const { return this->name; }

const std::string &Gender::get_nom() const { return this->nom; }

const std::string &Gender::get_acc() const { return this->acc; }

const std::string &Gender::get_reflex() const { return this->reflex; }

const std::string &Gender::get_ind_gen() const { return this->ind_gen; }

const std::string &Gender::get_dep_gen() const { return this->dep_gen; }
