#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
using namespace std;

class Course {
private:
    string courseID;
    string courseName;
    string department;
    int semester;
    int maxCapacity;
    vector<string> enrolledStudentIDs;

public:
    Course();

    Course(string id, string name, string dept,
           int sem, int capacity);

    string getCourseID() const;
    string getCourseName() const;
    string getDepartment() const;
    int getSemester() const;
    int getMaxCapacity() const;
    int getEnrolledCount() const;

    bool hasStudent(string studentID) const;
    bool addStudent(string studentID);
    bool removeStudent(string studentID);

    bool isValid() const;
    void display() const;
};

#endif