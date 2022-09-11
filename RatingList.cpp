//
// Created by mhmdk on 4/16/2022.
//

#include "RatingList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>


using namespace std;

RatingList::RatingList(string myFile) {
    ratingsCount = 1;
    capacity = 100;
    listOfRatings = new int *[capacity];
    fileName = myFile;
    readFile();
}
// reads the ratings file and populate ratings into 2d array
void RatingList::readFile() {

    fstream myFile;
    myFile.open(fileName, ios::in);
    int row = 1;       // represent rows of rating array
    string line;       // hold the reading of one line
//    for (int i = 0 ; i < capacity ; i++){
//        listOfRatings[i] = new int[capacity];
//    }
    if (myFile) {
        while (getline(myFile, line)) {
            if (line.length() < 20) {
            } else {
                istringstream digit(line);
                int num;
                int col = 1;
                // this initializes all member ratings to 0's
                listOfRatings[row] = new int[capacity];
                while (digit >> num) {
                    if (ratingsCount == capacity){
                        //resize();
                    }
                    listOfRatings[row][col] = num;
                    col++;
                }
                ratingsCount = col;
                row++;
            }
        }
        myFile.close();
    } else {
        cout << "Invalid file path!" << std::endl;
        return;
    }

}

int RatingList::getRate(int mem, int bookIndex) {
    return listOfRatings[mem][bookIndex];
}
void RatingList::setNewRate(int user, int bookIndex, int newRate) {

    listOfRatings[user][bookIndex] = newRate;
}
void RatingList::resize() {
    int newCapacity =  capacity * 2;
    int ** biggerArray = new int*[newCapacity];
    // create new 2d array with double size
    for (int i = 0 ; i < newCapacity ; i++){
        biggerArray[i] = new int[newCapacity];
    }

    // copying all elements to the new array
    for (int i = 1; i < ratingsCount ; i++){
        for (int j = 1 ; j < ratingsCount ; j++){
            biggerArray[i][j] = listOfRatings[i][j];
        }
    }
    capacity = newCapacity;
    // deleting the old array
    for (int i = 0 ; i < capacity; i++){
        delete listOfRatings[i];
    }
    delete[] listOfRatings;
    // assigning old array to the new bigger array
    listOfRatings = biggerArray;
}



RatingList::~RatingList(){
    for (int i = 0 ; i < capacity; i++){
        delete listOfRatings[i];
    }
    delete[] listOfRatings;
}
