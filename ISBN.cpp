//Sam Emison
//12/11/2025
//ISBN.cpp

#include "ISBN.hpp"
#include <stdexcept>
#include <cctype>

//Remove hyphens/spaces, and converts to uppercase
std::string ISBN::normalize(const std::string& raw) {
  std::string out;
  out.reserve(raw.size());

  for (char c : raw) {
    if (std::isdigit(c)) {
      out.push_back(c);
    }
    else if (c == 'X' || c == 'x') {
      // Only valid as last character for ISBN-10
      out.push_back('X');
    }
  }

  return out;
}

//ISBN 10 Validating
bool ISBN::isValid10(const std::string& d) {
  if (d.size() != 10) return false;

  int sum = 0;
  for (int i = 0; i < 9; i++) {
    if (!std::isdigit(d[i])) return false;
    sum += (d[i] - '0') * (10 - i);
  }

  char last = d[9];
  int checkValue;

  if (last == 'X') checkValue = 10;
  else if (std::isdigit(last)) checkValue = last - '0';
  else return false;

  sum += checkValue;

  return (sum % 11 == 0);
}

//ISBN 13 Validating
bool ISBN::isValid13(const std::string& d) {
  if (d.size() != 13) return false;

  int sum = 0;
  for (int i = 0; i < 12; i++) {
    if (!std::isdigit(d[i])) return false;
    int digit = d[i] - '0';
    sum += (i % 2 == 0) ? digit : digit * 3;
  }

  int checkDigit = (10 - (sum % 10)) % 10;
  return checkDigit == (d[12] - '0');
}

//Constructer
ISBN::ISBN(const std::string& raw) {
  digits = normalize(raw);

  if (!(isValid10(digits) || isValid13(digits))) {
    throw std::invalid_argument("Invalid ISBN format or checksum");
  }
}

const std::string& ISBN::getValue() const {
  return digits;
}

bool ISBN::operator==(const ISBN& other) const {
  return digits == other.digits;
}

bool ISBN::operator!=(const ISBN& other) const {
  return digits != other.digits;
}
