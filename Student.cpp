#include "../include/Student.h"
#include <iostream>
#include <cctype>

using namespace std;

// Default constructor
Student::Student() {
    studentID = "";
    fullName = "";
    department = "";
    semester = 0;
    email = "";
    enrollmentYear = 0;
}

// Parameterized constructor
Student::Student(string id, string name, string dept,
                 int sem, string mail, int year) {
    studentID = id;
    fullName = name;
    department = dept;
    semester = sem;
    email = mail;
    enrollmentYear = year;
}

// Getter functions
string Student::getStudentID() const {
    return studentID;
}

string Student::getFullName() const {
    return fullName;
}

string Student::getDepartment() const {
    return department;
}

int Student::getSemester() const {
    return semester;
}

string Student::getEmail() const {
    return email;
}

int Student::getEnrollmentYear() const {
    return enrollmentYear;
}

// Setter functions
void Student::setFullName(string name) {
    if (!name.empty())
        fullName = name;
}

void Student::setDepartment(string dept) {
    if (!dept.empty())
        department = dept;
}

void Student::setSemester(int sem) {
    if (sem >= 1 && sem <= 8)
        semester = sem;
}

void Student::setEmail(string mail) {
    size_t at = mail.find('@');
    size_t dot = mail.find('.', at);

    if (at != string::npos && dot != string::npos)
        email = mail;
}

void Student::setEnrollmentYear(int year) {
    if (year >= 2000 && year <= 2100)
        enrollmentYear = year;
}

// Validation function
bool Student::isValid() const {
    size_t at = email.find('@');
    size_t dot = email.find('.', at);

    return !studentID.empty() &&
           !fullName.empty() &&
           !department.empty() &&
           semester >= 1 && semester <= 8 &&
           at != string::npos &&
           dot != string::npos &&
           dot > at + 1 &&
           dot < email.length() - 1 &&
           enrollmentYear >= 2000 &&
           enrollmentYear <= 2100;
}

// Display student details
void Student::display() const {
    cout << "\nStudent ID: " << studentID;
    cout << "\nFull Name: " << fullName;
    cout << "\nDepartment: " << department;
    cout << "\nSemester: " << semester;
    cout << "\nEmail: " << email;
    cout << "\nEnrollment Year: " << enrollmentYear << endl;
}