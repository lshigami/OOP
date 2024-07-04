//
// Created by yanke on 5/31/2024.
//

#ifndef CKOOP_BOOK_H
#define CKOOP_BOOK_H
#include "Ultils.h"
class Book {
protected:
    string name;
    string author;
    int year;
    double price;
public:
    Book(string name, string author, int year, double price) ;
    virtual string getName();
    virtual string getAuthor() ;
    virtual int getYear() ;
    virtual double getPrice();
    virtual string getType() = 0;
    virtual string getSpecial() = 0;
    virtual void display() {
        cout << std::left
             << std::setw(10) << getType() << " | "
             << std::setw(24) << getName() << " | "
             << std::setw(18) << getAuthor() << " | "
             << std::setw(6) << getYear() << " | "
             <<fixed<<setprecision(2)<< std::setw(10) << getPrice() << " | "
             << getSpecial() << std::endl;
    }
};

#endif //CKOOP_BOOK_H
