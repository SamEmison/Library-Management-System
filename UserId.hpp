#ifndef USERID_HPP
#define USERID_HPP


#include <stdexcept>

class UserId {
private:
  int value;

public:
  explicit UserId(int id);

  int getValue() const;

  bool operator==(const UserId& other) const;
  bool operator!=(const UserId& other) const;
  bool operator<(const UserId& other) const;
};

#endif
