#pragma once
#include "general.h"

string createCourseDirectoryWithFileName(const string& academicYear, const string& semester, const string& ClassName, const string& argLast, const string& FileExtension);
void loadCourse(ifstream& fin, Course& course);
bool loadListCourses(const string& filePath, Course*& listCourses, int& countCourse);
void initAttendanceList(AttendanceList& listAttends, const int& numberOfWeeks);
void loadScoreboard(ifstream& fin, Scoreboard& scoreboard, const string& FileExtension);
void loadAttendanceList(ifstream& fin, AttendanceList& listAttends);
bool loadStudentCourseInformationList(const string& filePath, StudentCourseInformation*& listInfo, int& countStudent);
void releaseStudentCourseInformationList(void* listInfo, const int& countStudent);

void saveStudent(ofstream& fout, const Student& st);
bool getInputCourseFromSemester(const string& academicYear, const string& semester, string& ClassName,
	Course& course, Course*& listCourses, int& countCourse);

bool saveListCourses(const string& filePath, Course* listCourses, const int& countCourse);
void saveCourse(ofstream& fout, Course& course);

bool isEqualCourseId(void* val1, void* val2);
void showListScoreboardsOfCourse(StudentCourseInformation*& listInfo, const int& countStudent);
void showAttendaceListOfCourse(StudentCourseInformation*& listInfo, const int& countStudent);

bool saveStudentCourseInformationList(const string& filePath, StudentCourseInformation* listInfo, const int& countStudent);