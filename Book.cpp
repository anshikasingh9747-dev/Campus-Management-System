#include "../include/Book.h"
#include <iostream>

using namespace std;

// Default constructor
Book::Book() {
    bookID = "";
    title = "";
    author = "";
    category = "";
    availableCopies = 0;
}

// Parameterized constructor
Book::Book(string id, string bookTitle, string bookAuthor,
           string bookCategory, int copies) {
    bookID = id;
    title = bookTitle;
    author = bookAuthor;
    category = bookCategory;
    availableCopies = copies;
}

// Getter functions
string Book::getBookID() const {
    return bookID;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getCategory() const {
    return category;
}

int Book::getAvailableCopies() const {
    return availableCopies;
}

// Issue a book copy
bool Book::issueCopy() {
    if (availableCopies <= 0) {
        return false;
    }

    availableCopies--;
    return true;
}

// Return a book copy
bool Book::returnCopy() {
    availableCopies++;
    return true;
}

// Validate book details
bool Book::isValid() const {
    return !bookID.empty() &&
           !title.empty() &&
           !author.empty() &&
           !category.empty() &&
           availableCopies >= 0;
}

// Display book details
void Book::display() const {
    cout << "\nBook ID: " << bookID;
    cout << "\nTitle: " << title;
    cout << "\nAuthor: " << author;
    cout << "\nCategory: " << category;
    cout << "\nAvailable Copies: " << availableCopies << endl;
}