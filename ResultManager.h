#ifndef RESULT_MANAGER_H
#define RESULT_MANAGER_H

#include <string>
#include <vector>

using namespace std;

class CourseManager;

// Stores one student's result in one course
struct ResultRecord {
string studentID;
string courseID;
float marks;
string grade;
};

class ResultManager {
private:
vector<ResultRecord> results;
string fileName;

string calculateGrade(float marks) const;

void mergeSort(vector<ResultRecord>& records,
               int left, int right) const;

void merge(vector<ResultRecord>& records,
           int left, int middle, int right) const;

public:
explicit ResultManager(
const string& file = "data/results.txt"
);

bool loadResults();
bool saveResults() const;

bool addOrUpdateResult(
    const string& studentID,
    const string& courseID,
    float marks,
    const CourseManager& courseManager
);

void displayMarksheet(const string& studentID) const;

void displayCourseResults(const string& courseID) const;

void displayTopPerformers(int limit) const;

int getResultCount() const;

};

#endif