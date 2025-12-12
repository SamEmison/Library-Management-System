#ifndef EMAILADDRESS_HPP
#define EMAILADDRESS_HPP

#include <string>

class EmailAddress {
private:
  std::string value;

  static std::string normalize(const std::string& email);
  static void validate(const std::string& email);

public:
  explicit EmailAddress(const std::string& email);

  const std::string& getValue() const;

  bool operator==(const EmailAddress& other) const;
  bool operator!=(const EmailAddress& other) const;
};

#endif
