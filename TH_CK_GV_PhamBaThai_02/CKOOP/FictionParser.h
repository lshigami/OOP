//
// Created by yanke on 5/31/2024.
//

#ifndef CKOOP_FICTIONPARSER_H
#define CKOOP_FICTIONPARSER_H

#include "IParserable.h"
class FictionParser : public IParserable {
public:
    Book* parseBook(string input) ;
};
#endif //CKOOP_FICTIONPARSER_H
