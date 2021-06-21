#ifndef STUDENT_H_
#define STUDENT_H_
#include "course.h"

string createClassDirectoryWithFileName(const string& ClassName);
void loadStudentFromTxt(ifstream& fin, Student& st);
bool loadStudentList(const string& filePath, Student*& listStudents, int& countStudent);
Schedule* getScheduleOfStudent(const string& academicYear, const string& semester, const Student& st, int& count);

void releaseListStudents(void* listStudents, const int& countStudent);
void copyStudent(void* st1, void* st2);
void* allocListStudents(const int& countStudent);
#endif