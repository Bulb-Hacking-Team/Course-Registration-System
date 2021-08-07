#ifndef STAFF_H_
#define STAFF_H_

#include "leturer.h"

bool isEqualAcademicYears(void* year1, void* year2);

// Do not compare password and gender.
bool isEqualStaff(void* s1, void* s2);

bool ascendingAcademicYear(void* year1, void* year2);

bool ascendingSemester(void* semester1, void* semester2);

// Add a new class name to text file.
bool addClassName(string ClassName);

// Add a new student.
void addNewStudent();

void addLecturer(Lecturer lec);

void addNewCourse(const string& academicYear, const string& semester);

// Add a new student to course.
void addStudentToCourse(const string& academicYear, const string& semester);

bool addAcademicYearsAndSemester(string& academicYears, string& semester);

// Import students of a class such from a csv file.
void importClass();

bool EnrollClassToCourse(const string& filePath, const Course& course);

void importListCoursesFromCsv(const string& filePath, const string& academicYear, const string& semester);

void importCourses(const string& academicYear, const string& semester);

void createAcademicYearsAndSemester();

//Print list of classes
void viewClassList();

// Load students from a class file and show student list on the screen.
// Lưu dữ liệu vào mảng listStudents và countStudent.
// Mảng listStudents có thể là mảng động hoặc mảng tĩnh.
// Hàm này không giải phóng mảng nếu là mảng động, phải tự giải phóng.
void viewStudentsOfClass();

// View list students of course.
void viewListStudentsOfCourse(const string& academicYear, const string& semester);

// View list of courses in the current semester.
void viewListCourses(const string& academicYear, const string& semester);

void viewScoreboardOfCourse(const string& academicYear, const string& semester);

void viewAttendanceListOfCourse(const string& academicYear, const string& semester);

void viewAcademicYearsAndSemester();

void viewLecturer(const Lecturer& lec);

void viewLecturerList();

void showFunctionsOfLecturer();

void showFunctionsOfAcademicYearAndSemester();

bool loadAcademicYearsAndSemester(const string& filePath, string*& listAcademicYears, string*& listSemesters,
	int& countAcademicYears);

bool saveAcademicYearsAndSemester(const string& filePath, string* listAcademicYears, string* listSemesters,
	const int& countAcademicYears);

// Export a scoreboard to a csv file.
void ExportScoreboardToCsv(const string& academicYear, const string& semester);

// Export a attendance list to a csv file.
void ExportAttendanceListToCsv(const string& academicYear, const string& semester);

// Input file automatically
// Show list of classes to pick. Chose No of class.
// Show list of student in the class. Chose student ID to manage.
// Ask if staff want to remove that student. Change the second number into 0 if staff chose 1.

// Remove a specific course.
void removeCourse(const string& academicYear, const string& semester);

void removeStudentFromCourse(const string& academicYear, const string& semester);

bool deleteAcademicYears(string academicYears);

bool deleteSemesterFromAcademicYears(string academicYears, string semester);

void deleteAcademicYearsAndSemester();

bool deleteLecturer();

void editCourseID(Course& course, const string academicYear, const string semester);
void editCourseName(Course& course);
void editCourseLecturer(Course& course);
void editDate(Course& course);
void editDayOfWeek(Course& course);
void editTime(Course& course);
void editRoom(Course& course);
void editAnExistingCourse(const string& academicYear, const string& semester);

void editStudentID(Student& st);
void editStudentName(Student& st);
void editStudentDOB(Student& st);
void editStudentGender(Student& st);
void editStudent();

void editLecturerName(Lecturer& lec);
void editLecturerGender(Lecturer& lec);
void editLecturerDegree(Lecturer& lec);
void editLecturer();

void updateClassForStudentFromCourse(const Student& st, const string& newClass);
void changeStudentClass();
void createClass();
#endif