//
// Created by yanke on 5/31/2024.
//

#ifndef CKOOP_COMIC_H
#define CKOOP_COMIC_H
#include "Book.h"
class Comic :public Book {
private:
    string series;
public:
    Comic(string name, string author, int year, double price, string series);
    string getType();
    string getSpecial();
    string getSeries();
};

#endif //CKOOP_COMIC_H
