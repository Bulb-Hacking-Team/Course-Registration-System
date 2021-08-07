#ifndef GENERAL_H_
#define GENERAL_H_
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm> // use function min()
#include <ctime>

#pragma pack(1)

#define NOT_FOUND		   -1
#define MAX_PWD_SIZE	   40
#define MIN_PWD_SIZE 	   8
#define MAX_SIZE 		   100
#define DELIMIT_TXT 	   '\n'
#define DELIMIT_CSV 	   ','
#define DEFAULT_PASSWORD   "12345678"
#define PATH_DATA		   "G:/output/"

using namespace std;

enum Gender { MALE, FEMALE };
enum DayOfWeek { SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };


struct Scoreboard
{
	double midterm, _final, bonus, total;
};

struct Time
{
	int hour, minute;
};

struct Date
{
	int day, month, year;
};

struct AttendanceList {
	Date* dateList;
	Time startTime, endTime;
	int countDate;
	bool* status;
};

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

struct Lecturer
{
	GeneralInformation info;
	string degree;
};

struct Schedule {
	string courseId, courseName, ClassName, room;
	Time startTime, endTime;
	int dayOfWeek;
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

struct StudentCourseInformation
{
	Student st;
	Scoreboard scoreList;
	AttendanceList attendList;
	bool status;
};

void resetPassword(Student& st);

Date nextWeek(const Date& dt);

string toString(const Date& dt, const char& delim = '-');

int convertWeekdayStringToNumber(const string& dayOfWeek);

string convertWeekdayNumberToString(const int& dayOfWeek);

int calcNumberOfWeeks(const Course& course);

/*
 * Returns 1 if dt2 is greater than dt1.
 * Returns 0 if dt2 is equal to dt1.
 * Otherwise returns -1.
 */
int compareTwoDates(const Date& dt1, const Date& dt2);

bool isLeapYear(const int& year);

bool checkPassword(const string& password);

bool checkElementInArray(void* arr, const int& numOfElements, const int& sizeItem,
	void* key, bool (*cmp)(void*, void*));

// Returns the number of days in a month.
int getDayInMonth(const int& year, const int& month);

// Get real time on the system.
void getCurrentDateAndTime(Date& dt, Time& t);

// Display the list of available classes.
// Returns the class name chosen by the user.
string getInputClassName();

string getInputPassword();

bool getInputGender();

string getInputCourseID();

string getInputSemester();

int getChoice(const int& minValue, const int& maxValue);

bool isEqualString(void* str1, void* str2);

bool ascendingString(void* str1, void* str2);

void* allocArrayString(const int& sz);

void copyString(void* str1, void* str2);

void releaseArrayString(void* arrString, const int& sz);

/*
 * Nối các chuỗi con lại thành một chuỗi ngăn cách nhau bởi một kí tự.
 *
 * Param arrString: mảng chứa các chuỗi con để nối lại thành một chuỗi.
 * Param delim: kí tự để ngăn cách giữa các chuỗi con khi nối lại thành một chuỗi.
 * Param numOfElements: số lượng phần tử của mảng các chuỗi con.
 *
 * Trả về một chuỗi sau khi được nối lại từ các chuõi con của mảng và ngăn cách bởi một kí tự.
 */
string ArrayStringToString(string*& arrString, const int& numOfElements, const char& delim);

/*
 * Tách một chuỗi thành mảng các chuỗi con, dấu hiệu để tách là một kí tự.
 *
 * Param str: chuỗi ban đầu muốn tách.
 * Param delim: kí tự để phân tách chuỗi ban đầu thành mảng các chuỗi con.
 * Param numOfElements: số lượng phần tử của mảng sau khi đã được tách ra từ chuỗi ban đầu.
 *
 * Trả về địa chỉ của mảng các chuỗi con, trả về null nếu không tách được chuỗi con nào.
 */
string* StringToArrayString(const string& str, const char& delim, int& numOfElements);

// Returns true if ClassName1 greater than ClassName2; otherwise returns false.
// So sánh theo thứ tự từ điển.
bool ascendingClassName(void* ClassName1, void* ClassName2);

void showListClassName(string*& listClassName, const int& countClassName);

void viewScoreboardOfStudent(const Student& st, const Scoreboard& score);

void viewAttendanceListStudent(const AttendanceList& attendList);

void viewStudent(const Student& st);

void showListCourses(Course* listCourses, const int& countCourse, const string& ClassName);

// Read a list of class names from file.
// Mảng listClassName sẽ được cấp phát bên trong hàm này.
// Mảng listClassName phải là mảng động.
bool loadListClassName(const string& filename, string*& listClassName, int& countClassName);

// Write a list of class names from file.
// Mảng listClassName phải có dữ liệu trước (đã cấp phát rồi).
// Mảng listClassName có thể là mảng động hoặc mảng tĩnh.
// Hàm này không giải phóng mảng nếu là mảng động, phải tự giải phóng.
bool saveListClassName(const string& filename, string* listClassName, const int& countClassName);

void loadStaff(ifstream& fin, Staff& s);

bool loadListStaffs(const string& filePath, Staff*& listStaffs, int& countStaff);

void saveStaff(ofstream& fout, const Staff& s);

bool saveListStaffs(const string& filePath, Staff*& listStaffs, const int& countStaff);

void releaseAttendanceList(AttendanceList& attendList);

void releaseStudentCourseInformation(StudentCourseInformation*& listInfo, const int& countStudent);

/*
 * Change the size of the array.
 *
 * Param oldSize: number of elements in the old array (= newSize sau khi kết thúc hàm).
 * Param newSize: number of elements in the new array.
 * Param sizeItem: size of an element.
 * Param alloc: used for dynamic allocation.
 * Param copyElement: used for copy value of element from old array to new array.
 * Param release: used to release dynamic arrays.
 *
 * Returns the address of the new array.
 */
void* resizeArray(void* arr, int& oldSize, const int& newSize, const int& sizeItem,
	void* (*alloc)(const int&), void (*copyElement)(void*, void*), void (*release)(void*, const int&));

/*
 * Add an element to the end of the array.
 *
 * Param numOfElements: number of elements (tăng thêm 1 sau khi kết thúc hàm).
 * Param sizeItem: size of an element.
 * Param val: address of value to add.
 * Param alloc: used for dynamic allocation.
 * Param copyElement: used for copy value of element from old array to new array.
 * Param release: used to release dynamic arrays.
 *
 * Returns the address of the new array.
 */
void* pushBackArray(void* arr, int& numOfElements, const int& sizeItem, void* val,
	void* (*alloc)(const int&), void (*copyElement)(void*, void*), void (*release)(void*, const int&));

/*
 * Delete an element with value is val (chỉ xóa giá trị đầu tiên xuất hiện).
 *
 * Param numOfElements: number of elements (giảm 1 nếu như đã xóa phần tử).
 * Param sizeItem: size of an element.
 * Param val: giá trị cần được xóa (phần tử này không xuất hiện sẽ trả về mảng ban đầu).
 * Param alloc: used for dynamic allocation.
 * Param copyElement: used for copy value of element from old array to new array.
 * Param release: used to release dynamic arrays.
 *
 * Returns the address of the new array.
 */
void* deleteElementWithValue(void* arr, int& numOfElements, const int& sizeItem, void* val, void* (*alloc)(const int&),
	void (*copyElement)(void*, void*), void (*release)(void*, const int&), bool (*equalValue)(void*, void*));

/*
 * Delete an element with value is val (chỉ xóa giá trị đầu tiên xuất hiện).
 *
 * Param numOfElements: number of elements (giảm 1 nếu như đã xóa phần tử).
 * Param sizeItem: size of an element.
 * Param pos: chỉ số của phần tử cần xóa (chỉ số không hợp lệ sẽ trả về mảng ban đầu).
 * Param alloc: used for dynamic allocation.
 * Param copyElement: used for copy value of element from old array to new array.
 * Param release: used to release dynamic arrays.
 *
 * Returns the address of the new array.
 */
void* deleteElementAtPosition(void* arr, int& numOfElements, const int& sizeItem, const int& pos, void* (*alloc)(const int&),
	void (*copyElement)(void*, void*), void (*release)(void*, const int&));

/*
 * Find an element in the array.
 *
 * Param n: number of elements.
 * Param sizeItem: size of an element.
 * Param key: address of value to find.
 * Param cmp: is function pointer, to compare key value with each element in the array.
 *
 * Returns a non-negative number that is the index of the element in the array; otherwise returns -1 (NOT_FOUND).
 */
int findValue(void* arr, const int& n, const int& sizeItem, void* key, bool (*cmp)(void*, void*));

/*
 * Sắp xếp mảng theo một thứ tự được định nghĩa thông qua con trỏ hàm.
 *
 * Param n: number of elements.
 * Param sizeItem: size of an element.
 * Param cmp: is function pointer, để so sánh các phần tử để sắp xếp theo một thứ tự nhất định.
 */
void sortArray(void* arr, const int& n, const int& sizeItem, bool (*cmp)(void*, void*));
int findValue_AcademicYear(string* listAcademicYear, int countAY, string academicYear);
#endif