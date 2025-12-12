//Sam Emison
//12/12/2025
//Librarysystem.cpp

#include "LibrarySystem.hpp"
#include <stdexcept>
#include <algorithm>
#include <chrono>

// REGISTER USER
void LibrarySystem::registerUser(const UserId& id, const std::string& name, const EmailAddress& email) {
  // Check unique ID
  for (const auto& user : users) {
    if (user.getId() == id) {
      throw std::invalid_argument("User already exists");
    }
  }

  users.emplace_back(id, name, email);
}

//ADD BOOK
void LibrarySystem::addBook(const ISBN& isbn, const std::string& title, const std::string& author) {
  // No duplicate ISBNs allowed
  for (const auto& book : books) {
    if (book.getIsbn() == isbn) {
      throw std::invalid_argument("Book with same ISBN already exists");
    }
  }

  books.emplace_back(isbn, title, author);
}

//CHECKOUT BOOK
void LibrarySystem::checkoutBook(const UserId& userId, const ISBN& isbn) {
  // Check max loans
  if (countLoansForUser(userId) >= MAX_LOANS_PER_USER) {
    throw std::invalid_argument("User has reached maximum allowed loans");
  }

  //Book must exist
  auto bookIt = std::find_if(books.begin(), books.end(),
			     [&](const Book& b) { return b.getIsbn() == isbn; });

  if (bookIt == books.end()) {
     throw std::invalid_argument("Book does not exist");
  }

  //Book must NOT be currently loaned
  if (isBookLoaned(isbn)) {
    throw std::invalid_argument("Book is already loaned out");
  }


  //Create Loan
  auto now = std::chrono::system_clock::now();
  loans.emplace_back(userId, isbn, now);
}

//RETURN BOOK
void LibrarySystem::returnBook(const UserId& userId, const ISBN& isbn) {
  for (auto& loan : loans) {
    if (loan.getUserId() == userId && loan.getIsbn() == isbn && !loan.isReturned()) {
      loan.markReturned();
      return;
    }
  }

  throw std::invalid_argument("Loan record not found");
}

// CHECK IF BOOK IS LOANED
bool LibrarySystem::isBookLoaned(const ISBN& isbn) const {
  for (const auto& loan : loans) {
    if (loan.getIsbn() == isbn && !loan.isReturned()) {
      return true;
    }
  }
  return false;
}

//COUNT USER LOANS
int LibrarySystem::countLoansForUser(const UserId& userId) const {
  int count = 0;
  for (const auto& loan : loans) {
    if (loan.getUserId() == userId && !loan.isReturned()) {
      count++;
    }
  }
  return count;
}
