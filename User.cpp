//Sam Emison
//12/11/2025
//User.cpp

#include "User.hpp"
#include <stdexcept>

User::User(const UserId& id, const std::string& name, const EmailAddress& email)
  : id(id), name(name), email(email)
{
  if (name.empty()) {
    throw std::invalid_argument("User name cannot be empty");
  }
}

const UserId& User::getId() const {
  return id;
}

const std::string& User::getName() const {
  return name;
}

const EmailAddress& User::getEmail() const {
  return email;
}

void User::rename(const std::string& newName) {
  if (newName.empty()) {
    throw std::invalid_argument("User name cannot be empty");
  }
  name = newName;
}

void User::changeEmail(const EmailAddress& newEmail) {
  email = newEmail;
}

//New Loan Stuff
const std::vector<Loan>& User::getLoans() const {
  return loans;
}

void User::checkoutBook(const ISBN& isbn,
                        const std::chrono::system_clock::time_point& now)
{
  //1. user must not exceed 5 active loans
  int activeCount = 0;
  for (const auto& loan : loans) {
    if (!loan.isReturned()) {
      activeCount++;
    }
  }

  if (activeCount >= 5) {
    throw std::runtime_error("User has reached the maximum loan limit (5)");
  }

  //2. user cannot borrow the same book twice unless returned
  for (const auto& loan : loans) {
    if (loan.getIsbn().getValue() == isbn.getValue() && !loan.isReturned()) {
      throw std::runtime_error("Book is already checked out by this user");
    }
  }

  //3. Add the loan
  loans.emplace_back(id, isbn, now);
}

void User::returnBook(const ISBN& isbn)
{
  for (auto& loan : loans) {
    if (loan.getIsbn().getValue() == isbn.getValue() && !loan.isReturned()) {
      loan.markReturned();
      return;
    }
  }

  throw std::runtime_error("Cannot return book: no active loan found for this ISBN");
}
