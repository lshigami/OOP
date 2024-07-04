//
// Created by yanke on 5/31/2024.
//

#ifndef CKOOP_FICTION_H
#define CKOOP_FICTION_H
#include "Ultils.h"
#include "Book.h"
class Fiction : public Book {
private:
    string award;
public:
    Fiction(string name, string author, int year, double price, string award);
    string getType();
    string getSpecial();
    string getAward();
};

#endif //CKOOP_FICTION_H
