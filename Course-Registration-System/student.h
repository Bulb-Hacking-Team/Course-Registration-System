#ifndef STUDENT_H_
#define STUDENT_H_
#include "course.h"

string createClassDirectoryWithFileName(const string& ClassName);
// Create account for student.
void createAccountStudent(Student& st);
// Returns true if st1.id equal to st2.id; otherwise returns false.
bool isEqualStudentId(void* st1, void* st2);
// Giống với hàm isEqualStudentId nhưng dùng cho struct StudentCourseInformation.
bool isEqualStudentIdFromCourse(void* val1, void* val2);
bool checkStudentOfCourse(const string& academicYear, const string& semester, const Course& c, const Student& st);

bool checkStudent(Student st);

bool getInputCourseOfStudent(const string& academicYear, const string& semester, Course& course, const Student& st);

int getInputStudent(Student*& listStudents, const int& countStudent);

Schedule* getScheduleOfStudent(const string& academicYear, const string& semester, const Student& st, int& count);

// Returns true if st1.id greater than st2.id; otherwise returns false.
bool ascendingStudentId(void* st1, void* st2);

void* allocListStudents(const int& countStudent);

void copyStudent(void* st1, void* st2);

void releaseListStudents(void* listStudents, const int& countStudent);

bool checkInImp(const Date& dt, const Time& tm, AttendanceList& attendList);


void loadStudentFromCsv(ifstream& fin, Student& st);


// Import student list from a csv file.
void importStudentListFromCsv(const string& filePath);


// Read the list of students to a text file.
// Mảng listStudents sẽ được cấp phát bên trong hàm này.
// Mảng listStudents phải là mảng động.
bool loadStudentList(const string& filePath, Student*& listStudents, int& countStudent);


// Save the list of students to a text file.
// Mảng listStudents phải có dữ liệu trước (đã cấp phát rồi).
// Mảng listStudents có thể là mảng động hoặc mảng tĩnh.
// Hàm này không giải phóng mảng nếu là mảng động, phải tự giải phóng.
bool saveStudentList(const string& filePath, Student* listStudents, const int& countStudent);


// Save the list of scoreboards to a csv file.
// Mảng listInfo phải có dữ liệu trước (đã cấp phát rồi).
// Mảng listInfo có thể là mảng động hoặc mảng tĩnh.
// Hàm này không giải phóng mảng nếu là mảng động, phải tự giải phóng.
bool saveListScoreboardsToCsv(const string& filePath, StudentCourseInformation* listInfo, const int& countStudent);

void viewStudentList(Student* listStudents, const int& countStudent);

void viewStudentListFromCourse(StudentCourseInformation* listInfo, const int& countStudent);

void viewSchedule(const string& academicYear, const string& semester, const Student& st);

void viewScores(const string& academicYear, const string& semester, const Student& st);

// View check-in result of a student.
void viewCheckInResult(const string& academicYear, const string& semester, Student st);

void checkIn(const string& academicYear, const string& semester, Student& st);
void sortArray_1(Student* listInfo, int countStudent);
#endif