//
// Created by yanke on 5/31/2024.
//

#ifndef CKOOP_IPARSERABLE_H
#define CKOOP_IPARSERABLE_H
#include "Book.h"
class IParserable{
public:
    virtual Book* parseBook(string input) = 0;
};

#endif //CKOOP_IPARSERABLE_H
