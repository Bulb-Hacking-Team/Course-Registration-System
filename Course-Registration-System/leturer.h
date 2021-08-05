#pragma once
#include "student.h"

bool isEqualLecturer(void* val1, void* val2);

bool getInputCourseOfLecturer(const string& academicYear, const string& semester, Course& course, Lecturer lec);

void* allocListLecturers(const int& countLecturer);

void copyLecturer(void* lec1, void* lec2);
