#pragma once
#include "student.h"

bool isEqualLecturer(void* val1, void* val2);

bool getInputCourseOfLecturer(const string& academicYear, const string& semester, Course& course, Lecturer lec);

void* allocListLecturers(const int& countLecturer);

void copyLecturer(void* lec1, void* lec2);

void viewListCourses(const string& academicYear, const string& semester, Lecturer& lec);

void viewAttendanceListOfCourseForLecturer(const string& academicYear,
	const string& semester, Lecturer& lec);

void releaseListlecturers(void* listLecturers, const int& countLecturer);

bool loadListLecturers(const string& filePath, Lecturer*& listLecturers, int& countLecturer);

bool loadListScoreboardFromCsv(const string& filePath, StudentCourseInformation*& listInfo, int& countStudent);

void viewScoreboardOfCourse(const string& academicYear, const string& semester, const Lecturer& lec);

void viewListStudentsOfCourse(const string& academicYear, const string& semester, const Lecturer& lec);

void editGradeStudent(const string& academicYear, const string& semester, const Lecturer& lec);

void loadLecturer(ifstream& fin, Lecturer& lec);

void saveLecturer(ofstream& fout, const Lecturer& lec);

void editAttendance(const string& academicYear, const string& semester, const Lecturer& lec);

bool saveListLecturers(const string& filePath, Lecturer*& listLecturers, int& countLecturer);

void importScoreboardsOfCourse(const string& academicYear, const string& semester, const Lecturer& lec);