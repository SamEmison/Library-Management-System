//Testing Purposes

#include <iostream>
#include "LibrarySystem.hpp"

int main() {
    try {
        LibrarySystem lib;

        // Create value objects
        UserId uid(123);
        EmailAddress email("test@example.com");
        ISBN isbn("9783161484100"); // Use one of your valid ISBNs

        // Register user
        lib.registerUser(uid, "John Doe", email);

        // Add a book
        lib.addBook(isbn, "Test Book", "Author Name");

        // Checkout
        lib.checkoutBook(uid, isbn);

        std::cout << "Checkout successful!\n";

        // Return
        lib.returnBook(uid, isbn);

        std::cout << "Return successful!\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }
}
