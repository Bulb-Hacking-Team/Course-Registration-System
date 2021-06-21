#ifndef STAFF_H_
#define STAFF_H_
#include "leturer.h"

bool isEqualAcademicYears(void* year1, void* year2);

bool loadAcademicYearsAndSemester(const string& filePath, string*& listAcademicYears, string*& listSemesters, int& countAcademicYears);
void viewAcademicYearsAndSemester();

void removeCourse(const string& academicYear, const string& semester);

#endif