#include "../include/ManagerHeaders.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Integer input
int readInt(const string& message) {
    string input;
    int value;
    char extra;

    while (true) {
        cout << message;
        getline(cin, input);

        stringstream ss(input);

        if (ss >> value && !(ss >> extra)) {
            return value;
        }

        cout << "Invalid input. Please enter a valid number.\n";
    }
}

// Float input
float readFloat(const string& message) {
    string input;
    float value;
    char extra;

    while (true) {
        cout << message;
        getline(cin, input);

        stringstream ss(input);

        if (ss >> value && !(ss >> extra)) {
            return value;
        }

        cout << "Invalid input. Please enter a valid number.\n";
    }
}

// String input
string readString(const string& message) {
    string value;

    cout << message;
    getline(cin, value);

    return value;
}

int main() {

    StudentManager studentManager;
    CourseManager courseManager;
    ResultManager resultManager;
    LibraryManager libraryManager;

    int choice = -1;

    do {
        cout << "\n====================================";
        cout << "\n       CAMPUS MANAGEMENT SYSTEM";
        cout << "\n====================================";

        cout << "\n\nSTUDENT MANAGEMENT";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Remove Student";

        cout << "\n\nCOURSE MANAGEMENT";
        cout << "\n6. Add Course";
        cout << "\n7. Display All Courses";
        cout << "\n8. Enroll Student";
        cout << "\n9. Display Courses of Student";

        cout << "\n\nACADEMIC RESULTS";
        cout << "\n10. Add / Update Result";
        cout << "\n11. Display Student Marksheet";
        cout << "\n12. Display Course Results";
        cout << "\n13. Display Top Performers";

        cout << "\n\nLIBRARY MANAGEMENT";
        cout << "\n14. Add Book";
        cout << "\n15. Display All Books";
        cout << "\n16. Issue Book";
        cout << "\n17. Return Book";
        cout << "\n18. Display Current Loans";
        cout << "\n19. Display Overdue Loans";
        cout << "\n20. Display Available Books";
        cout << "\n21. Add Student to Waiting List";
        cout << "\n22. Display Book Waiting List";

        cout << "\n\n0. Exit";

        cout << "\n====================================\n";

        choice = readInt("Enter your choice: ");

        switch (choice) {

        // Add Student
        case 1: {
            string id, name, dept, email;
            int semester, year;

            id = readString("Enter Student ID: ");
            name = readString("Enter Full Name: ");
            dept = readString("Enter Department: ");
            semester = readInt("Enter Semester: ");
            email = readString("Enter Email: ");
            year = readInt("Enter Enrollment Year: ");

            Student student(id, name, dept,
                            semester, email, year);

            if (studentManager.addStudent(student))
                cout << "\nStudent added successfully!\n";
            else
                cout << "\nUnable to add student. Check details or duplicate ID.\n";

            break;
        }

        // Display Students
        case 2:
            studentManager.displayAllStudents();
            break;

        // Search Student
        case 3: {
            string id;
            Student student;

            id = readString("Enter Student ID: ");

            if (studentManager.searchStudentByID(id, student))
                student.display();
            else
                cout << "\nStudent not found.\n";

            break;
        }

        // Update Student
        case 4: {
            string id, name, dept, email;
            int semester, year;

            id = readString("Enter Student ID to update: ");
            name = readString("Enter New Name: ");
            dept = readString("Enter New Department: ");
            semester = readInt("Enter New Semester: ");
            email = readString("Enter New Email: ");
            year = readInt("Enter New Enrollment Year: ");

            if (studentManager.updateStudent(
                    id, name, dept, semester, email, year))
                cout << "\nStudent updated successfully!\n";
            else
                cout << "\nUnable to update student.\n";

            break;
        }

        // Remove Student
        case 5: {
            string id = readString("Enter Student ID to remove: ");

            if (studentManager.removeStudent(id))
                cout << "\nStudent removed successfully!\n";
            else
                cout << "\nUnable to remove student.\n";

            break;
        }

        // Add Course
        case 6: {
            string id, name, dept;
            int semester, capacity;

            id = readString("Enter Course ID: ");
            name = readString("Enter Course Name: ");
            dept = readString("Enter Department: ");
            semester = readInt("Enter Semester: ");
            capacity = readInt("Enter Maximum Capacity: ");

            Course course(id, name, dept, semester, capacity);

            if (courseManager.addCourse(course))
                cout << "\nCourse added successfully!\n";
            else
                cout << "\nUnable to add course.\n";

            break;
        }

        // Display Courses
        case 7:
            courseManager.displayAllCourses();
            break;

        // Enroll Student
        case 8: {
            string courseID, studentID;

            courseID = readString("Enter Course ID: ");
            studentID = readString("Enter Student ID: ");

            if (courseManager.enrollStudent(
                    courseID, studentID,
                    studentManager.getAllStudents()))
                cout << "\nStudent enrolled successfully!\n";
            else
                cout << "\nEnrollment failed. Check student, course or capacity.\n";

            break;
        }

        // Display Courses of Student
        case 9: {
            string studentID;

            studentID = readString("Enter Student ID: ");

            courseManager.displayCoursesForStudent(studentID);
            break;
        }

        // Add or Update Result
        case 10: {
            string studentID, courseID;
            float marks;

            studentID = readString("Enter Student ID: ");
            courseID = readString("Enter Course ID: ");
            marks = readFloat("Enter Marks (0-100): ");

            if (resultManager.addOrUpdateResult(
                    studentID, courseID, marks, courseManager))
                cout << "\nResult saved successfully!\n";
            else
                cout << "\nUnable to save result. Check enrollment and marks.\n";

            break;
        }

        // Student Marksheet
        case 11: {
            string studentID;

            studentID = readString("Enter Student ID: ");

            resultManager.displayMarksheet(studentID);
            break;
        }

        // Course Results
        case 12: {
            string courseID;

            courseID = readString("Enter Course ID: ");

            resultManager.displayCourseResults(courseID);
            break;
        }

        // Top Performers
        case 13: {
            int limit = readInt("Enter number of top performers: ");

            if (limit > 0)
                resultManager.displayTopPerformers(limit);
            else
                cout << "\nEnter a positive number.\n";

            break;
        }

        // Add Book
        case 14: {
            string id, title, author, category;
            int copies;

            id = readString("Enter Book ID: ");
            title = readString("Enter Book Title: ");
            author = readString("Enter Author Name: ");
            category = readString("Enter Category: ");
            copies = readInt("Enter Available Copies: ");

            Book book(id, title, author, category, copies);

            if (libraryManager.addBook(book))
                cout << "\nBook added successfully!\n";
            else
                cout << "\nUnable to add book.\n";

            break;
        }

        // Display Books
        case 15:
            libraryManager.displayAllBooks();
            break;

        // Issue Book
        case 16: {
            string studentID, bookID, issueDate, dueDate;

            studentID = readString("Enter Student ID: ");
            bookID = readString("Enter Book ID: ");
            issueDate = readString("Enter Issue Date (YYYY-MM-DD): ");
            dueDate = readString("Enter Due Date (YYYY-MM-DD): ");

            if (libraryManager.issueBook(
                    studentID, bookID, issueDate, dueDate))
                cout << "\nBook issued successfully!\n";
            else
                cout << "\nBook issue failed.\n";

            break;
        }

        // Return Book
        case 17: {
            string studentID, bookID, returnDate;

            studentID = readString("Enter Student ID: ");
            bookID = readString("Enter Book ID: ");
            returnDate = readString("Enter Return Date (YYYY-MM-DD): ");

            if (libraryManager.returnBook(
                    studentID, bookID, returnDate))
                cout << "\nBook returned successfully!\n";
            else
                cout << "\nBook return failed.\n";

            break;
        }

        // Current Loans
        case 18:
            libraryManager.displayCurrentLoans();
            break;

        // Overdue Loans
        case 19: {
            string currentDate;

            currentDate = readString("Enter Current Date (YYYY-MM-DD): ");

            libraryManager.displayOverdueLoans(currentDate);
            break;
        }

        // Available Books
        case 20:
            libraryManager.displayAvailableBooks();
            break;

        // Add to Waiting List
        case 21: {
            string studentID, bookID;

            studentID = readString("Enter Student ID: ");
            bookID = readString("Enter Book ID: ");

            if (libraryManager.addToWaitingList(studentID, bookID))
                cout << "\nStudent added to waiting list!\n";
            else
                cout << "\nUnable to add student to waiting list.\n";

            break;
        }

        // Display Waiting List
        case 22: {
            string bookID;

            bookID = readString("Enter Book ID: ");

            libraryManager.displayWaitingList(bookID);
            break;
        }

        // Exit
        case 0:
            cout << "\nThank you for using Campus Management System!\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}