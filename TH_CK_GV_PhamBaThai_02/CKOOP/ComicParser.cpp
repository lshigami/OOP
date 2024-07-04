//
// Created by yanke on 5/31/2024.
//

#include "ComicParser.h"
Book* ComicParser::parseBook(string input) {
    vector<string> v;
    stringstream ss(input);
    string token;
    while(getline(ss, token, ',')) {
        v.push_back(token);
    }
    string name = v[1];
    string author = v[2];
    int year = stoi(v[3]);
    double price = stod(v[4]);
    string series = v[5];
    return new Comic(name, author, year, price, series);
}

