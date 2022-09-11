//
// Created by mhmdk on 4/16/2022.
//

#ifndef P1_BOOKLIST_H
#define P1_BOOKLIST_H
#include <string>
#include <iostream>
using namespace std;


class BookList {
    struct Book {
        string author;
        string title;
        string year;
        int ISBN;
    };
    Book* bookList;
    int bookCount;
    int capacity;
    string fileName;
public:
    // Default constructor
    BookList(string);
    void readFile();
    int getBookCount();
    Book getBook(int);
    void resize();
    void addBook(string, string, string);
    void addBook();
    string getBookDetails(int);
    ~BookList();
};

#endif //P1_BOOKLIST_H
