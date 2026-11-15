CAMPUS MANAGEMENT SYSTEM

1. Project Overview

The Campus Management System is a console-based application developed using C++17. It is designed to manage the academic and library activities of a college or educational institution.

The system provides facilities for managing student records, courses, enrollments, academic results, marksheets, rankings, and library operations.

It uses file handling to store and retrieve data.

2. Objectives of the Project

- To simplify student record management.
- To manage courses and student enrollments.
- To maintain academic results and marksheets.
- To generate student rankings and display top performers.
- To manage library books and transactions.
- To provide data storage using file handling.

3. Technologies Used

- Programming Language: C++17
- IDE: Visual Studio Code
- Compiler: GCC (g++)
- Operating System: Windows
- Storage: File Handling

4. Main Features

Student Management

- Add new student records.
- Display student details.
- Search student records.
- Update student information.
- Remove student records.

Course Management

- Add new courses.
- Display available courses.
- Enroll students in courses.
- Display student course information.

Result Management

- Enter student marks.
- Display course results.
- Generate student marksheets.
- Generate student rankings.
- Display top performers.
- Validate marks.

Library Management

- Add books.
- Display book inventory.
- Issue books to students.
- Return issued books.
- Display current loans.
- Track overdue loans.
- Manage book waiting lists.
- Display available books.

5. Project Folder Structure

Campus_Management_System/
│
├── src/
│   ├── main.cpp
│   ├── Student.cpp
│   ├── Course.cpp
│   ├── StudentManager.cpp
│   ├── CourseManager.cpp
│   ├── ResultManager.cpp
│   ├── LibraryManager.cpp
│   ├── Book.cpp
│   └── LibraryTransaction.cpp
│
├── include/
│   ├── Student.h
│   ├── Course.h
│   ├── Book.h
│   ├── LibraryTransaction.h
│   ├── ManagerHeaders.h
│   ├── StudentManager.h
│   ├── CourseManager.h
│   ├── ResultManager.h
│   └── LibraryManager.h
│
├── data/
│   ├── students.txt
│   ├── courses.txt
│   ├── enrollments.txt
│   ├── results.txt
│   ├── books.txt
│   └── loans.txt
│
├── docs/
│   ├── System_Architecture.pdf
│   ├── Data_Structures_and_Algorithms.pdf
│   └── Test_Cases.pdf
│
├── screenshots/
│
└── README.md

6. System Requirements

- Windows Operating System
- Visual Studio Code
- GCC C++ Compiler
- C++17 Support

7. Setup and Compilation Instructions

Step 1: Install Visual Studio Code and GCC compiler.

Step 2: Open the Campus Management System project folder in VS Code.

Step 3: Open the integrated terminal.

Step 4: Compile the project using the following command:

g++ -std=c++17 src/main.cpp src/Student.cpp src/Course.cpp src/StudentManager.cpp src/CourseManager.cpp src/ResultManager.cpp src/Book.cpp src/LibraryTransaction.cpp src/LibraryManager.cpp -o CampusManagement

8. Execution Instructions

After successful compilation, execute the application using:

.\CampusManagement.exe

The main menu will appear. Select the required option to access different modules.

9. Data Structures Used

1. Vector

Used to store collections of records and manage data dynamically.

2. Pair

Used to store two related values together.

3. Unordered Map

Used for key-value based data management and efficient average-case lookup.

4. Queue

Used to manage book waiting-list operations in FIFO order.

10. Algorithms Used

1. Linear Search

Linear Search is used to find a particular record by checking elements one by one.

Time Complexity:

- Best Case: O(1)
- Average Case: O(n)
- Worst Case: O(n)

Space Complexity: O(1)

2. Merge Sort

Merge Sort is used to arrange student result records in descending order of marks for ranking purposes.

Time Complexity:

- Best Case: O(n log n)
- Average Case: O(n log n)
- Worst Case: O(n log n)

Auxiliary Space Complexity: O(n)

11. File Handling

The project uses text files to store and retrieve information.

The following files are used:

- students.txt – Student records
- courses.txt – Course records
- enrollments.txt – Enrollment information
- results.txt – Academic results
- books.txt – Library book records
- loans.txt – Book loan records

File handling helps maintain data between program executions.

12. Testing and Validation

The project is tested using different test cases covering student management, course management, enrollment, results, and library operations.

The test cases include:

- Adding and displaying student records.
- Searching and updating student information.
- Adding and displaying courses.
- Student enrollment.
- Duplicate enrollment validation.
- Entering valid and invalid marks.
- Generating marksheets and rankings.
- Adding and issuing books.
- Returning books.
- Invalid ID handling.
- File data persistence.

Some test cases, including course capacity, overdue tracking, and waiting-list testing, require final verification.

Refer to the "docs/Test_Cases.pdf" file for the detailed test case list and results.

13. Screenshots and Sample Outputs

The "screenshots" folder contains screenshots demonstrating the working of different modules, including:

- Student registration and profile management.
- Course creation and enrollment.
- Academic results and marksheets.
- Student ranking and top performers.
- Library inventory.
- Book issue and return.
- Searching, sorting, and error handling.

14. Project Documentation

The "docs" folder contains the following documentation:

1. System Architecture
2. Data Structures and Algorithms
3. Test Cases and Results

The project report PDF and demonstration video should also be included or linked as required by the submission guidelines.

15. Conclusion

The Campus Management System provides a simple and organized solution for managing academic and library activities.

The project demonstrates the practical implementation of C++17 programming concepts, object-oriented programming, data structures, algorithms, and file handling.