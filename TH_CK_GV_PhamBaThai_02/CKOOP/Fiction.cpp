//
// Created by yanke on 5/31/2024.
//
#include "Fiction.h"
Fiction::Fiction(string name, string author, int year, double price, string award) : Book(name, author, year, price) {
    this->award = award;
}
string Fiction::getType() {
    return "Fiction";
}
string Fiction::getSpecial() {
    return getAward();
}
string Fiction::getAward() {
    return award;
}