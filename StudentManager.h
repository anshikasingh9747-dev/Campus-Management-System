#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Student.h"

#include <vector>
#include <string>

using namespace std;

class StudentManager {
private:
vector<Student> students;
string fileName;

public:
explicit StudentManager(
const string& file = "data/students.txt"
);

// File handling
bool loadStudents();
bool saveStudents() const;

// Student management
bool addStudent(const Student& student);

bool searchStudentByID(
    const string& id,
    Student& result
) const;

void searchStudentByName(
    const string& name
) const;

bool updateStudent(
    const string& id,
    const string& name,
    const string& department,
    int semester,
    const string& email,
    int year
);

bool removeStudent(const string& id);

// Display students
void displayAllStudents() const;

// Return all students for course enrollment
vector<Student> getAllStudents() const;

// Student count
int getStudentCount() const;

};

#endif