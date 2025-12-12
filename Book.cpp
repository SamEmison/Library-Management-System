//Sam Emison
//12/11/2025
//Book.cpp

#include "Book.hpp"
#include <stdexcept>

Book::Book(const ISBN& isbn, const std::string& title, const std::string& author)
  : isbn(isbn), title(title), author(author)
{
  if (title.empty()) {
    throw std::invalid_argument("Book title cannot be empty");
  }
  if (author.empty()) {
    throw std::invalid_argument("Book author cannot be empty");
  }
}

const ISBN& Book::getIsbn() const {
  return isbn;
}

const std::string& Book::getTitle() const {
  return title;
}

const std::string& Book::getAuthor() const {
  return author;
}

void Book::renameTitle(const std::string& newTitle) {
  if (newTitle.empty()) {
    throw std::invalid_argument("Book title cannot be empty");
  }
  title = newTitle;
}

void Book::changeAuthor(const std::string& newAuthor) {
  if (newAuthor.empty()) {
    throw std::invalid_argument("Book author cannot be empty");
  }
  author = newAuthor;
}
