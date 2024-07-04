//
// Created by yanke on 5/31/2024.
//

#ifndef CKOOP_NONFICTIONPARSER_H
#define CKOOP_NONFICTIONPARSER_H
#include "IParserable.h"

class NonFictionParser : public IParserable {
public:
    Book* parseBook(string input);
};

#endif //CKOOP_NONFICTIONPARSER_H
