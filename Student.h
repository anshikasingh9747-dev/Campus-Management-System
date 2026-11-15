#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student {
private:
    string studentID;
    string fullName;
    string department;
    int semester;
    string email;
    int enrollmentYear;

public:
    Student();

    Student(string id, string name, string dept,
            int sem, string mail, int year);

    string getStudentID() const;
    string getFullName() const;
    string getDepartment() const;
    int getSemester() const;
    string getEmail() const;
    int getEnrollmentYear() const;

    void setFullName(string name);
    void setDepartment(string dept);
    void setSemester(int sem);
    void setEmail(string mail);
    void setEnrollmentYear(int year);

    bool isValid() const;
    void display() const;
};

#endif