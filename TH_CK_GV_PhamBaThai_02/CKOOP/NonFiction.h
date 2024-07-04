//
// Created by yanke on 5/31/2024.
//

#ifndef CKOOP_NONFICTION_H
#define CKOOP_NONFICTION_H
#include "Book.h"
class NonFiction : public Book {
private:
    string genre;
public:
    NonFiction(string name, string author, int year, double price, string genre);
    string getType();
    string getSpecial();
    string getGenre();
};

#endif //CKOOP_NONFICTION_H
