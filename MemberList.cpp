//
// Created by mhmdk on 4/16/2022.
//

#include "MemberList.h"
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

MemberList::MemberList(string myFile) {
    capacity = 10;
    activeUserIndex = 0;  //represent the logged-in user account number
    memCount = 1;
    members =  new string[capacity];
    logged_in = false;
    fileName = myFile;
    getMembers();   // populate members int the members array
}
// adds one member
void MemberList::addMember() {
    if (memCount == capacity-1)
        resize();
    string memName;
    getline(cin, memName); // consume the first line
    cout << "Enter the name of the new member: ";
    getline(cin, memName);
    members[memCount] = memName;
    cout << members[memCount];
    cout << " (account #: "<< memCount << ") was added.";
    memCount++;
}
// log in user
void MemberList::login() {
    int AccNum;
    cout << "Enter member account:";
    cin >> AccNum;
    if (AccNum > 0 and AccNum < memCount){
        cout << members[AccNum];
        cout << ", you are logged in!" << endl;
        logged_in = true;
        activeUserIndex = AccNum;
    }
    else {
        cout << "Sorry! your account never created";
    }
}
// log out
void MemberList::logout() {
    logged_in = false;

}
//checks if any user logged in
bool MemberList::getLoginStatus() const {
    return logged_in;
}
// populate members by reading them from ratings file
void MemberList::getMembers() {

    fstream myFile;
    myFile.open(fileName, ios::in);
    string line;
    while (getline(myFile, line)) {
        if (line.length() < 20) {
            if (memCount == capacity-1)
                resize();
            members[memCount] = line;
            memCount++;
        }
    }
}
// rates a book or re-rate a book
void MemberList::rateBook(RatingList &rates, BookList &books) {
    int isbn;
    int newRating;
    cout << "Enter the ISBN for the book you'd like to rate: ";
    cin >> isbn;
    if (rates.getRate(activeUserIndex,isbn) != 0){
        char answer;
        cout << "Your current rating for ";
        cout << books.getBookDetails(isbn) << " => rating: " <<
        rates.getRate(activeUserIndex, isbn) << endl;

        cout << "Would you like to re-rate this book (y/n)?";
        cin >> answer;
        if (answer == 'y'){
                cout << "Enter your rating:";
                cin >> newRating;
            } else
            return;
    } else {
        cout << "Enter your rating: ";
        cin >> newRating;
    }
    rates.setNewRate(activeUserIndex, isbn, newRating);

    cout << "Your new rating for " + books.getBookDetails(isbn) << " => rating: " <<
    rates.getRate(activeUserIndex,isbn);
    cout << endl;
}

void MemberList::getRecommedations(BookList &bookObj, RatingList &rates, int *recomList) {

    int listCounter = 0;  // keeps track of books in the recommendation list
    int memberIndex = 1;  // temp pointer to iterate list of members
    int max = 0;
    int sum = 0;    // sum of dot product of ratings for two members
    int similarMemIndex;   // the account number matched member.
    while (memberIndex < memCount) {
        for (int i = 1; i < bookObj.getBookCount(); i++) {
            if (memberIndex == activeUserIndex) continue;
            sum += rates.getRate(memberIndex,i) * rates.getRate(activeUserIndex,i);
        }
        if (sum > max){
            max = sum;
            similarMemIndex = memberIndex;
        }
        sum = 0;
        memberIndex++;
    }
    cout << "You have similar taste in books as "
         <<members[similarMemIndex] << "!" << endl;

    for (int i = 1 ; i < bookObj.getBookCount() ; i++){
        if (rates.getRate(similarMemIndex,i)== 5 && rates.getRate(activeUserIndex,i) == 0){
            recomList[listCounter] = i;
            listCounter++;
        }
    }
    // -1 denoting the end of first list of recommendation (the really liked)
    recomList[listCounter] = -1;
    listCounter++;

    for (int i = 1 ; i < bookObj.getBookCount() ; i++){
        if (rates.getRate(similarMemIndex,i) == 3 && rates.getRate(activeUserIndex,i) == 0){
            recomList[listCounter] = i;
            listCounter++;
        }
    }
    // denoting the end of second list of recommendation
    recomList[listCounter] = -2;
}
// returns the account number of logged in user
int MemberList::getActiveUserIndex() {
    return activeUserIndex;
}
// return member name by providing his account number
string MemberList::getMemberName(int AccNum) {
    return members[AccNum];
}
int MemberList::getMembersCount() {
    return memCount;
}
// resize the list of members
void MemberList::resize() {
    capacity = capacity * 2;
    string* biggerArray = new string[capacity];
    for (int i = 1; i < memCount ; i++){
        biggerArray[i] = members[i];
    }
    delete[] members;
    members = biggerArray;
}
//deconstructor
MemberList::~MemberList() {
    delete [] members;
}
