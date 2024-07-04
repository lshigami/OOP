cmake_minimum_required(VERSION 3.26)
project(CKOOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(CKOOP main.cpp
        Book.h
        Ultils.h
        Book.cpp
        Fiction.h
        Fiction.cpp
        NonFiction.h
        NonFiction.cpp
        Comic.h
        Comic.cpp
        Library.h
        Library.cpp
        IParserable.h
        FictionParser.h
        FictionParser.cpp
        NonFictionParser.h
        NonFictionParser.cpp
        ComicParser.h
        ComicParser.cpp
        Parser.h
        Parser.cpp
)
