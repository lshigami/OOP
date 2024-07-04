//
// Created by yanke on 5/31/2024.
//

#include "NonFiction.h"
NonFiction::NonFiction(string name, string author, int year, double price, string genre) : Book(name, author, year, price) {
    this->genre = genre;
}
string NonFiction::getType() {
    return "NonFiction";
}
string NonFiction::getSpecial() {
    return getGenre();
}
string NonFiction::getGenre() {
    return genre;
}