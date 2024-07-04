//
// Created by yanke on 5/31/2024.
//

#include "FictionParser.h"
#include "Fiction.h"
Book* FictionParser::parseBook(string input) {
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
    string award = v[5];
    return new Fiction(name, author, year, price, award);
}
