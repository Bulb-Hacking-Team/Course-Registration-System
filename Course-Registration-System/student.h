#pragma once
#include "course.h"

string createClassDirectoryWithFileName(const string& ClassName);
void loadStudentFromTxt(ifstream& fin, Student& st);
bool loadStudentList(const string& filePath, Student*& listStudents, int& countStudent);
Schedule* getScheduleOfStudent(const string& academicYear, const string& semester, const Student& st, int& count);

bool isEqualStudentIdFromCourse(void* val1, void* val2);
bool ascendingStudentId(void* Name1, void* Name2);

void releaseListStudents(void* listStudents, const int& countStudent);
void copyStudent(void* st1, void* st2);
void* allocListStudents(const int& countStudent);
void viewSchedule(const string& academicYear, const string& semester, const Student& st);

bool checkStudentOfCourse(const string& academicYear, const string& semester, const Course& c, const Student& st);
void viewScores(const string& academicYear, const string& semester, const Student& st);
bool getInputCourseOfStudent(const string& academicYear, const string& semester, Course& course, const Student& st);

