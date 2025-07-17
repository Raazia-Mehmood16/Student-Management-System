#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <string>

using namespace std;

const int MAX_STUDENTS = 30;
const int MAX_TEACHERS = 5;

// Structures to store student and teacher data
struct Student {
    string id;
    string name;
    string class_name;
    string subjects[5] ;
    // 5 subjects for each student
    int quizMarks[5];        // Quiz marks for each subject
    int assignmentMarks[5];  // Assignment marks for each subject
    int sessionalMarks[5];   // Sessional marks for each subject
    int totalMarks[5];       // Total marks for each subject (quiz + assignment + sessional)
    char grades[5];          // Grade for each subject
    float CGPA;              // CGPA of the student
};


struct Teacher {
    string id;
    string name;
    string subject;
    string class_name;    // Class for teacher
};

// Declare global arrays for storing data
extern Student students[MAX_STUDENTS];
extern Teacher teachers[MAX_TEACHERS];
extern int studentCount, teacherCount;

// Declare global arrays for login data
extern string teacherLogin[MAX_TEACHERS];
extern string teacherPasswords[MAX_TEACHERS];
extern string studentLogin[MAX_STUDENTS];
extern string studentPasswords[MAX_STUDENTS];




// File handling functions
void loadStudents(Student students[], int& studentCount);
void saveStudents(Student students[], int studentCount);
void loadTeachers(Teacher teachers[], int& teacherCount);
void saveTeachers(Teacher teachers[], int teacherCount);

// Admin and Teacher functions
void addTeacher();
void deleteTeacher();

// Student functions
void addStudent();
void deleteStudent();
void assignMarks();
void averageCGPA();
void calculate();
void listPassedStudents();
void listFailedStudents();
void listStudentsByCGPA();
void sortStudentsByCGPADescending();
void sortStudentsByCGPAAscending();
void displayStudents();


// Student view functions
void viewGrades(string id);
void viewCGPA(string id);

// File handling to load and save all data
void loadData();
void saveData();


// Input validation functions
bool isValidID(const string& id);
bool isValidName(const string& name);
bool isValidMarksInput(const string& input);



// Grade assignment based on marks
char assignGrade(int marks);

#endif
