#ifndef LIBRARY_SYSTEM_HPP
#define LIBRARY_SYSTEM_HPP

#include <vector>
#include <optional>
#include "User.hpp"
#include "Book.hpp"
#include "Loan.hpp"

class LibrarySystem {
private:
  std::vector<User> users;
  std::vector<Book> books;
  std::vector<Loan> loans;

  static constexpr int MAX_LOANS_PER_USER = 5;

public:
  LibrarySystem() = default;

  // User management
  void registerUser(const UserId& id, const std::string& name, const EmailAddress& email);

  // Book management
  void addBook(const ISBN& isbn, const std::string& title, const std::string& author);

  // Loan management
  void checkoutBook(const UserId& userId, const ISBN& isbn);
  void returnBook(const UserId& userId, const ISBN& isbn);

  // Helpers
  bool isBookLoaned(const ISBN& isbn) const;
  int countLoansForUser(const UserId& userId) const;
};

#endif
