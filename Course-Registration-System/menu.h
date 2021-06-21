#ifndef MENU_H_
#define MENU_H_
//#include "general.h"
#include "staff.h"
#include "leturer.h"
#include "student.h"

void showMenu();
void showMenuOfStudent(Student& st);
void showMenuOfStaff(Staff& staff);
int getChoice(const int& minValue, const int& maxValue);

void loadStaff(ifstream& fin, Staff& s);
bool loadListStaffs(const string& filePath, Staff*& listStaffs, int& countStaff);



void loadStudentFromTxt(ifstream& fin, Student& st);
bool checkStudentForLogin(Student& st);
void getInputAcademicYearAndSemester(string& academicYear, string& semester);
bool login(short role, Staff& s, Student& st);
#endif