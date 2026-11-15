#include "../include/ResultManager.h"
#include "../include/CourseManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cstdio>
#include <limits>

using namespace std;

// Constructor
ResultManager::ResultManager(const string& file)
: fileName(file) {
loadResults();
}

// Calculate grade
string ResultManager::calculateGrade(float marks) const {
if (marks >= 90) return "A+";
if (marks >= 80) return "A";
if (marks >= 70) return "B";
if (marks >= 60) return "C";
if (marks >= 50) return "D";
return "F";
}

// Load results from file
bool ResultManager::loadResults() {
ifstream inFile(fileName);

if (!inFile.is_open()) {
    return false;
}

vector<ResultRecord> loadedResults;
string line;

while (getline(inFile, line)) {
    if (line.empty()) continue;

    stringstream ss(line);
    ResultRecord record;
    string marksText;
    string extra;

    if (!getline(ss, record.studentID, '|') ||
        !getline(ss, record.courseID, '|') ||
        !getline(ss, marksText, '|') ||
        !getline(ss, record.grade, '|') ||
        getline(ss, extra)) {
        continue;
    }

    try {
        size_t pos = 0;
        record.marks = stof(marksText, &pos);

        if (pos != marksText.size() ||
            record.studentID.empty() ||
            record.courseID.empty() ||
            record.marks < 0 ||
            record.marks > 100 ||
            record.grade != calculateGrade(record.marks)) {
            continue;
        }
    }
    catch (...) {
        continue;
    }

    bool duplicate = false;

    for (const auto& existing : loadedResults) {
        if (existing.studentID == record.studentID &&
            existing.courseID == record.courseID) {
            duplicate = true;
            break;
        }
    }

    if (!duplicate) {
        loadedResults.push_back(record);
    }
}

inFile.close();
results = loadedResults;

return true;

}

// Save results safely using a temporary file
bool ResultManager::saveResults() const {
string tempFile = fileName + ".tmp";
string backupFile = fileName + ".bak";

ofstream outFile(tempFile, ios::trunc);

if (!outFile.is_open()) {
    return false;
}

outFile << fixed << setprecision(2);

for (const auto& record : results) {
    outFile << record.studentID << "|"
            << record.courseID << "|"
            << record.marks << "|"
            << record.grade << "\n";

    if (!outFile) {
        outFile.close();
        remove(tempFile.c_str());
        return false;
    }
}

outFile.close();

if (!outFile) {
    remove(tempFile.c_str());
    return false;
}

bool hadOriginal = false;

ifstream checkFile(fileName);
if (checkFile.good()) {
    hadOriginal = true;
}
checkFile.close();

if (hadOriginal) {
    remove(backupFile.c_str());

    if (rename(fileName.c_str(), backupFile.c_str()) != 0) {
        remove(tempFile.c_str());
        return false;
    }
}

if (rename(tempFile.c_str(), fileName.c_str()) != 0) {
    if (hadOriginal) {
        rename(backupFile.c_str(), fileName.c_str());
    }

    remove(tempFile.c_str());
    return false;
}

if (hadOriginal) {
    remove(backupFile.c_str());
}

return true;

}

// Add or update a student's result
bool ResultManager::addOrUpdateResult(
const string& studentID,
const string& courseID,
float marks,
const CourseManager& courseManager) {

if (studentID.empty() ||
    courseID.empty() ||
    marks < 0 ||
    marks > 100 ||
    !courseManager.isStudentEnrolled(courseID, studentID)) {
    return false;
}

ResultRecord newRecord;
newRecord.studentID = studentID;
newRecord.courseID = courseID;
newRecord.marks = marks;
newRecord.grade = calculateGrade(marks);

for (auto& record : results) {
    if (record.studentID == studentID &&
        record.courseID == courseID) {

        ResultRecord oldRecord = record;
        record = newRecord;

        if (!saveResults()) {
            record = oldRecord;
            return false;
        }

        return true;
    }
}

results.push_back(newRecord);

if (!saveResults()) {
    results.pop_back();
    return false;
}

return true;

}

// Merge two sorted parts
void ResultManager::merge(
vector<ResultRecord>& records,
int left, int middle, int right) const {

vector<ResultRecord> leftPart;
vector<ResultRecord> rightPart;

for (int i = left; i <= middle; i++) {
    leftPart.push_back(records[i]);
}

for (int i = middle + 1; i <= right; i++) {
    rightPart.push_back(records[i]);
}

int i = 0;
int j = 0;
int k = left;

while (i < static_cast<int>(leftPart.size()) &&
       j < static_cast<int>(rightPart.size())) {

    if (leftPart[i].marks >= rightPart[j].marks) {
        records[k++] = leftPart[i++];
    } else {
        records[k++] = rightPart[j++];
    }
}

while (i < static_cast<int>(leftPart.size())) {
    records[k++] = leftPart[i++];
}

while (j < static_cast<int>(rightPart.size())) {
    records[k++] = rightPart[j++];
}

}

// Merge Sort: descending order of marks
void ResultManager::mergeSort(
vector<ResultRecord>& records,
int left, int right) const {

if (left >= right) return;

int middle = left + (right - left) / 2;

mergeSort(records, left, middle);
mergeSort(records, middle + 1, right);

merge(records, left, middle, right);

}

// Display individual marksheet
void ResultManager::displayMarksheet(
const string& studentID) const {

bool found = false;
float total = 0;
int count = 0;

cout << "\n========== STUDENT MARKSHEET ==========\n";
cout << "Student ID: " << studentID << "\n";

cout << left << setw(18) << "Course ID"
     << setw(15) << "Marks"
     << "Grade\n";

cout << "---------------------------------------\n";

for (const auto& record : results) {
    if (record.studentID == studentID) {
        cout << left << setw(18) << record.courseID
             << setw(15) << fixed << setprecision(2)
             << record.marks
             << record.grade << "\n";

        total += record.marks;
        count++;
        found = true;
    }
}

if (!found) {
    cout << "No results found for this student.\n";
    return;
}

cout << "---------------------------------------\n";
cout << "Total Marks: " << total << "\n";
cout << "Average Marks: " << total / count << "\n";
cout << "=======================================\n";

}

// Display course-wise results
void ResultManager::displayCourseResults(
const string& courseID) const {

vector<ResultRecord> courseResults;

for (const auto& record : results) {
    if (record.courseID == courseID) {
        courseResults.push_back(record);
    }
}

if (courseResults.empty()) {
    cout << "\nNo results found for this course.\n";
    return;
}

mergeSort(courseResults, 0,
          static_cast<int>(courseResults.size()) - 1);

cout << "\n========== COURSE RESULTS ==========\n";
cout << "Course ID: " << courseID << "\n\n";

cout << left << setw(18) << "Student ID"
     << setw(15) << "Marks"
     << "Grade\n";

cout << "-----------------------------------\n";

int rank = 0;
float previousMarks = -1;

for (size_t i = 0; i < courseResults.size(); i++) {

    if (i == 0 ||
        courseResults[i].marks != previousMarks) {
        rank = static_cast<int>(i) + 1;
    }

    cout << left << setw(18)
         << courseResults[i].studentID
         << setw(15) << fixed << setprecision(2)
         << courseResults[i].marks
         << courseResults[i].grade
         << "  Rank: " << rank << "\n";

    previousMarks = courseResults[i].marks;
}

cout << "===================================\n";

}

// Display top performers
void ResultManager::displayTopPerformers(int limit) const {

if (limit <= 0 || results.empty()) {
    cout << "\nNo top performers available.\n";
    return;
}

vector<ResultRecord> sortedResults = results;

mergeSort(sortedResults, 0,
          static_cast<int>(sortedResults.size()) - 1);

cout << "\n========== TOP PERFORMERS ==========\n";

int displayed = 0;

for (const auto& record : sortedResults) {
    if (displayed >= limit) break;

    cout << "Student ID: " << record.studentID
         << " | Course ID: " << record.courseID
         << " | Marks: " << fixed << setprecision(2)
         << record.marks
         << " | Grade: " << record.grade << "\n";

    displayed++;
}

cout << "===================================\n";

}

// Get total number of result records
int ResultManager::getResultCount() const {
return static_cast<int>(results.size());
}