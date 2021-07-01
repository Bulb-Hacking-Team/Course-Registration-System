#pragma once
#include "leturer.h"

bool isEqualAcademicYears(void* year1, void* year2);

bool loadAcademicYearsAndSemester(const string& filePath, string*& listAcademicYears, string*& listSemesters, int& countAcademicYears);
void viewAcademicYearsAndSemester();

void removeCourse(const string& academicYear, const string& semester);
void viewClassList();

void importClass();
bool addClassName(string ClassName);
void addNewStudent();
void createClass();
void viewStudentsOfClass();
