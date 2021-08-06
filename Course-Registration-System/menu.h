#pragma once
#include "staff.h"
#include "leturer.h"
#include "student.h"

void showMenu();
void showMenuOfStudent(Student& st);
void showMenuOfStaff(Staff& staff);

void loadStaff(ifstream& fin, Staff& s);
bool loadListStaffs(const string& filePath, Staff*& listStaffs, int& countStaff);
void showMenuOfCourse(const string& academicYear, const string& semester);

void loadStudentFromTxt(ifstream& fin, Student& st);
bool checkStudentForLogin(Student& st);
void getInputAcademicYearAndSemester(string& academicYear, string& semester);
bool login(short role, Staff& s, Student& st);
void changePassword(Account& acc);
void addNewStudent2(Student st);

void showMenuOfAttendanceList(const string& academicYear, const string& semester);
void showMenuOfLecturer(Lecturer& lec);
void viewSchedule2(const string& academicYear, const string& semester, const Student& st);
void viewGeneralInfo(GeneralInformation info);
void viewStudentInfo(Student st);
void showMenuOfClass();

