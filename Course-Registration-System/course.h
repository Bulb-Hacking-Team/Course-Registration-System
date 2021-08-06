#pragma once
#include "general.h"

string createCourseDirectoryWithFileName(const string& academicYear, const string& semester, const string& ClassName, const string& argLast, const string& FileExtension);
void loadCourse(ifstream& fin, Course& course);
bool loadListCourses(const string& filePath, Course*& listCourses, int& countCourse);

void initAttendanceList(AttendanceList& listAttends, const Course& course);
void initAttendanceList(AttendanceList& listAttends, const int& numberOfWeeks);

void loadScoreboard(ifstream& fin, Scoreboard& scoreboard, const string& FileExtension);
void loadAttendanceList(ifstream& fin, AttendanceList& listAttends);
void saveAttendanceList(ofstream& fout, const AttendanceList& listAttends);

bool loadStudentCourseInformationList(const string& filePath, StudentCourseInformation*& listInfo, int& countStudent);
void releaseStudentCourseInformationList(void* listInfo, const int& countStudent);

void saveStudent(ofstream& fout, const Student& st);
bool getInputCourseFromSemester(const string& academicYear, const string& semester, string& ClassName,
	Course& course, Course*& listCourses, int& countCourse);

void initScoreboard(Scoreboard& score, const double& midterm = 0, const double& _final = 0, const double& bonus = 0, const double& total = 0);

void* allocListCourses(const int& countCourse);
bool saveListCourses(const string& filePath, Course* listCourses, const int& countCourse);

bool loadListCoursesFromCsv(const string& filePath, Course*& listCourses, int& countCourse);
void loadCourseFromCsv(ifstream& fin, Course& course);
void loadStudentFromTxt(ifstream& fin, Student& st);

void copyCourse(void* lec1, void* lec2);
void saveCourse(ofstream& fout, Course& course);

bool isEqualCourseId(void* val1, void* val2);
void showListScoreboardsOfCourse(StudentCourseInformation*& listInfo, const int& countStudent);

bool saveAttendanceListOfCourseToCsv(const string& filePath, StudentCourseInformation* listInfo, const int& countStudent);
void showAttendaceListOfCourse(StudentCourseInformation*& listInfo, const int& countStudent);

bool saveStudentCourseInformationList(const string& filePath, StudentCourseInformation* listInfo, const int& countStudent);

bool ascendingStudentIdOfCourse(void* val1, void* val2);
void saveScoreboard(ofstream& fout, const Scoreboard& scoreboard);

void releaseListCourses(void* listCourses, const int& countCourse);
