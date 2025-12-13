//Sam Emison
//12/11/2025
//Quantity.cpp

#include "Quantity.hpp"

Quantity::Quantity(int v) : value(v) {
  if (v <= 0) {
    throw std::invalid_argument("Quantity must be positive");
  }
}

int Quantity::getValue() const {
  return value;
}

Quantity Quantity::add(int amount) const {
  if (amount < 0)
    throw std::invalid_argument("Cannot add a negative amount");

  int result = value + amount;
  if (result > MAX_VALUE)
    throw std::invalid_argument("Resulting quantity exceeds maximum");

  return Quantity(result);
}

Quantity Quantity::subtract(int amount) const {
  if (amount < 0)
    throw std::invalid_argument("Cannot subtract a negative amount");

  int result = value - amount;
  if (result < MIN_VALUE)
    throw std::invalid_argument("Quantity cannot go negative");

  return Quantity(result);
}

bool Quantity::operator==(const Quantity& other) const {
  return value == other.value;
}

bool Quantity::operator!=(const Quantity& other) const {
  return value != other.value;
}
