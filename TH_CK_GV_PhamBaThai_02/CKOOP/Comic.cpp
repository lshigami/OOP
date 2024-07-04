//
// Created by yanke on 5/31/2024.
//

#include "Comic.h"
Comic::Comic(string name, string author, int year, double price, string series) : Book(name, author, year, price) {
    this->series = series;
}
string Comic::getType() {
    return "Comic";
}
string Comic::getSpecial() {
    return getSeries();
}
string Comic::getSeries() {
    return series;
}
