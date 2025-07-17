#include "file_handling.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <limits>

using namespace std;

Student students[MAX_STUDENTS];
Teacher teachers[MAX_TEACHERS];
int studentCount = 0, teacherCount = 0;

// Global login arrays

string teacherLogin[MAX_TEACHERS];
string teacherPasswords[MAX_TEACHERS];
string studentLogin[MAX_STUDENTS];
string studentPasswords[MAX_STUDENTS];


// Function to validate student and teacher ID (alphanumeric only)
bool isValidID(const string& id) {
    return regex_match(id, regex("^[A-Za-z0-9]+$"));
}

// Function to validate name input (only letters and spaces)
bool isValidName(const string& name) {
    return regex_match(name, regex("^[A-Za-z ]+$"));
}

// Function to validate marks input (only integers)
bool isValidMarksInput(const string& input) {
    // Check if the input is a valid integer
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }

    // Convert the input string to an integer
    int marks = stoi(input);

    // Check if marks are between 1 and 100 (inclusive)
    if (marks < 1 || marks > 100) {
        return false;
    }

    return true;
}


// Function to assign grades based on marks
char assignGrade(int totalMarks) {
    if (totalMarks >= 85) return 'A';
    if (totalMarks >= 70) return 'B';
    if (totalMarks >= 55) return 'C';
    return 'F';
}


// Function to load students from file

void loadStudents(Student students[], int& studentCount) {
    ifstream file("students.txt");
    studentCount = 0;
    if (file.is_open()) {
        string temp;
        while (getline(file, temp)) {
            if (temp.find("Name:") == 0) {
                students[studentCount].name = temp.substr(6);  // Extract the name after "Name: "
            }
            getline(file, temp);  // Read next line for ID
            if (temp.find("ID:") == 0) {
                students[studentCount].id = temp.substr(4);  // Extract the ID after "ID: "
            }
            getline(file, temp);  // Read next line for Class
            if (temp.find("Class:") == 0) {
                students[studentCount].class_name = temp.substr(7);  // Extract the class after "Class: "
            }
            for (int j = 0; j < 5; j++) {
                getline(file, temp);  // Read next line for Subject
                if (temp.find("Subject") == 0) {
                    students[studentCount].subjects[j] = temp.substr(temp.find(":") + 2);  // Extract subject name after ": "
                }
                getline(file, temp);  // Read Quiz Marks
                if (temp.find("Quiz Marks") == 0) {
                    students[studentCount].quizMarks[j] = stoi(temp.substr(temp.find(":") + 2));  // Extract Quiz Marks
                }
                getline(file, temp);  // Read Assignment Marks
                if (temp.find("Assignment Marks") == 0) {
                    students[studentCount].assignmentMarks[j] = stoi(temp.substr(temp.find(":") + 2));  // Extract Assignment Marks
                }
                getline(file, temp);  // Read Sessional Marks
                if (temp.find("Sessional Marks") == 0) {
                    students[studentCount].sessionalMarks[j] = stoi(temp.substr(temp.find(":") + 2));  // Extract Sessional Marks
                }
                getline(file, temp);  // Read Total Marks
                if (temp.find("Total Marks") == 0) {
                    students[studentCount].totalMarks[j] = stoi(temp.substr(temp.find(":") + 2));  // Extract Total Marks
                }
                getline(file, temp);  // Read Grade
                if (temp.find("Grade") == 0) {
                    students[studentCount].grades[j] = temp.substr(temp.find(":") + 2)[0];  // Extract Grade
                }
            }
            getline(file, temp);  // Read CGPA
            if (temp.find("CGPA:") == 0) {
                students[studentCount].CGPA = stof(temp.substr(6));  // Extract CGPA after "CGPA: "
            }
            getline(file, temp);  // Read next line for Password
            if (temp.find("Password:") == 0) {
                studentPasswords[studentCount] = temp.substr(10);  // Extract password after "Password: "
            }
            getline(file, temp);  // Read the separator line (---------------------)
            studentLogin[studentCount] = students[studentCount].id;  // Add the login ID to the array
            studentCount++;
        }
        file.close();
        cout << "Student records loaded successfully!\n";
    }
    else {
        cout << "No student data found, starting fresh.\n";
    }
}




// Function to save students to file
void saveStudents(Student students[], int studentCount) {
    ofstream file("students.txt");
    if (!file) {
        cout << "Error opening students file!" << endl;
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        file << "Name: " << students[i].name << endl;
        file << "ID: " << students[i].id << endl;
        file << "Class: " << students[i].class_name << endl;
        for (int j = 0; j < 5; j++) {
            file << "Subject " << (j + 1) << ": " << students[i].subjects[j] << endl;
            file << "Quiz Marks: " << students[i].quizMarks[j] << "/25" << endl;
            file << "Assignment Marks: " << students[i].assignmentMarks[j] << "/25" << endl;
            file << "Sessional Marks: " << students[i].sessionalMarks[j] << "/50" << endl;
            file << "Total Marks: " << students[i].totalMarks[j] << "/100" << endl;
            file << "Grade: " << students[i].grades[j] << endl;
        }
        file << "CGPA: " << students[i].CGPA << endl;
        file << "Password: " << studentPasswords[i] << endl;  // Save student password
        file << "---------------------" << endl;  // Divider for each record
    }
    file.close();
    cout << "Student records saved successfully!\n";
}




// Function to load teachers from file in the desired format
void loadTeachers(Teacher teachers[], int& teacherCount) {
    ifstream file("teachers.txt");
    teacherCount = 0;
    if (file.is_open()) {
        string temp;
        while (getline(file, temp)) {
            if (temp.find("Name:") == 0) {
                teachers[teacherCount].name = temp.substr(6);  // Extract the name after "Name: "
            }
            getline(file, temp);  // Read next line for ID
            if (temp.find("ID:") == 0) {
                teachers[teacherCount].id = temp.substr(4);  // Extract the ID after "ID: "
            }
            getline(file, temp);  // Read next line for Class
            if (temp.find("Class:") == 0) {
                teachers[teacherCount].class_name = temp.substr(7);  // Extract the class after "Class: "
            }
            getline(file, temp);  // Read next line for Subject
            if (temp.find("Subject:") == 0) {
                teachers[teacherCount].subject = temp.substr(9);  // Extract the subject after "Subject: "
            }
            getline(file, temp);  // Read next line for password
            if (temp.find("Password:") == 0) {
                teacherPasswords[teacherCount] = temp.substr(10);  // Extract password after "Password: "
            }
            getline(file, temp);  // Read the separator line (---------------------)
            teacherLogin[teacherCount] = teachers[teacherCount].id;  // Add the login ID to the array
            teacherCount++;
        }
        file.close();
        cout << "Teacher records loaded successfully!\n";
    }
    else {
        cout << "No teacher data found, starting fresh.\n";
    }
}

// Function to save teachers to file in the desired format
void saveTeachers(Teacher teachers[], int teacherCount) {
    ofstream file("teachers.txt");
    if (!file) {
        cout << "Error opening teachers file!" << endl;
        return;
    }

    for (int i = 0; i < teacherCount; i++) {
        file << "Name: " << teachers[i].name << endl;
        file << "ID: " << teachers[i].id << endl;
        file << "Class: " << teachers[i].class_name << endl;
        file << "Subject: " << teachers[i].subject << endl;
        file << "Password: " << teacherPasswords[i] << endl;  // Save teacher password
        file << "---------------------" << endl;  // Divider for each record
    }
    file.close();
    cout << "Teacher records saved successfully!\n";
}



void loadData() {
    loadStudents(students, studentCount);
    loadTeachers(teachers, teacherCount);
}

void saveData() {
    saveStudents(students, studentCount);
    saveTeachers(teachers, teacherCount);
}

// Admin functions
void addTeacher() {
    if (teacherCount < MAX_TEACHERS) {
        cout << "Enter Teacher ID (no special characters): ";
        cin >> teachers[teacherCount].id;
        while (!isValidID(teachers[teacherCount].id)) {
            cout << "Invalid ID! Enter again: ";
            cin >> teachers[teacherCount].id;
        }

        cout << "Enter Teacher Name: ";
        cin.ignore();
        getline(cin, teachers[teacherCount].name);
        while (!isValidName(teachers[teacherCount].name)) {
            cout << "Invalid name! Enter again: ";
            getline(cin, teachers[teacherCount].name);
        }

        cout << "Enter Subject: ";
        getline(cin, teachers[teacherCount].subject);

        cout << "Enter Class: ";
        getline(cin, teachers[teacherCount].class_name);

        cout << "Set Teacher Login Password: ";
        cin >> teacherPasswords[teacherCount];
        teacherLogin[teacherCount] = teachers[teacherCount].id;
        teacherCount++;
        cout << "Teacher added successfully!\n";
        saveTeachers(teachers, teacherCount);
    }
    else {
        cout << "Max teacher limit reached!\n";
    }
}

void deleteTeacher() {
    string id;
    cout << "Enter Teacher ID to delete: ";
    cin >> id;
    for (int i = 0; i < teacherCount; i++) {
        if (teachers[i].id == id) {
            for (int j = i; j < teacherCount - 1; j++) {
                teachers[j] = teachers[j + 1];
                teacherPasswords[j] = teacherPasswords[j + 1];
            }
            teacherCount--;
            cout << "Teacher deleted successfully!\n";
            saveTeachers(teachers, teacherCount);
            return;
        }
    }
    cout << "Teacher not found!\n";
}

// Teacher functions
void addStudent() {
    if (studentCount < MAX_STUDENTS) {
        cout << "Enter Student ID (no special characters): ";
        cin >> students[studentCount].id;
        while (!isValidID(students[studentCount].id)) {
            cout << "Invalid ID! Enter again: ";
            cin >> students[studentCount].id;
        }

        cout << "Enter Student Name: ";
        cin.ignore();
        getline(cin, students[studentCount].name);
        while (!isValidName(students[studentCount].name)) {
            cout << "Invalid name! Enter again: ";
            getline(cin, students[studentCount].name);
        }

        cout << "Enter Class: ";
        getline(cin, students[studentCount].class_name);

        cout << "Set Student Login Password: ";
        cin >> studentPasswords[studentCount];
        studentLogin[studentCount] = students[studentCount].id;
        studentCount++;
        cout << "Student added successfully!\n";
        saveStudents(students, studentCount);
    }
    else {
        cout << "Max student limit reached!\n";
    }
}

void deleteStudent() {
    string id;
    cout << "Enter Student ID to delete: ";
    cin >> id;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
                studentPasswords[j] = studentPasswords[j + 1];
            }
            studentCount--;
            cout << "Student deleted successfully!\n";
            saveStudents(students, studentCount);
            return;
        }
    }
    cout << "Student not found!\n";
}

void assignMarks() {
    string id;
    cout << "Enter Student ID to assign marks: ";
    cin >> id;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            float totalCGPAMarks = 0;  // To calculate the total marks for CGPA
            cout << "Assigning marks for 5 subjects:\n";

            for (int j = 0; j < 5; j++) {
                cout << "Enter Subject " << (j + 1) << " Name: ";
                cin.ignore();  // Clear any leftover input
                getline(cin, students[i].subjects[j]);  // Get subject name

                // Get Quiz, Assignment, and Sessional Marks
                int quizMarks, assignmentMarks, sessionalMarks;
                string input;

                // Input Quiz Marks
                cout << "Enter Quiz Marks (out of 25) for " << students[i].subjects[j] << ": ";
                while (true) {
                    cin >> input;
                    if (isValidMarksInput(input) && stoi(input) <= 25 && stoi(input) >= 0) {
                        quizMarks = stoi(input);
                        break;
                    }
                    else {
                        cout << "Invalid input! Enter a valid integer between 0 and 25: ";
                    }
                }

                // Input Assignment Marks
                cout << "Enter Assignment Marks (out of 25) for " << students[i].subjects[j] << ": ";
                while (true) {
                    cin >> input;
                    if (isValidMarksInput(input) && stoi(input) <= 25 && stoi(input) >= 0) {
                        assignmentMarks = stoi(input);
                        break;
                    }
                    else {
                        cout << "Invalid input! Enter a valid integer between 0 and 25: ";
                    }
                }

                // Input Sessional Marks
                cout << "Enter Sessional Marks (out of 50) for " << students[i].subjects[j] << ": ";
                while (true) {
                    cin >> input;
                    if (isValidMarksInput(input) && stoi(input) <= 50 && stoi(input) >= 0) {
                        sessionalMarks = stoi(input);
                        break;
                    }
                    else {
                        cout << "Invalid input! Enter a valid integer between 0 and 50: ";
                    }
                }

                // Store the marks and calculate total
                students[i].quizMarks[j] = quizMarks;
                students[i].assignmentMarks[j] = assignmentMarks;
                students[i].sessionalMarks[j] = sessionalMarks;
                students[i].totalMarks[j] = quizMarks + assignmentMarks + sessionalMarks;

                // Assign grade based on total marks
                students[i].grades[j] = assignGrade(students[i].totalMarks[j]);

                // Add total marks to calculate CGPA later
                totalCGPAMarks += students[i].totalMarks[j];
            }

            // Calculate CGPA based on total marks (assuming CGPA out of 4)
            students[i].CGPA = (totalCGPAMarks / 500) * 4;  // 500 is the max total marks (5 subjects * 100 marks each)
            cout << "Marks assigned and CGPA calculated!\n";
            saveStudents(students, studentCount);  // Save data after assigning marks
            return;
        }
    }
    cout << "Student not found!\n";
}


void listPassedStudents() {
    cout << "List of Passed Students (CGPA >= 2.0): \n";
    for (int i = 0; i < studentCount; i++) {
        if (students[i].CGPA >= 2.0) {
            cout << students[i].name << " (CGPA: " << students[i].CGPA << ")\n";
        }
    }
}

void listFailedStudents() {
    cout << "List of Failed Students (CGPA < 2.0): \n";
    for (int i = 0; i < studentCount; i++) {
        if (students[i].CGPA < 2.0) {
            cout << students[i].name << " (CGPA: " << students[i].CGPA << ")\n";
        }
    }
}

void viewGrades(string id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << "Grades for " << students[i].name << ": \n";
            for (int j = 0; j < 5; j++) {
                cout << "Marks of : "<<students[i].subjects[j] << ": " << endl  // Display the subject name
                    << " Quiz Marks: " << students[i].quizMarks[j] << " /25  " << endl
                    << " Assignment Marks: " << students[i].assignmentMarks[j] << " /25  " << endl
                    << " Sessional Marks: " << students[i].sessionalMarks[j] << " /50  " << endl
                    << " Total Marks: " << students[i].totalMarks[j] << " /100   " << endl
                    << " Grade: " << students[i].grades[j] << "\n" << endl;
            }
            return;
        }
    }
    cout << "Student not found!\n";
}


void viewCGPA(string id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << "CGPA for " << students[i].name << ": " << students[i].CGPA << "\n";
            return;
        }
    }
    cout << "Student not found!\n";
}



void averageCGPA() {
    if (studentCount == 0) {
        cout << "No students available to calculate average CGPA.\n";
        return;
    }

    float totalCGPA = 0;
    for (int i = 0; i < studentCount; i++) {
        totalCGPA += students[i].CGPA;
    }
    float average = totalCGPA / studentCount;
    cout << "The average CGPA of all students is: " << average << "\n";
}
// Function to sort students in ascending order by CGPA
void sortStudentsByCGPAAscending() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].CGPA > students[j + 1].CGPA) {
                // Swap students[j] and students[j + 1]
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// Function to sort students in descending order by CGPA
void sortStudentsByCGPADescending() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].CGPA < students[j + 1].CGPA) {
                // Swap students[j] and students[j + 1]
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void listStudentsByCGPA() {
    int sortChoice;
    cout << "Sort students by CGPA:\n";
    cout << "1. Ascending order\n";
    cout << "2. Descending order\n";
    cout << "Enter your choice: ";
    cin >> sortChoice;

    if (sortChoice == 1) {
        sortStudentsByCGPAAscending();
        displayStudents();
    }
    else if (sortChoice == 2) {
        sortStudentsByCGPADescending();
        displayStudents();
    }
    
    else {
        cout << "Invalid choice! Please choose 1 for Ascending or 2 for Descending.\n";
    }
}
void displayStudents() {
    cout << "Displaying list of students:\n";
    for (int i = 0; i < studentCount; i++) {
        cout << "Name: " << students[i].name << ", CGPA: " << students[i].CGPA << endl;
    }
}

void calculate() {
    for (int i = 0; i < studentCount; i++) {
        float totalCGPAMarks = 0;
        for (int j = 0; j < 5; j++) {
            totalCGPAMarks += students[i].totalMarks[j];  // Use total marks to calculate CGPA
        }
        students[i].CGPA = (totalCGPAMarks / 500) * 4;  // Assuming 500 is the total possible marks (5 subjects, 100 each)
    }
    cout << "CGPA for all students calculated successfully!\n";
    saveStudents(students, studentCount);  // Save updated CGPA values to file
}
