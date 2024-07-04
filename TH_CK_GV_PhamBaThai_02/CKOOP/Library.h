//
// Created by yanke on 5/31/2024.
//

#ifndef CKOOP_LIBRARY_H
#define CKOOP_LIBRARY_H
#include "Book.h"
class Library {
private:
    vector<Book*> books;
public:
    void addBook(Book* book);
    void display();
};

#endif //CKOOP_LIBRARY_H
