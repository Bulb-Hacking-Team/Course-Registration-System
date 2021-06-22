#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>

#pragma pack(1)

#define NOT_FOUND		   -1
#define MAX_PWD_SIZE	   40
#define MIN_PWD_SIZE 	   8
#define MAX_SIZE 		   100
#define DELIMIT_TXT 	   '\n'
#define DELIMIT_CSV 	   ','
#define DEFAULT_PASSWORD   "12345678"
#define PATH_DATA		   "D:/hcmus/ktlt/Do_An/Bulb-Hacking-Team-20CTT3/data/output/"

using namespace std;

enum Gender { MALE, FEMALE };
enum DayOfWeek { SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
struct Account
{
	string username, password;
};

struct GeneralInformation
{
	string fullName;
	bool gender;
	Account acc;
};

struct Staff
{
	GeneralInformation info;
};

struct Student
{
	GeneralInformation info;
	string id, dateOfBirth, ClassName;
	bool status;
};

struct Time
{
	int hour, minute;
};

struct Date
{
	int day, month, year;
};

struct Scoreboard
{
	double midterm, _final, bonus, total;
};

struct Schedule
{
	string courseId, courseName, ClassName, room;
	Time startTime, endTime;
	int dayOfWeek;
};

struct Lecturer
{
	GeneralInformation info;
	string degree;
};

struct Course
{
	string courseId, courseName, ClassName, room;
	Lecturer lecturer;
	Date startDate, endDate;
	Time startTime, endTime;
	int NumberOfCredits;
	int dayOfWeek;
	bool status;
};
struct AttendanceList
{
	Date* dateList;
	Time startTime, endTime;
	int countDate;
	bool* status;
};
struct StudentCourseInformation
{
	Student st;
	Scoreboard scoreList;
	AttendanceList attendList;
	bool status;
};

int getChoice(const int& minValue, const int& maxValue);
string getInputPassword();

bool isEqualString(void* str1, void* str2);
string toString(const Date& dt, const char& delim = '-');
bool checkPassword(const string& password);

string* StringToArrayString(const string& str, const char& delim, int& numOfElements);
string convertWeekdayNumberToString(const int& dayOfWeek);
bool loadListClassName(const string& filename, string*& listClassName, int& countClassName);
int findValue(void* arr, const int& n, const int& sizeItem, void* key, bool (*cmp)(void*, void*));
void releaseAttendanceList(AttendanceList& attendList);
void releaseStudentCourseInformation(StudentCourseInformation*& listInfo, const int& countStudent);

string getInputClassName();
void showListClassName(string*& listClassName, const int& countClassName);

void* pushBackArray(void* arr, int& numOfElements, const int& sizeItem, void* val,
	void* (*alloc)(const int&), void (*copyElement)(void*, void*), void (*release)(void*, const int&));

void* resizeArray(void* arr, int& oldSize, const int& newSize, const int& sizeItem,
	void* (*alloc)(const int&), void (*copyElement)(void*, void*), void (*release)(void*, const int&));

void copyString(void* str1, void* str2);
void releaseArrayString(void* arrString, const int& sz);
bool saveListClassName(const string& filename, string* listClassName, const int& countClassName);

bool saveStudentList(const string& filePath, Student* listStudents, const int& countStudent);
void sortArray(void* arr, const int& n, const int& sizeItem, bool (*cmp)(void*, void*));
bool checkElementInArray(void* arr, const int& numOfElements, const int& sizeItem,
	void* key, bool (*cmp)(void*, void*));
void showListCourses(Course* listCourses, const int& countCourse, const string& ClassName);
void viewScoreboardOfStudent(const Student& st, const Scoreboard& score);
void* allocArrayString(const int& sz);

