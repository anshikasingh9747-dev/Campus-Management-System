#ifndef LIBRARY_TRANSACTION_H
#define LIBRARY_TRANSACTION_H

#include <string>
using namespace std;

class LibraryTransaction {
private:
    string studentID;
    string bookID;
    string issueDate;
    string dueDate;
    string returnDate;

public:
    LibraryTransaction();

    LibraryTransaction(string student, string book,
                        string issue, string due,
                        string returned = "");

    string getStudentID() const;
    string getBookID() const;
    string getIssueDate() const;
    string getDueDate() const;
    string getReturnDate() const;

    void setReturnDate(string date);

    bool isValid() const;
    bool isReturned() const;
    void display() const;
};

#endif