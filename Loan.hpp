#ifndef LOAN_HPP
#define LOAN_HPP

#include "UserId.hpp"
#include "ISBN.hpp"
#include <chrono>

class Loan {
private:
  UserId userId;
  ISBN isbn;
  std::chrono::system_clock::time_point checkoutDate;
  std::chrono::system_clock::time_point dueDate;
  bool returned;

public:

  // Constructor automatically sets due date to 4 weeks later
  Loan(const UserId& userId,
       const ISBN& isbn,
       const std::chrono::system_clock::time_point& checkoutDate);

  const UserId& getUserId() const;
  const ISBN& getIsbn() const;
  const std::chrono::system_clock::time_point& getCheckoutDate() const;
  const std::chrono::system_clock::time_point& getDueDate() const;

  bool isReturned() const;
  void markReturned();
};

#endif
