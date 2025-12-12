//Sam Emison
//12/11/2025
//EmailAddress.cpp

#include "EmailAddress.hpp"
#include <algorithm>
#include <stdexcept>

std::string EmailAddress::normalize(const std::string& email) {
  std::string lower = email;
  std::transform(lower.begin(), lower.end(), lower.begin(),
		 [](unsigned char c) { return std::tolower(c); });
  return lower;
}

void EmailAddress::validate(const std::string& email) {
  if (email.empty()) {
    throw std::invalid_argument("Email cannot be empty");
  }

  size_t atPos = email.find('@');
  if (atPos == std::string::npos) {
    throw std::invalid_argument("Email must contain '@'");
  }
  //Ensure there is only 1 '@'
  if (email.find('@', atPos + 1) != std::string::npos) {
    throw std::invalid_argument("Email cannot contain multiple '@' characters");
  }

  //Must have text before @
  if (atPos == 0) {
    throw std::invalid_argument("Email must have a local part before '@'");
  }

  //Must have text after @
  if (atPos == email.size() - 1) {
    throw std::invalid_argument("Email must have a domain part after '@'");
  }

  std::string domain = email.substr(atPos + 1);

  //Domain must contain at least one '.'
  if (domain.find('.') == std::string::npos) {
    throw std::invalid_argument("Email domain must contain '.'");
  }
}

EmailAddress::EmailAddress(const std::string& email) {
  std::string normalized = normalize(email);
  validate(normalized);
  value = normalized;
}

const std::string& EmailAddress::getValue() const {
  return value;
}

bool EmailAddress::operator==(const EmailAddress& other) const {
  return value == other.value;
}

bool EmailAddress::operator!=(const EmailAddress& other) const {
  return value != other.value;
}
