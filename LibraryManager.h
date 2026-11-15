#ifndef LIBRARY_MANAGER_H
#define LIBRARY_MANAGER_H

#include "Book.h"
#include "LibraryTransaction.h"

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class LibraryManager {
private:
vector<Book> books;
vector<LibraryTransaction> transactions;

// Waiting list for each book
unordered_map<string, queue<string>> waitingLists;

string bookFileName;
string loanFileName;

bool isStudentValid(const string& studentID) const;
int findBookIndex(const string& bookID) const;

public:
LibraryManager(
const string& bookFile = "data/books.txt",
const string& loanFile = "data/loans.txt"
);

// File handling
bool loadBooks();
bool saveBooks() const;

bool loadLoans();
bool saveLoans() const;

// Book management
bool addBook(const Book& book);

bool updateBook(
    const string& bookID,
    const string& title,
    const string& author,
    const string& category,
    int availableCopies
);

bool searchBookByID(
    const string& bookID,
    Book& result
) const;

void searchBookByTitle(const string& title) const;

void displayAllBooks() const;

// Issue and return operations
bool issueBook(
    const string& studentID,
    const string& bookID,
    const string& issueDate,
    const string& dueDate
);

bool returnBook(
    const string& studentID,
    const string& bookID,
    const string& returnDate
);

// Waiting list
bool addToWaitingList(
    const string& studentID,
    const string& bookID
);

void displayWaitingList(const string& bookID) const;

// Reports
void displayCurrentLoans() const;
void displayOverdueLoans(const string& currentDate) const;
void displayAvailableBooks() const;

int getBookCount() const;
int getActiveLoanCount() const;

};

#endif