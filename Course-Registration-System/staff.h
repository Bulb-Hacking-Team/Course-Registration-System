#pragma once
#include "leturer.h"

bool isEqualAcademicYears(void* year1, void* year2);

bool loadAcademicYearsAndSemester(const string& filePath, string*& listAcademicYears, string*& listSemesters, int& countAcademicYears);
void viewAcademicYearsAndSemester();

void removeCourse(const string& academicYear, const string& semester);
void viewClassList();

void importClass();
bool ascendingSemester(void* semester1, void* semester2);

void createAcademicYearsAndSemester();
bool addAcademicYearsAndSemester(string& academicYears, string& semester);
bool saveAcademicYearsAndSemester(const string& filePath, string* listAcademicYears, string* listSemesters,
	const int& countAcademicYears);
bool addClassName(string ClassName);
void addNewStudent();
void createClass();
void viewStudentsOfClass();
