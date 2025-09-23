#ifndef BOOK_H
#define BOOK_H

#include <iostream>

struct Book {
    int id;
    std::string title;
    std::string author;
    std::string genre;
    int year;
    double rating;
};

#endif