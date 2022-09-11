//
// Created by mhmdk on 4/16/2022.
//

#ifndef P1_RATINGLIST_H
#define P1_RATINGLIST_H
#include <string>
#include <iostream>

using namespace std;

class RatingList {
    int ratingsCount;   //keeps track of ratings count
    int capacity;
    //2d array each row => represents member, column =>book rate
    int** listOfRatings;
    string fileName;  // to read ratings from

public:

    RatingList(string);
    ~RatingList();
    void readFile();
    int getRate(int, int);
    void setNewRate(int ,int, int);
    void resize();

};




#endif //P1_RATINGLIST_H
