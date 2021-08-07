#pragma once
#include "course.h"

string createClassDirectoryWithFileName(const string& ClassName);
void loadStudentFromTxt(ifstream& fin, Student& st);
bool loadStudentList(const string& filePath, Student*& listStudents, int& countStudent);
Schedule* getScheduleOfStudent(const string& academicYear, const string& semester, const Student& st, int& count);

bool isEqualStudentIdFromCourse(void* val1, void* val2);
bool ascendingStudentId(void* Name1, void* Name2);
bool saveListScoreboardsToCsv(const string& filePath, StudentCourseInformation* listInfo, const int& countStudent);
void releaseListStudents(void* listStudents, const int& countStudent);
void copyStudent(void* st1, void* st2);
void* allocListStudents(const int& countStudent);
void viewSchedule(const string& academicYear, const string& semester, const Student& st);
bool isEqualStudentId(void* st1, void* st2);
void importStudentListFromCsv(const string& filePath);
void loadStudentFromCsv(ifstream& fin, Student& st);
void createAccountStudent(Student& st);
bool checkStudent(Student st);

bool ascendingStudentId(void* st1, void* st2);
bool checkStudentOfCourse(const string& academicYear, const string& semester, const Course& c, const Student& st);
void viewScores(const string& academicYear, const string& semester, const Student& st);
bool getInputCourseOfStudent(const string& academicYear, const string& semester, Course& course, const Student& st);
void viewStudentList(Student* listStudents, const int& countStudent);
void viewStudentListFromCourse(StudentCourseInformation* listInfo, const int& countStudent);
bool checkInImp(const Date& dt, const Time& tm, AttendanceList& attendList);
void checkIn(const string& academicYear, const string& semester, Student& st);
void viewCheckInResult(const string& academicYear, const string& semester, Student st);