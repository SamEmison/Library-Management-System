#include <gtest/gtest.h> //Google file

#include "UserId.hpp"
#include "EmailAddress.hpp"
#include "ISBN.hpp"
#include "Quantity.hpp"
#include "Book.hpp"
#include "User.hpp"
#include "Loan.hpp"
#include "LibrarySystem.hpp"

//I prompted chatgpt for my unit test cases. I gave it an example of test cases from the final and gave it a brief overview of the project and what files were included in the project. I felt like this was the best way to not have any bias and find issues in my code if they were to arise.


// Value Object Tests
TEST(Task1, UserIdValidation) {
    EXPECT_THROW(UserId(""), std::invalid_argument);
    EXPECT_NO_THROW(UserId("U123"));
}

TEST(Task1, EmailValidation) {
    EXPECT_THROW(EmailAddress(""), std::invalid_argument);
    EXPECT_THROW(EmailAddress("not-an-email"), std::invalid_argument);
    EXPECT_NO_THROW(EmailAddress("test@example.com"));
}

TEST(Task1, ISBNValidation) {
    EXPECT_THROW(ISBN("123"), std::invalid_argument);
    EXPECT_THROW(ISBN("abcdefghijklm"), std::invalid_argument);
    EXPECT_NO_THROW(ISBN("9783161484100"));
}

TEST(Task1, QuantityValidation) {
    EXPECT_THROW(Quantity(0), std::invalid_argument);
    EXPECT_THROW(Quantity(-1), std::invalid_argument);
    EXPECT_NO_THROW(Quantity(1));
}

//Entity Tests

TEST(Task2, BookCreation) {
    ISBN isbn("9783161484100");
    EXPECT_THROW(Book(isbn, "", "Author"), std::invalid_argument);
    EXPECT_THROW(Book(isbn, "Title", ""), std::invalid_argument);

    Book book(isbn, "Secure by Design", "John Doe");
    EXPECT_EQ(book.getTitle(), "Secure by Design");
    EXPECT_EQ(book.getAuthor(), "John Doe");
}

TEST(Task2, UserCreation) {
    UserId uid("U001");
    EmailAddress email("user@example.com");

    EXPECT_THROW(User(uid, "", email), std::invalid_argument);

    User user(uid, "Alice", email);
    EXPECT_EQ(user.getName(), "Alice");
}
//Lona test
TEST(Task3, LoanLifecycle) {
    UserId uid("U100");
    ISBN isbn("9783161484100");

    auto now = std::chrono::system_clock::now();
    Loan loan(uid, isbn, now);

    EXPECT_FALSE(loan.isReturned());
    EXPECT_NO_THROW(loan.markReturned());
    EXPECT_TRUE(loan.isReturned());
}


//Backend / Service Tests

TEST(Task4, LibrarySystemCheckoutAndReturn) {
    LibrarySystem system;

    UserId uid("U200");
    EmailAddress email("borrower@example.com");
    ISBN isbn("9783161484100");

    EXPECT_NO_THROW(system.registerUser(uid, "Bob", email));
    EXPECT_NO_THROW(system.addBook(isbn, "C++ Security", "Author"));

    EXPECT_NO_THROW(system.checkoutBook(uid, isbn));
    EXPECT_THROW(system.checkoutBook(uid, isbn), std::invalid_argument); // already loaned

    EXPECT_NO_THROW(system.returnBook(uid, isbn));
}

TEST(Task4, MaxLoanLimit) {
    LibrarySystem system;

    UserId uid("U300");
    EmailAddress email("limit@example.com");
    system.registerUser(uid, "Charlie", email);

    for (int i = 0; i < 5; ++i) {
        ISBN isbn("97831614841" + std::to_string(10 + i));
        system.addBook(isbn, "Book " + std::to_string(i), "Author");
        system.checkoutBook(uid, isbn);
    }

    ISBN extra("9783161484199");
    system.addBook(extra, "Extra Book", "Author");

    EXPECT_THROW(system.checkoutBook(uid, extra), std::invalid_argument);
}

//Test Runner

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
