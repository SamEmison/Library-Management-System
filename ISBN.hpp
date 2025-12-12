#ifndef ISBN_HPP
#define ISBN_HPP

#include <string>

class ISBN {
private:
  std::string digits;

  static std::string normalize (const std::string& raw);
  static bool isValid10(const std::string& d);
  static bool isValid13(const std::string& d);

public:
  explicit ISBN(const std::string& raw);

  const std::string& getValue() const;

  bool operator==(const ISBN& other) const;
  bool operator!=(const ISBN& other) const;
};

#endif

