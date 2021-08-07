#ifndef COURSE_H_
#define COURSE_H_
#include "general.h"

bool isEqualCourseId(void* val1, void* val2);

bool ascendingStudentIdOfCourse(void* val1, void* val2);

/*
 * Create a directory (contain file name) of course.
 *
 * Param argLast: depend on the path you want to create.
 *
 * Trả về một đường dẫn đến file mà tên file dựa vào những tham số đã truyền vào.
 * Return type is string.
 *
 * Ex: PATH_DATA/academicYear-semester-ClassName-argLast.FileExtension    (PATH_DATA has been defined).
 */
string createCourseDirectoryWithFileName(const string& academicYear, const string& semester,
	const string& ClassName, const string& argLast, const string& FileExtension);

// Display the list of available classes and enter the class name from user.
// Display the list of available coursesand enter the course id from the user.
// Hàm này sẽ đọc danh sách các môn học hiện có vào listCourses.
// Hàm không giải phóng bộ nhớ của listCourses.
bool getInputCourseFromSemester(const string& academicYear, const string& semester, string& ClassName,
	Course& course, Course*& listCourses, int& countCourse);


// Initialize a student's attendance list.
void initAttendanceList(AttendanceList& listAttends, const Course& course);

void initAttendanceList(AttendanceList& listAttends, const int& numberOfWeeks);

void initScoreboard(Scoreboard& score, const double& midterm = 0, const double& _final = 0,
	const double& bonus = 0, const double& total = 0);

void copyAttendanceList(AttendanceList& dest, const AttendanceList& src);

void* allocListCourses(const int& countCourse);

void* allocStudentCourseInformationList(const int& countStudent);

void copyCourse(void* lec1, void* lec2);

void copyStudentCourseInformation(void* sci1, void* sci2);

void releaseListCourses(void* listCourses, const int& countCourse);

void releaseStudentCourseInformationList(void* listInfo, const int& countStudent);

void loadCourseFromCsv(ifstream& fin, Course& course);

// Read course information from text file.
void loadCourse(ifstream& fin, Course& course);


// Write course information to text file.
void saveCourse(ofstream& fout, Course& course);


// Read student information from a text file.
void loadStudentFromTxt(ifstream& fin, Student& st);


// Write student information to a text file.
void saveStudent(ofstream& fout, const Student& st);


// Read a scoreboard of a student from csv or txt file.
void loadScoreboard(ifstream& fin, Scoreboard& scoreboard, const string& FileExtension);


// Save a scoreboard of a student to a txt file.
void saveScoreboard(ofstream& fout, const Scoreboard& scoreboard);


// Read a student's attendance list from a txt file.
void loadAttendanceList(ifstream& fin, AttendanceList& listAttends);


// Save a student's attendance list to a txt file.
void saveAttendanceList(ofstream& fout, const AttendanceList& listAttends);

bool loadListCoursesFromCsv(const string& filePath, Course*& listCourses, int& countCourse);

// Read the list of courses from text file.
// Mảng listCourses sẽ được cấp phát bên trong hàm này.
// Mảng listCourses phải là mảng động.
bool loadListCourses(const string& filePath, Course*& listCourses, int& countCourse);


// Write the list of courses to text file.
// Mảng listCourses phải có dữ liệu trước (đã cấp phát rồi).
// Mảng listCourses có thể là mảng động hoặc mảng tĩnh.
// Hàm này không giải phóng mảng nếu là mảng động, phải tự giải phóng.
bool saveListCourses(const string& filePath, Course* listCourses, const int& countCourse);


bool saveAttendanceListOfCourseToCsv(const string& filePath, StudentCourseInformation* listInfo, const int& countStudent);


// Read the list of students from a course file.
// Mảng listInfo sẽ được cấp phát bên trong hàm này.
// Mảng listInfo phải là mảng động.
bool loadStudentCourseInformationList(const string& filePath, StudentCourseInformation*& listInfo,
	int& countStudent);


// Save the list of students to a course file.
// Mảng listInfo phải có dữ liệu trước (đã cấp phát rồi).
// Mảng listInfo có thể là mảng động hoặc mảng tĩnh.
// Hàm này không giải phóng mảng nếu là mảng động, phải tự giải phóng.
bool saveStudentCourseInformationList(const string& filePath, StudentCourseInformation* listInfo,
	const int& countStudent);

void viewStudentListFromStudentCourseInformationList(StudentCourseInformation* sci, int countStudent);

void showAttendaceListOfCourse(StudentCourseInformation*& listInfo, const int& countStudent);

void showListScoreboardsOfCourse(StudentCourseInformation*& listInfo, const int& countStudent);

#endif