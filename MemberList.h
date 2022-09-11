//
// Created by mhmdk on 4/16/2022.
//

#ifndef P1_MEMBERLIST_H
#define P1_MEMBERLIST_H
#include "RatingList.h"
#include "BookList.h"
#include <string>


class MemberList {
    bool logged_in;
    int capacity;
    int memCount;
    int activeUserIndex;
    string* members;
    string fileName;

public:

    MemberList(string);
    void addMember();
    void login();
    void logout();
    int getActiveUserIndex();
    int getMembersCount();
    string getMemberName(int);
    void rateBook(RatingList &rates, BookList &books);
    void getMembers();
    bool getLoginStatus() const;
    void getRecommedations(BookList &, RatingList &, int *);
    void resize();
    ~MemberList();


};


#endif //P1_MEMBERLIST_H
