#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include "ISBN.hpp"

class Book {
private:
  ISBN isbn;
  std::string title;
  std::string author;

public:
  Book(const ISBN& isbn, const std::string& title, const std::string& author);

  const ISBN& getIsbn() const;
  const std::string& getTitle() const;
  const std::string& getAuthor() const;

  void renameTitle(const std::string& newTitle);
  void changeAuthor(const std::string& newAuthor);
};

#endif
