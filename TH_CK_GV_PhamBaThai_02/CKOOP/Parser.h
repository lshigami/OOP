//
// Created by yanke on 5/31/2024.
//

#ifndef CKOOP_PARSER_H
#define CKOOP_PARSER_H
#include "IParserable.h"
class Parser{
private:
    unordered_map<string, IParserable*> parsers;
public:
    Parser();
    IParserable* getParser(string type) ;
    static Book* parseBook(string input) {
        Parser parser;
        string type=input.substr(0, input.find(","));
        IParserable* p = parser.getParser(type);
        Book* book = p->parseBook(input);
        return book;
    }
};

#endif //CKOOP_PARSER_H
