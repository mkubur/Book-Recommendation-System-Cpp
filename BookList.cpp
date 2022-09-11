//
// Created by mhmdk on 4/16/2022.
//

#include "BookList.h"
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <iostream>

BookList::BookList(string myFile)  {
    fileName = myFile;
    capacity = 100;
    bookList = new Book[capacity];
    bookCount = 1;
    readFile();
}
// this method read file and manipulate the data into dynamic array
// each node is one book details. all bookds are saved the array
void::BookList::readFile(){
    fstream myFile;
    myFile.open(fileName, ios::in);
    if (myFile) {
        int i = 0;
        string temp[3];  // holds details of one book
        string line;
        while(getline(myFile, line)){ // reads a whole line
            stringstream ss(line);
            while (ss.good()) {   //divides the line by "," and save tokens to temp array
                string substr;
                getline(ss, substr, ',');
                temp[i] = substr;
                i++;
            }
            this->addBook(temp[0], temp[1],temp[2]);
            i = 0;
        }
        myFile.close();
    }
    else {
        cout << "Invalid file path!" << std::endl;
        return;
    }
}
// Function to insert a new node.
void BookList::addBook(string auth, string tit, string yr)
{
    if (bookCount == capacity){
        resize();
    }
    // Create the new Book.
    Book newBook;
    newBook.author = auth;
    newBook.title = tit;
    newBook.year = yr;
    newBook.ISBN = this->bookCount;
    bookList[bookCount] = newBook;
    bookCount++;
}

// deconstructor
BookList::~BookList() {
    delete[] bookList;
}
void BookList::addBook() {
    string author;
    string title;
    string year;

    getline(cin, author); // consumes the first line
    cout << "Enter the author of the new book:";
    getline(cin, author);

    cout << "Enter the title of the new book:";
    getline(cin, title);

    cout << "Enter the year (or range of years) of the new book:";
    getline(cin , year);

    addBook(author, title, year);

}
int BookList::getBookCount() {
    return bookCount;
}
BookList::Book BookList::getBook(int b) {
    return bookList[b];
}
string BookList::getBookDetails(int isbn) {
    string details;
     details += to_string(getBook(isbn).ISBN) + ", ";
    details += getBook(isbn).author + ", ";
    details += getBook(isbn).title + ", ";
    details += getBook(isbn).year;
    return details;
}

void BookList::resize() {
    Book* tempList = new Book[bookCount * 2];
    for (int i = 1 ; i < bookCount ; i++){
        tempList[i] = bookList[i];
    }
    delete[] bookList;
    bookList = tempList;
}


