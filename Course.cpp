#include "../include/Course.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Default constructor
Course::Course() {
    courseID = "";
    courseName = "";
    department = "";
    semester = 0;
    maxCapacity = 0;
}

// Parameterized constructor
Course::Course(string id, string name, string dept,
               int sem, int capacity) {
    courseID = id;
    courseName = name;
    department = dept;
    semester = sem;
    maxCapacity = capacity;
}

// Getter functions
string Course::getCourseID() const {
    return courseID;
}

string Course::getCourseName() const {
    return courseName;
}

string Course::getDepartment() const {
    return department;
}

int Course::getSemester() const {
    return semester;
}

int Course::getMaxCapacity() const {
    return maxCapacity;
}

int Course::getEnrolledCount() const {
    return static_cast<int>(enrolledStudentIDs.size());
}

// Check student enrollment
bool Course::hasStudent(string studentID) const {
    return find(enrolledStudentIDs.begin(),
                enrolledStudentIDs.end(),
                studentID) != enrolledStudentIDs.end();
}

// Add student
bool Course::addStudent(string studentID) {
    if (studentID.empty() ||
        hasStudent(studentID) ||
        getEnrolledCount() >= maxCapacity) {
        return false;
    }

    enrolledStudentIDs.push_back(studentID);
    return true;
}

// Remove student
bool Course::removeStudent(string studentID) {
    auto it = find(enrolledStudentIDs.begin(),
                   enrolledStudentIDs.end(),
                   studentID);

    if (it == enrolledStudentIDs.end()) {
        return false;
    }

    enrolledStudentIDs.erase(it);
    return true;
}

// Validate course details
bool Course::isValid() const {
    return !courseID.empty() &&
           !courseName.empty() &&
           !department.empty() &&
           semester >= 1 &&
           semester <= 8 &&
           maxCapacity > 0;
}

// Display course details
void Course::display() const {
    cout << "\nCourse ID: " << courseID;
    cout << "\nCourse Name: " << courseName;
    cout << "\nDepartment: " << department;
    cout << "\nSemester: " << semester;
    cout << "\nMaximum Capacity: " << maxCapacity;
    cout << "\nEnrolled Students: " << getEnrolledCount()
         << "/" << maxCapacity << endl;
}