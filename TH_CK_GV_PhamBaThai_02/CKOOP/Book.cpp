//
// Created by yanke on 5/31/2024.
//
#include "Book.h"
Book::Book(string name, string author, int year, double price) {
    this->name = name;
    this->author = author;
    this->year = year;
    this->price = price;
}
string Book::getName() {
    return name;
}
string Book::getAuthor() {
    return author;
}
int Book::getYear() {
    return year;
}
double Book::getPrice() {
    return price;
}