#include "../include/LibraryTransaction.h"
#include <iostream>

using namespace std;

// Default constructor
LibraryTransaction::LibraryTransaction() {
    studentID = "";
    bookID = "";
    issueDate = "";
    dueDate = "";
    returnDate = "";
}

// Parameterized constructor
LibraryTransaction::LibraryTransaction(
    string student, string book,
    string issue, string due, string returned) {

    studentID = student;
    bookID = book;
    issueDate = issue;
    dueDate = due;
    returnDate = returned;
}

// Getter functions
string LibraryTransaction::getStudentID() const {
    return studentID;
}

string LibraryTransaction::getBookID() const {
    return bookID;
}

string LibraryTransaction::getIssueDate() const {
    return issueDate;
}

string LibraryTransaction::getDueDate() const {
    return dueDate;
}

string LibraryTransaction::getReturnDate() const {
    return returnDate;
}

// Set return date
void LibraryTransaction::setReturnDate(string date) {
    if (!date.empty()) {
        returnDate = date;
    }
}

// Check whether transaction is returned
bool LibraryTransaction::isReturned() const {
    return !returnDate.empty();
}

// Validate transaction details
bool LibraryTransaction::isValid() const {
    return !studentID.empty() &&
           !bookID.empty() &&
           !issueDate.empty() &&
           !dueDate.empty();
}

// Display transaction details
void LibraryTransaction::display() const {
    cout << "\nStudent ID: " << studentID;
    cout << "\nBook ID: " << bookID;
    cout << "\nIssue Date: " << issueDate;
    cout << "\nDue Date: " << dueDate;

    if (isReturned()) {
        cout << "\nReturn Date: " << returnDate;
    } else {
        cout << "\nReturn Status: Not Returned";
    }

    cout << endl;
}