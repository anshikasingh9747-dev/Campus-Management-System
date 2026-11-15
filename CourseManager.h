#ifndef COURSE_MANAGER_H
#define COURSE_MANAGER_H

#include "Course.h"
#include "Student.h"

#include <vector>
#include <string>
#include <utility>

using namespace std;

class CourseManager {
private:
vector<Course> courses;

// Stores course ID and student ID relationships
vector<pair<string, string>> enrollments;

string fileName;
string enrollmentFileName;

public:
CourseManager(
const string& courseFile = "data/courses.txt",
const string& enrollmentFile = "data/enrollments.txt"
);

// File handling
bool loadCourses();
bool saveCourses() const;

bool loadEnrollments();
bool saveEnrollments() const;

// Course management
bool addCourse(const Course& course);

bool searchCourseByID(
    const string& id,
    Course& result
) const;

void searchCourseByName(
    const string& name
) const;

bool updateCourse(
    const string& id,
    const string& name,
    const string& department,
    int semester,
    int capacity
);

// Student enrollment management
bool enrollStudent(
    const string& courseID,
    const string& studentID,
    const vector<Student>& students
);

bool removeEnrollment(
    const string& courseID,
    const string& studentID
);

// Check whether a student is enrolled in a course
bool isStudentEnrolled(
    const string& courseID,
    const string& studentID
) const;

// Display functions
void displayAllCourses() const;

void displayStudentsInCourse(
    const string& courseID
) const;

void displayCoursesForStudent(
    const string& studentID
) const;

// Count functions
int getCourseCount() const;

int getEnrollmentCount(
    const string& courseID
) const;

};

#endif