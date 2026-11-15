#include "../include/CourseManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <iterator>

using namespace std;

// Constructor
CourseManager::CourseManager(
const string& courseFile,
const string& enrollmentFile
) : fileName(courseFile),
enrollmentFileName(enrollmentFile) {

loadCourses();
loadEnrollments();

}

// Load courses
bool CourseManager::loadCourses() {
courses.clear();

ifstream inFile(fileName);

if (!inFile.is_open()) {
    return true;
}

string line;

while (getline(inFile, line)) {
    if (line.empty()) continue;

    stringstream ss(line);

    string id, name, dept, semesterText, capacityText;

    if (!getline(ss, id, '|') ||
        !getline(ss, name, '|') ||
        !getline(ss, dept, '|') ||
        !getline(ss, semesterText, '|') ||
        !getline(ss, capacityText)) {
        continue;
    }

    try {
        size_t pos1, pos2;

        int semester = stoi(semesterText, &pos1);
        int capacity = stoi(capacityText, &pos2);

        if (pos1 != semesterText.size() ||
            pos2 != capacityText.size()) {
            continue;
        }

        Course course(id, name, dept, semester, capacity);

        bool duplicate = false;

        for (const Course& existing : courses) {
            if (existing.getCourseID() == id) {
                duplicate = true;
                break;
            }
        }

        if (course.isValid() && !duplicate) {
            courses.push_back(course);
        }
    }
    catch (...) {
        continue;
    }
}

bool success = !inFile.bad();
inFile.close();

return success;

}

// Save courses
bool CourseManager::saveCourses() const {
string tempFile = fileName + ".tmp";
string backupFile = fileName + ".bak";

ofstream outFile(tempFile);

if (!outFile.is_open()) return false;

for (const Course& course : courses) {
    outFile << course.getCourseID() << "|"
            << course.getCourseName() << "|"
            << course.getDepartment() << "|"
            << course.getSemester() << "|"
            << course.getMaxCapacity() << "\n";
}

outFile.close();

if (!outFile) {
    remove(tempFile.c_str());
    return false;
}

ifstream checkFile(fileName);

if (checkFile.good()) {
    checkFile.close();

    remove(backupFile.c_str());

    if (rename(fileName.c_str(), backupFile.c_str()) != 0) {
        remove(tempFile.c_str());
        return false;
    }

    if (rename(tempFile.c_str(), fileName.c_str()) != 0) {
        rename(backupFile.c_str(), fileName.c_str());
        remove(tempFile.c_str());
        return false;
    }

    remove(backupFile.c_str());
}
else {
    checkFile.close();

    if (rename(tempFile.c_str(), fileName.c_str()) != 0) {
        remove(tempFile.c_str());
        return false;
    }
}

return true;

}

// Load enrollments
bool CourseManager::loadEnrollments() {
enrollments.clear();

ifstream inFile(enrollmentFileName);

if (!inFile.is_open()) return true;

string line;

while (getline(inFile, line)) {
    if (line.empty()) continue;

    stringstream ss(line);

    string courseID, studentID;

    if (!getline(ss, courseID, '|') ||
        !getline(ss, studentID)) {
        continue;
    }

    Course* selectedCourse = nullptr;

    for (Course& course : courses) {
        if (course.getCourseID() == courseID) {
            selectedCourse = &course;
            break;
        }
    }

    if (selectedCourse == nullptr || studentID.empty()) {
        continue;
    }

    bool duplicate = false;

    for (const auto& enrollment : enrollments) {
        if (enrollment.first == courseID &&
            enrollment.second == studentID) {
            duplicate = true;
            break;
        }
    }

    if (!duplicate && selectedCourse->addStudent(studentID)) {
        enrollments.push_back({courseID, studentID});
    }
}

bool success = !inFile.bad();
inFile.close();

return success;

}

// Save enrollments
bool CourseManager::saveEnrollments() const {
string tempFile = enrollmentFileName + ".tmp";
string backupFile = enrollmentFileName + ".bak";

ofstream outFile(tempFile);

if (!outFile.is_open()) return false;

for (const auto& enrollment : enrollments) {
    outFile << enrollment.first << "|"
            << enrollment.second << "\n";
}

outFile.close();

if (!outFile) {
    remove(tempFile.c_str());
    return false;
}

ifstream checkFile(enrollmentFileName);

if (checkFile.good()) {
    checkFile.close();

    remove(backupFile.c_str());

    if (rename(enrollmentFileName.c_str(),
               backupFile.c_str()) != 0) {
        remove(tempFile.c_str());
        return false;
    }

    if (rename(tempFile.c_str(),
               enrollmentFileName.c_str()) != 0) {
        rename(backupFile.c_str(),
               enrollmentFileName.c_str());
        remove(tempFile.c_str());
        return false;
    }

    remove(backupFile.c_str());
}
else {
    checkFile.close();

    if (rename(tempFile.c_str(),
               enrollmentFileName.c_str()) != 0) {
        remove(tempFile.c_str());
        return false;
    }
}

return true;

}

// Add course
bool CourseManager::addCourse(const Course& course) {
if (!course.isValid()) return false;

Course existing;

if (searchCourseByID(course.getCourseID(), existing)) {
    return false;
}

courses.push_back(course);

if (!saveCourses()) {
    courses.pop_back();
    return false;
}

return true;

}

// Search course by ID
bool CourseManager::searchCourseByID(
const string& id,
Course& result
) const {
for (const Course& course : courses) {
if (course.getCourseID() == id) {
result = course;
return true;
}
}

return false;

}

// Search course by name
void CourseManager::searchCourseByName(const string& name) const {
bool found = false;

for (const Course& course : courses) {
    if (course.getCourseName().find(name) != string::npos) {
        course.display();
        found = true;
    }
}

if (!found) {
    cout << "\nNo course found with this name.\n";
}

}

// Update course
bool CourseManager::updateCourse(
const string& id,
const string& name,
const string& department,
int semester,
int capacity
) {
for (Course& course : courses) {
if (course.getCourseID() == id) {
int enrolled = getEnrollmentCount(id);

        if (name.empty() || department.empty() ||
            semester < 1 || semester > 8 ||
            capacity < enrolled || capacity <= 0) {
            return false;
        }

        Course updated(id, name, department, semester, capacity);
        Course oldCourse = course;

        course = updated;

        for (const auto& enrollment : enrollments) {
            if (enrollment.first == id) {
                course.addStudent(enrollment.second);
            }
        }

        if (!saveCourses()) {
            course = oldCourse;
            return false;
        }

        return true;
    }
}

return false;

}

// Enroll student
bool CourseManager::enrollStudent(
const string& courseID,
const string& studentID,
const vector<Student>& students
) {
Course* selectedCourse = nullptr;

for (Course& course : courses) {
    if (course.getCourseID() == courseID) {
        selectedCourse = &course;
        break;
    }
}

if (selectedCourse == nullptr || studentID.empty()) {
    return false;
}

bool studentExists = false;

for (const Student& student : students) {
    if (student.getStudentID() == studentID) {
        studentExists = true;
        break;
    }
}

if (!studentExists) return false;

for (const auto& enrollment : enrollments) {
    if (enrollment.first == courseID &&
        enrollment.second == studentID) {
        return false;
    }
}

if (!selectedCourse->addStudent(studentID)) {
    return false;
}

enrollments.push_back({courseID, studentID});

if (!saveEnrollments()) {
    enrollments.pop_back();
    selectedCourse->removeStudent(studentID);
    return false;
}

return true;

}

// Remove enrollment
bool CourseManager::removeEnrollment(
const string& courseID,
const string& studentID
) {
auto it = find_if(
enrollments.begin(),
enrollments.end(),
[&](const pair<string, string>& enrollment) {
return enrollment.first == courseID &&
enrollment.second == studentID;
}
);

if (it == enrollments.end()) return false;

Course* selectedCourse = nullptr;

for (Course& course : courses) {
    if (course.getCourseID() == courseID) {
        selectedCourse = &course;
        break;
    }
}

if (selectedCourse == nullptr) return false;

selectedCourse->removeStudent(studentID);

auto position = distance(enrollments.begin(), it);

enrollments.erase(it);

if (!saveEnrollments()) {
    enrollments.insert(
        enrollments.begin() + position,
        {courseID, studentID}
    );

    selectedCourse->addStudent(studentID);
    return false;
}

return true;

}

// Check student enrollment
bool CourseManager::isStudentEnrolled(
const string& courseID,
const string& studentID
) const {
for (const auto& enrollment : enrollments) {
if (enrollment.first == courseID &&
enrollment.second == studentID) {
return true;
}
}

return false;

}

// Display all courses
void CourseManager::displayAllCourses() const {
if (courses.empty()) {
cout << "\nNo courses available.\n";
return;
}

for (const Course& course : courses) {
    course.display();
    cout << "--------------------------\n";
}

}

// Display students in a course
void CourseManager::displayStudentsInCourse(
const string& courseID
) const {
bool courseExists = false;
bool found = false;

for (const Course& course : courses) {
    if (course.getCourseID() == courseID) {
        courseExists = true;
        break;
    }
}

if (!courseExists) {
    cout << "\nCourse not found.\n";
    return;
}

cout << "\nEnrolled Student IDs:\n";

for (const auto& enrollment : enrollments) {
    if (enrollment.first == courseID) {
        cout << enrollment.second << endl;
        found = true;
    }
}

if (!found) {
    cout << "No students enrolled.\n";
}

}

// Display courses for a student
void CourseManager::displayCoursesForStudent(
const string& studentID
) const {
bool found = false;

cout << "\nCourses enrolled by student:\n";

for (const auto& enrollment : enrollments) {
    if (enrollment.second == studentID) {
        for (const Course& course : courses) {
            if (course.getCourseID() == enrollment.first) {
                course.display();
                found = true;
                break;
            }
        }
    }
}

if (!found) {
    cout << "No courses found for this student.\n";
}

}

// Course count
int CourseManager::getCourseCount() const {
return static_cast<int>(courses.size());
}

// Enrollment count
int CourseManager::getEnrollmentCount(
const string& courseID
) const {
int count = 0;

for (const auto& enrollment : enrollments) {
    if (enrollment.first == courseID) {
        count++;
    }
}

return count;

}