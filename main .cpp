#include <iostream>
#include <string>
#include "file_handling.h"

using namespace std;
int getValidIntegerInput(const string& prompt) {
    int input;
    while (true) {
        cout << prompt;
        if (cin >> input) {
            return input;  // Return the valid input
        }
        else {
            cout << "Invalid input! Please enter an integer value." << endl;
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the incorrect input
        }
    }
}

int main() {
    loadData();  // Load data from files at startup

    int choice, role;
    string id, password;

    // Variable initialization moved outside the switch block

    bool teacherFound = false;
    bool studentFound = false;

    do {
        
        role = getValidIntegerInput("\nHello! Welcome to the Student Management System!!!\n"
            "---------------------------------------\n"
            "1. Admin\n2. Teacher\n3. Student\n4. Exit\nEnter your role: ");
 
        
        

        switch (role) {
        case 1:  // Admin login
            cout << "Enter Admin ID: ";
            cin >> id;
            cout << "Enter Password: ";
            cin >> password;
            if (id == "admin" && password == "admin123") {
                cout << "Admin Login Successful!\n";
                int adminChoice;
                do {
                    adminChoice = getValidIntegerInput("\n1. Add Teacher\n2. Delete Teacher\n3. Exit\nEnter choice: ");
                    if (adminChoice > 3 || adminChoice < 1)
                        cout << "Invalid Choice. Please Enter Again.\n";
                    if (adminChoice == 1) addTeacher();
                    else if (adminChoice == 2) deleteTeacher();
                } while (adminChoice != 3);
                cout << "Exit from admin menu\n";
            }
            else {
                cout << "Invalid Admin credentials!\n";
            }
            break;
        case 2:  // Teacher login
            cout << "Enter Teacher ID: ";
            cin >> id;
            cout << "Enter Password: ";
            cin >> password;
            teacherFound = false;
            for (int i = 0; i < teacherCount; i++) {
                if (teacherLogin[i] == id && teacherPasswords[i] == password) {
                    teacherFound = true;
                    cout << "Teacher Login Successful!\n";
                    int teacherChoice;
                    do {
                        teacherChoice = getValidIntegerInput("\n1. Add Student\n2. Delete Student\n3. Assign Marks\n"
                            "4. List Passed Students\n5. List Failed Students\n"
                            "6. Calculate CGPA for all students\n7. Average CGPA\n"
                            "8. List of Students\n9. Exit\nPlease Enter your Choice\n");
                        if (teacherChoice > 9 || teacherChoice < 1)
                            cout << "Invalid Choice. Please Enter Again.\n";
                        if (teacherChoice == 1) addStudent();
                        else if (teacherChoice == 2) deleteStudent();
                        else if (teacherChoice == 3) assignMarks();
                        else if (teacherChoice == 4) listPassedStudents();
                        else if (teacherChoice == 5) listFailedStudents();
                        else if (teacherChoice == 6) calculate();
                        else if (teacherChoice == 7) averageCGPA();
                        else if (teacherChoice == 8) listStudentsByCGPA();
                       

                    } while (teacherChoice != 9);
                    break;
                }
            }
            if (!teacherFound) {
                cout << "Invalid Teacher credentials!\n";
            }
            break;
        case 3:  // Student login
            cout << "Enter Student ID: ";
            cin >> id;
            cout << "Enter Password: ";
            cin >> password;
            studentFound = false;
            for (int i = 0; i < studentCount; i++) {
                if (studentLogin[i] == id && studentPasswords[i] == password) {
                    studentFound = true;
                    cout << "Student Login Successful!\n";
                    int studentChoice;
                    do {
                        
                        studentChoice = getValidIntegerInput("\n1. View Grades\n2. View CGPA\n3. Exit\nEnter choice: ");
                        if (studentChoice > 3 || studentChoice < 1)
                            cout << "Invalid Choice. Please Enter Again.\n";
                        if (studentChoice == 1) viewGrades(id);
                        else if (studentChoice == 2) viewCGPA(id);
                    } while (studentChoice != 3);
                    break;
                }
            }
            if (!studentFound) {
                cout << "Invalid Student credentials!\n";
            }
            break;
        case 4:
            saveData();  // Save data to files before exiting
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid role! Please choose a valid role.\n";
        }
        
    } while (role != 4);

    return 0;
}
