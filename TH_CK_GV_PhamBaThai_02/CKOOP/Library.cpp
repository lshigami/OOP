//
// Created by yanke on 5/31/2024.
//
#include "Library.h"

void Library::addBook(Book* book) {
    books.push_back(book);
}
void Library::display() {
    std::cout << std::left << std::setw(10) << "Type" << " | "
              << std::setw(24) << "Name" << " | "
              << std::setw(18) << "Author" << " | "
              << std::setw(6) << "Year" << " | "
              << std::setw(10) << "Price" << " | "
              << "Special" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    for (auto book : books) {
        book->display();
    }
}
