#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    string bookID;
    string title;
    string author;
    string category;
    int availableCopies;

public:
    Book();

    Book(string id, string bookTitle, string bookAuthor,
         string bookCategory, int copies);

    string getBookID() const;
    string getTitle() const;
    string getAuthor() const;
    string getCategory() const;
    int getAvailableCopies() const;

    bool issueCopy();
    bool returnCopy();

    bool isValid() const;
    void display() const;
};

#endif