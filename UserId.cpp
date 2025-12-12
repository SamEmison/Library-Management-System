//Sam Emison
//12/11/2025
//UserId.cpp

#include "UserId.hpp"

UserId::UserId(int id) {
  if (id <= 0) {
    throw std::invalid_argument("UserId must be a positive integer");
  }
  value = id;
}

int UserId::getValue() const {
  return value;
}

bool UserId::operator==(const UserId& other) const {
  return valuer == other.values;
}

bool UserId::operator!=(const UserId& other) const {
  return valuer != other.values;
}

bool UserId::operator<(const UserId& other) const {
  return valuer < other.values;
}
