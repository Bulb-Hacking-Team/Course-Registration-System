#ifndef COURSE_H_
#define COURSE_H_
#include "general.h"
string createCourseDirectoryWithFileName(const string& academicYear, const string& semester, const string& ClassName, const string& argLast, const string& FileExtension);
void loadCourse(ifstream& fin, Course& course);
bool loadListCourses(const string& filePath, Course*& listCourses, int& countCourse);
void initAttendanceList(AttendanceList& listAttends, const int& numberOfWeeks);
void loadScoreboard(ifstream& fin, Scoreboard& scoreboard, const string& FileExtension);
void loadAttendanceList(ifstream& fin, AttendanceList& listAttends);
bool loadStudentCourseInformationList(const string& filePath, StudentCourseInformation*& listInfo, int& countStudent);
void releaseStudentCourseInformationList(void* listInfo, const int& countStudent);

#endif