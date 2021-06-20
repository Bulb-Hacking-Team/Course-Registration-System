#pragma once
#include "general.h"
string createClassDirectoryWithFileName(const string& ClassName);
void loadStudentFromTxt(ifstream& fin, Student& st);
bool loadStudentList(const string& filePath, Student*& listStudents, int& countStudent);