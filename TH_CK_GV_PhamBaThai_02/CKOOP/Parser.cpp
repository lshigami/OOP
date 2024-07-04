//
// Created by yanke on 5/31/2024.
//
#include "Parser.h"
#include "FictionParser.h"
#include "NonFictionParser.h"
#include "ComicParser.h"

Parser::Parser() {
    parsers["Fiction"] = new FictionParser();
    parsers["NonFiction"] = new NonFictionParser();
    parsers["Comic"] = new ComicParser();
}
IParserable* Parser::getParser(string type) {
    return parsers[type];
}