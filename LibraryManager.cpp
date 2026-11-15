#include "../include/LibraryManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <cctype>

using namespace std;

// Safely save data using temporary and backup files
static bool saveLibraryFile(
const string& fileName,
const vector<string>& lines
) {
string tempFile = fileName + ".tmp";
string backupFile = fileName + ".bak";

ofstream outFile(tempFile, ios::trunc);

if (!outFile.is_open()) {
    return false;
}

for (const string& line : lines) {
    outFile << line << '\n';

    if (!outFile) {
        outFile.close();
        remove(tempFile.c_str());
        return false;
    }
}

outFile.close();

if (!outFile) {
    remove(tempFile.c_str());
    return false;
}

ifstream checkFile(fileName);
bool originalExists = checkFile.good();
checkFile.close();

if (originalExists) {
    remove(backupFile.c_str());

    if (rename(fileName.c_str(), backupFile.c_str()) != 0) {
        remove(tempFile.c_str());
        return false;
    }
}

if (rename(tempFile.c_str(), fileName.c_str()) != 0) {
    if (originalExists) {
        rename(backupFile.c_str(), fileName.c_str());
    }

    remove(tempFile.c_str());
    return false;
}

if (originalExists) {
    remove(backupFile.c_str());
}

return true;

}

// Constructor
LibraryManager::LibraryManager(
const string& bookFile,
const string& loanFile
) {
bookFileName = bookFile;
loanFileName = loanFile;

loadBooks();
loadLoans();

}

// Check whether student ID exists in students.txt
bool LibraryManager::isStudentValid(
const string& studentID
) const {
if (studentID.empty()) {
return false;
}

ifstream inFile("data/students.txt");

if (!inFile.is_open()) {
    return false;
}

string line;

while (getline(inFile, line)) {
    stringstream ss(line);
    string storedID;

    if (getline(ss, storedID, '|') &&
        storedID == studentID) {
        return true;
    }
}

return false;

}

// Find book index by ID
int LibraryManager::findBookIndex(
const string& bookID
) const {
for (size_t i = 0; i < books.size(); i++) {
if (books[i].getBookID() == bookID) {
return static_cast<int>(i);
}
}

return -1;

}

// Load books
bool LibraryManager::loadBooks() {
ifstream inFile(bookFileName);

if (!inFile.is_open()) {
    return false;
}

vector<Book> loadedBooks;
string line;

while (getline(inFile, line)) {
    if (line.empty()) {
        continue;
    }

    stringstream ss(line);

    string id, title, author, category, copiesText, extra;

    if (!getline(ss, id, '|') ||
        !getline(ss, title, '|') ||
        !getline(ss, author, '|') ||
        !getline(ss, category, '|') ||
        !getline(ss, copiesText, '|') ||
        getline(ss, extra)) {
        continue;
    }

    try {
        size_t pos = 0;
        int copies = stoi(copiesText, &pos);

        if (pos != copiesText.size()) {
            continue;
        }

        Book book(id, title, author, category, copies);

        if (!book.isValid()) {
            continue;
        }

        bool duplicate = false;

        for (const auto& existing : loadedBooks) {
            if (existing.getBookID() == id) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            loadedBooks.push_back(book);
        }
    }
    catch (...) {
        continue;
    }
}

inFile.close();
books = loadedBooks;

return true;

}

// Save books
bool LibraryManager::saveBooks() const {
vector<string> lines;

for (const auto& book : books) {
    lines.push_back(
        book.getBookID() + "|" +
        book.getTitle() + "|" +
        book.getAuthor() + "|" +
        book.getCategory() + "|" +
        to_string(book.getAvailableCopies())
    );
}

return saveLibraryFile(bookFileName, lines);

}

// Load loan transactions
bool LibraryManager::loadLoans() {
ifstream inFile(loanFileName);

if (!inFile.is_open()) {
    return false;
}

vector<LibraryTransaction> loadedTransactions;
string line;

while (getline(inFile, line)) {
    if (line.empty()) {
        continue;
    }

    stringstream ss(line);

    string studentID, bookID;
    string issueDate, dueDate, returnDate, extra;

    if (!getline(ss, studentID, '|') ||
        !getline(ss, bookID, '|') ||
        !getline(ss, issueDate, '|') ||
        !getline(ss, dueDate, '|') ||
        !getline(ss, returnDate, '|') ||
        getline(ss, extra)) {
        continue;
    }

    LibraryTransaction transaction(
        studentID, bookID, issueDate, dueDate, returnDate
    );

    if (!transaction.isValid()) {
        continue;
    }

    bool bookExists = findBookIndex(bookID) != -1;

    if (!bookExists) {
        continue;
    }

    loadedTransactions.push_back(transaction);
}

inFile.close();

transactions = loadedTransactions;

// Recalculate available copies from active loans
for (auto& book : books) {
    int activeLoans = 0;

    for (const auto& transaction : transactions) {
        if (transaction.getBookID() == book.getBookID() &&
            !transaction.isReturned()) {
            activeLoans++;
        }
    }

    // The stored count is already the available count.
    // No extra decrement is performed here.
    (void)activeLoans;
}

return true;

}

// Save loan transactions
bool LibraryManager::saveLoans() const {
vector<string> lines;

for (const auto& transaction : transactions) {
    lines.push_back(
        transaction.getStudentID() + "|" +
        transaction.getBookID() + "|" +
        transaction.getIssueDate() + "|" +
        transaction.getDueDate() + "|" +
        transaction.getReturnDate()
    );
}

return saveLibraryFile(loanFileName, lines);

}

// Add book
bool LibraryManager::addBook(const Book& book) {
if (!book.isValid() ||
findBookIndex(book.getBookID()) != -1) {
return false;
}

books.push_back(book);

if (!saveBooks()) {
    books.pop_back();
    return false;
}

return true;

}

// Update book details
bool LibraryManager::updateBook(
const string& bookID,
const string& title,
const string& author,
const string& category,
int availableCopies
) {
int index = findBookIndex(bookID);

if (index == -1 ||
    title.empty() ||
    author.empty() ||
    category.empty() ||
    availableCopies < 0) {
    return false;
}

int activeLoans = 0;

for (const auto& transaction : transactions) {
    if (transaction.getBookID() == bookID &&
        !transaction.isReturned()) {
        activeLoans++;
    }
}

if (availableCopies < 0) {
    return false;
}

Book oldBook = books[index];

Book updatedBook(
    bookID, title, author, category, availableCopies
);

if (!updatedBook.isValid()) {
    return false;
}

books[index] = updatedBook;

if (!saveBooks()) {
    books[index] = oldBook;
    return false;
}

return true;

}

// Search book by ID
bool LibraryManager::searchBookByID(
const string& bookID,
Book& result
) const {
int index = findBookIndex(bookID);

if (index == -1) {
    return false;
}

result = books[index];
return true;

}

// Search book by title
void LibraryManager::searchBookByTitle(
const string& title
) const {
string target = title;

transform(
    target.begin(), target.end(),
    target.begin(),
    [](unsigned char c) {
        return static_cast<char>(tolower(c));
    }
);

bool found = false;

for (const auto& book : books) {
    string currentTitle = book.getTitle();

    transform(
        currentTitle.begin(), currentTitle.end(),
        currentTitle.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        }
    );

    if (currentTitle.find(target) != string::npos) {
        book.display();
        found = true;
    }
}

if (!found) {
    cout << "\nBook not found.\n";
}

}

// Display all books
void LibraryManager::displayAllBooks() const {
if (books.empty()) {
cout << "\nNo books available.\n";
return;
}

cout << "\n========== LIBRARY BOOKS ==========\n";

for (const auto& book : books) {
    book.display();
    cout << "----------------------------------\n";
}

}

// Issue book
bool LibraryManager::issueBook(
const string& studentID,
const string& bookID,
const string& issueDate,
const string& dueDate
) {
if (!isStudentValid(studentID) ||
issueDate.empty() ||
dueDate.empty() ||
dueDate < issueDate) {
return false;
}

int bookIndex = findBookIndex(bookID);

if (bookIndex == -1 ||
    books[bookIndex].getAvailableCopies() <= 0) {
    return false;
}

for (const auto& transaction : transactions) {
    if (transaction.getStudentID() == studentID &&
        transaction.getBookID() == bookID &&
        !transaction.isReturned()) {
        return false;
    }
}

LibraryTransaction newTransaction(
    studentID, bookID, issueDate, dueDate
);

if (!newTransaction.isValid()) {
    return false;
}

Book oldBook = books[bookIndex];

if (!books[bookIndex].issueCopy()) {
    return false;
}

transactions.push_back(newTransaction);

if (!saveBooks()) {
    transactions.pop_back();
    books[bookIndex] = oldBook;
    return false;
}

if (!saveLoans()) {
    transactions.pop_back();
    books[bookIndex] = oldBook;
    saveBooks();
    return false;
}

return true;

}

// Return book
bool LibraryManager::returnBook(
const string& studentID,
const string& bookID,
const string& returnDate
) {
if (studentID.empty() ||
bookID.empty() ||
returnDate.empty()) {
return false;
}

int bookIndex = findBookIndex(bookID);

if (bookIndex == -1) {
    return false;
}

for (auto& transaction : transactions) {
    if (transaction.getStudentID() == studentID &&
        transaction.getBookID() == bookID &&
        !transaction.isReturned()) {

        if (returnDate < transaction.getIssueDate()) {
            return false;
        }

        Book oldBook = books[bookIndex];
        string oldReturnDate = transaction.getReturnDate();

        if (!books[bookIndex].returnCopy()) {
            return false;
        }

        transaction.setReturnDate(returnDate);

        if (!saveBooks()) {
            books[bookIndex] = oldBook;
            transaction.setReturnDate(oldReturnDate);
            return false;
        }

        if (!saveLoans()) {
            books[bookIndex] = oldBook;
            transaction.setReturnDate(oldReturnDate);
            saveBooks();
            return false;
        }

        return true;
    }
}

return false;

}

// Add student to waiting list
bool LibraryManager::addToWaitingList(
const string& studentID,
const string& bookID
) {
if (!isStudentValid(studentID) ||
findBookIndex(bookID) == -1) {
return false;
}

queue<string>& waitingQueue = waitingLists[bookID];

queue<string> temp = waitingQueue;

while (!temp.empty()) {
    if (temp.front() == studentID) {
        return false;
    }

    temp.pop();
}

waitingQueue.push(studentID);

return true;

}

// Display waiting list
void LibraryManager::displayWaitingList(
const string& bookID
) const {
auto it = waitingLists.find(bookID);

if (it == waitingLists.end() || it->second.empty()) {
    cout << "\nNo waiting list for this book.\n";
    return;
}

queue<string> temp = it->second;

cout << "\nWaiting List for Book: " << bookID << "\n";

int position = 1;

while (!temp.empty()) {
    cout << position++ << ". "
         << temp.front() << '\n';

    temp.pop();
}

}

// Display current loans
void LibraryManager::displayCurrentLoans() const {
bool found = false;

cout << "\n========== CURRENT LOANS ==========\n";

for (const auto& transaction : transactions) {
    if (!transaction.isReturned()) {
        transaction.display();
        found = true;
    }
}

if (!found) {
    cout << "No active loans found.\n";
}

}

// Display overdue loans
void LibraryManager::displayOverdueLoans(
const string& currentDate
) const {
if (currentDate.empty()) {
cout << "\nInvalid current date.\n";
return;
}

bool found = false;

cout << "\n========== OVERDUE LOANS ==========\n";

for (const auto& transaction : transactions) {
    if (!transaction.isReturned() &&
        transaction.getDueDate() < currentDate) {
        transaction.display();
        found = true;
    }
}

if (!found) {
    cout << "No overdue loans found.\n";
}

}

// Display available books
void LibraryManager::displayAvailableBooks() const {
bool found = false;

cout << "\n========== AVAILABLE BOOKS ==========\n";

for (const auto& book : books) {
    if (book.getAvailableCopies() > 0) {
        book.display();
        found = true;
    }
}

if (!found) {
    cout << "No books are currently available.\n";
}

}

// Get book count
int LibraryManager::getBookCount() const {
return static_cast<int>(books.size());
}

// Get active loan count
int LibraryManager::getActiveLoanCount() const {
int count = 0;

for (const auto& transaction : transactions) {
    if (!transaction.isReturned()) {
        count++;
    }
}

return count;

}