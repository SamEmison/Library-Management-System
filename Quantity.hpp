#ifndef QUANTITY_HPP
#define QUANTITY_HPP

#include <stdexcept>

class Quantity {
private:
  int value;
  static constexpr int MIN_VALUE = 0;
  static constexpr int MAX_VALUE = 1000;

public:
  explicit Quantity(int v);

  int getValue() const;

  Quantity add(int amount) const;
  Quantity subtract(int amount) const;

  bool operator==(const Quantity& other) const;
  bool operator!=(const Quantity& other) const;
};

#endif

