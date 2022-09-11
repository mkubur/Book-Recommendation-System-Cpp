/**
 * This program give individualized recommendations of books according to people with similar
 * interest.
 **/
#include <iostream>
#include <fstream>
#include "RatingList.h"
#include "BookList.h"
#include "MemberList.h"
#include <string>
using namespace std;
void welcomeMsg();
string getBookFile();
string getRatingsFile();
void printCounts(MemberList&,BookList&);
void viewAllRatings(MemberList&,RatingList&, BookList&);
void printNewlyAddedBook(BookList &bookObj);
void printRecommendations(MemberList&,RatingList&, BookList&);
void nonMemberUI();
void memberUI();
int main() {
    welcomeMsg();

    string booksFile = getBookFile();
    string ratingsFile = getRatingsFile();

    BookList myBooks(booksFile);  // creates bookList obj
    RatingList ratings(ratingsFile);  // create ratingList obj
    MemberList memObj(ratingsFile);   // creates memberList obj
    printCounts(memObj, myBooks);
    while (!memObj.getLoginStatus()){
            nonMemberUI();
        int option;
        cout << "Enter a menu option:";
        cin >> option;
        if (option == 1){
            memObj.addMember();
        }
        if (option == 2){
            myBooks.addBook();
            printNewlyAddedBook(myBooks);
        }
        if (option == 3){
            memObj.login();
            if (memObj.getLoginStatus()){
                while (memObj.getLoginStatus()){
                    memberUI();
                    cout << "Enter a menu option: ";
                    cin >> option;
                    if (option == 1){
                        memObj.addMember();
                    }
                    if (option == 2){
                        myBooks.addBook();
                        printNewlyAddedBook(myBooks);
                    }
                    if (option == 3){
                        memObj.rateBook(ratings,myBooks);
                    }
                    if (option == 4)
                        viewAllRatings(memObj, ratings, myBooks);
                    if (option == 5)
                        printRecommendations(memObj,ratings,myBooks);
                    if (option == 6){
                        memObj.logout();
                        break;
                    }
                }
            }
        }
        if (option == 4){
            cout << "\nThank you for using  the Book Recommendation Program!\n";
            return 0;
        }
    }
    return 0;
}
// logged in user interface
void memberUI(){
    cout << "\n************** MENU **************" << endl;
    cout << "* 1. Add a new member            *\n"
            "* 2. Add a new book              *\n"
            "* 3. Rate book                   *\n"
            "* 4. View ratings                *\n"
            "* 5. See recommendations         *\n"
            "* 6. Logout                      *\n"
            "**********************************" << endl;
}
// logged out user interface
void nonMemberUI(){
    cout << "\n************** MENU **************\n"
            "* 1. Add a new member            *\n"
            "* 2. Add a new book              *\n"
            "* 3. Login                       *\n"
            "* 4. Quit                        *\n"
            "**********************************" << endl;
}
// welcome message
 void welcomeMsg(){
    cout << "Welcome to the Book Recommendation Program.\n"
            "This program reads and manages books, members and ratings.\n"
            " Also gives recommendations about books to read\n" << endl;
}
// prints all ratings to screen
void viewAllRatings(MemberList& member, RatingList &rates, BookList &bookObj){
    cout << member.getMemberName(member.getActiveUserIndex()) <<
    " ratings..." << endl;
    for (int i = 1 ; i < bookObj.getBookCount(); i++){
        cout << bookObj.getBookDetails(i) << " => rating: " <<
        rates.getRate(member.getActiveUserIndex(), i) << endl;
    }
}
// prints the last added book
void printNewlyAddedBook(BookList &bookObj){
    int bookISBN = bookObj.getBookCount() -1 ;
    cout << bookObj.getBookDetails(bookISBN) << " was added!" << endl;
}
/*
 * This method receive recommendation as a list of books and
 * prints these books recommendations.
 */
void printRecommendations(MemberList& memObj,RatingList& rateObj, BookList& bookOBJ){
    // initializing array will hold ISBN of recommended books

    int* recomList = new int[100];
    memObj.getRecommedations(bookOBJ,rateObj,recomList);
    cout << "\nHere are the books they really liked: " << endl;
    int i = 0;
    for ( ; i < 100 ; i++){
        if (recomList[i] == -1){ // breaks out if we reach end of the first list
            i++;
            break;
        }
        cout << bookOBJ.getBookDetails(recomList[i]) << endl;
    }

    cout << "\nAnd here are the books they liked:" << endl;
    // this loop will continue until the end signal (-2)
    for ( ; i < 100 ; i++){
        if (recomList[i] == -2) break; //breaks if we reach end of second list
        cout << bookOBJ.getBookDetails(recomList[i]) << endl;
    }


}
// takes the user input for books file name and validate it
string getBookFile(){
    string booksFileName;
    fstream booksFile;
    while (true){
        cout << "Enter book file: ";
        cin >> booksFileName;
        booksFile.open (booksFileName, ios::in);
        if (booksFile){
            booksFile.close();
            break;
        } else {
            cout << "invalid file path!\n";

            getline(cin, booksFileName);
        }

    }
    return booksFileName;

}
// takes the user input for ratings file name and validat it.
string getRatingsFile(){
    string ratingsFileName;
    fstream ratingsFile;
    while (true){
    cout << "Enter rating file: ";
    cin >> ratingsFileName;
    ratingsFile.open (ratingsFileName,ios::in);
    if (ratingsFile){
        ratingsFile.close();
        break;
    } else {
        cout << "invalid file path!\n";

        getline(cin, ratingsFileName);
    }

}
    return ratingsFileName;

}
// prints count of books and members
void printCounts(MemberList& memObj,BookList& bookOBJ){
    cout << "# of books: " << bookOBJ.getBookCount()-1 << endl;
    cout << "# of memberList: " << memObj.getMembersCount()-1 << endl;
}

