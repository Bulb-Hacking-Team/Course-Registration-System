#pragma once
#include "student.h"

bool isEqualLecturer(void* val1, void* val2);

bool getInputCourseOfLecturer(const string& academicYear, const string& semester, Course& course, Lecturer lec);

void* allocListLecturers(const int& countLecturer);

void copyLecturer(void* lec1, void* lec2);

void releaseListlecturers(void* listLecturers, const int& countLecturer);

bool loadListLecturers(const string& filePath, Lecturer*& listLecturers, int& countLecturer);

void loadLecturer(ifstream& fin, Lecturer& lec);

void saveLecturer(ofstream& fout, const Lecturer& lec);

void editAttendance(const string& academicYear, const string& semester, const Lecturer& lec);

bool saveListLecturers(const string& filePath, Lecturer*& listLecturers, int& countLecturer);

void importScoreboardsOfCourse(const string& academicYear, const string& semester, const Lecturer& lec);