#include "Book.h"
#include "Fiction.h"
#include "NonFiction.h"
#include "Comic.h"
#include "Library.h"
#include "Parser.h"


int main() {
    int testID;
    std::cin >> testID;
    std::cout << "Test " << testID << ":" << std::endl;

    Library library;
    library.addBook(new Fiction("To Kill a Mockingbird", "Harper Lee", 1960, 18.99, "Pulitzer Prize"));
    library.addBook(new NonFiction("Sapiens", "Yuval Noah Harari", 2011, 22.50, "History"));
    library.addBook(new Comic("Spider-Man", "Stan Lee", 1962, 12.75, "Superhero"));

    std::vector<std::string> inputs = {
            "Fiction,1984,George Orwell,1949,15.00,Dystopian",
            "NonFiction,Educated,Tara Westover,2018,20.00,Memoir",
            "Comic,Batman,Bob Kane,1939,13.99,Detective"
    };

    for (const auto& input : inputs) {
        Book* book = Parser::parseBook(input);
        library.addBook(book);
    }

    library.display();

    return 0;
}