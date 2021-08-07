#pragma once
#include "leturer.h"

bool isEqualAcademicYears(void* year1, void* year2);

bool loadAcademicYearsAndSemester(const string& filePath, string*& listAcademicYears, string*& listSemesters, int& countAcademicYears);
void viewAcademicYearsAndSemester();

void removeCourse(const string& academicYear, const string& semester);
void viewClassList();
void importCourses(const string& academicYear, const string& semester);

void importClass();
bool ascendingSemester(void* semester1, void* semester2);
bool EnrollClassToCourse(const string& filePath, const Course& course);
void createAcademicYearsAndSemester();
bool addAcademicYearsAndSemester(string& academicYears, string& semester);
bool saveAcademicYearsAndSemester(const string& filePath, string* listAcademicYears, string* listSemesters,
	const int& countAcademicYears);
bool addClassName(string ClassName);
void addNewStudent();
void createClass();
void viewStudentsOfClass();
void ExportScoreboardToCsv(const string& academicYear, const string& semester);
void importListCoursesFromCsv(const string& filePath, const string& academicYear, const string& semester);

void editCourseID(Course& course, const string academicYear, const string semester);
void editCourseName(Course& course);
void editCourseLecturer(Course& course);
void editDate(Course& course);
void editDayOfWeek(Course& course);
void editTime(Course& course);
void editRoom(Course& course);
void editAnExistingCourse(const string& academicYear, const string& semester);
void viewScoreboardOfCourse(const string& academicYear, const string& semester);
void viewAttendanceListOfCourse(const string& academicYear, const string& semester);
