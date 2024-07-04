//
// Created by yanke on 5/31/2024.
//

#ifndef CKOOP_COMICPARSER_H
#define CKOOP_COMICPARSER_H
#include "IParserable.h"
#include "Comic.h"
class ComicParser : public IParserable {
public:
    Book* parseBook(string input) ;
};

#endif //CKOOP_COMICPARSER_H
