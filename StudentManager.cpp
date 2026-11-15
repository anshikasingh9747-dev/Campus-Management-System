#include "../include/StudentManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdio>

using namespace std;

// Constructor
StudentManager::StudentManager(const string& file) {
fileName = file;
loadStudents();
}

// Load students from file
bool StudentManager::loadStudents() {

ifstream file(fileName);

if (!file.is_open()) {
    return true;
}

vector<Student> loadedStudents;
string line;

while (getline(file, line)) {

    if (line.empty())
        continue;

    stringstream ss(line);

    string id, name, department, email;
    string semesterText, yearText;

    if (!getline(ss, id, '|') ||
        !getline(ss, name, '|') ||
        !getline(ss, department, '|') ||
        !getline(ss, semesterText, '|') ||
        !getline(ss, email, '|') ||
        !getline(ss, yearText)) {
        continue;
    }

    try {

        size_t pos1, pos2;

        int semester = stoi(semesterText, &pos1);
        int year = stoi(yearText, &pos2);

        if (pos1 != semesterText.size() ||
            pos2 != yearText.size()) {
            continue;
        }

        Student student(
            id, name, department,
            semester, email, year
        );

        if (!student.isValid())
            continue;

        bool duplicate = false;

        for (const Student& existing : loadedStudents) {
            if (existing.getStudentID() == id) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate)
            loadedStudents.push_back(student);

    }
    catch (...) {
        continue;
    }
}

if (file.bad())
    return false;

students = loadedStudents;

return true;

}

// Save students to file
bool StudentManager::saveStudents() const {

string tempFile = fileName + ".tmp";
string backupFile = fileName + ".bak";

ofstream file(tempFile);

if (!file.is_open())
    return false;

for (const Student& student : students) {

    file << student.getStudentID() << "|"
         << student.getFullName() << "|"
         << student.getDepartment() << "|"
         << student.getSemester() << "|"
         << student.getEmail() << "|"
         << student.getEnrollmentYear() << "\n";
}

file.close();

if (!file)
    return false;

// Keep existing file as backup
bool backupCreated = false;

ifstream existing(fileName);

if (existing.good()) {
    existing.close();

    remove(backupFile.c_str());

    if (rename(fileName.c_str(), backupFile.c_str()) != 0) {
        remove(tempFile.c_str());
        return false;
    }

    backupCreated = true;
}

// Replace old file with temporary file
if (rename(tempFile.c_str(), fileName.c_str()) != 0) {

    if (backupCreated)
        rename(backupFile.c_str(), fileName.c_str());

    remove(tempFile.c_str());
    return false;
}

if (backupCreated)
    remove(backupFile.c_str());

return true;

}

// Add student
bool StudentManager::addStudent(const Student& student) {

if (!student.isValid())
    return false;

for (const Student& existing : students) {

    if (existing.getStudentID() == student.getStudentID())
        return false;
}

students.push_back(student);

if (!saveStudents()) {
    students.pop_back();
    return false;
}

return true;

}

// Search student by ID
bool StudentManager::searchStudentByID(
const string& id,
Student& result
) const {

for (const Student& student : students) {

    if (student.getStudentID() == id) {
        result = student;
        return true;
    }
}

return false;

}

// Search student by name
void StudentManager::searchStudentByName(
const string& name
) const {

string searchName = name;

transform(
    searchName.begin(),
    searchName.end(),
    searchName.begin(),
    ::tolower
);

bool found = false;

for (const Student& student : students) {

    string studentName = student.getFullName();

    transform(
        studentName.begin(),
        studentName.end(),
        studentName.begin(),
        ::tolower
    );

    if (studentName.find(searchName) != string::npos) {
        student.display();
        found = true;
    }
}

if (!found)
    cout << "\nStudent not found.\n";

}

// Update student
bool StudentManager::updateStudent(
const string& id,
const string& name,
const string& department,
int semester,
const string& email,
int year
) {

for (size_t i = 0; i < students.size(); i++) {

    if (students[i].getStudentID() == id) {

        Student updatedStudent(
            id, name, department,
            semester, email, year
        );

        if (!updatedStudent.isValid())
            return false;

        Student oldStudent = students[i];

        students[i] = updatedStudent;

        if (!saveStudents()) {
            students[i] = oldStudent;
            return false;
        }

        return true;
    }
}

return false;

}

// Remove student
bool StudentManager::removeStudent(const string& id) {

for (size_t i = 0; i < students.size(); i++) {

    if (students[i].getStudentID() == id) {

        Student oldStudent = students[i];

        students.erase(students.begin() + i);

        if (!saveStudents()) {
            students.insert(
                students.begin() + i,
                oldStudent
            );

            return false;
        }

        return true;
    }
}

return false;

}

// Display all students
void StudentManager::displayAllStudents() const {

if (students.empty()) {
    cout << "\nNo student records available.\n";
    return;
}

cout << "\n========== STUDENT RECORDS ==========\n";

for (const Student& student : students) {
    student.display();
}

}

// Return all students
vector<Student> StudentManager::getAllStudents() const {

return students;

}

// Get student count
int StudentManager::getStudentCount() const {

return static_cast<int>(students.size());

}