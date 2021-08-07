#include "general.h"
void saveStaff(ofstream& fout, const Staff& s) {
	fout << s.info.acc.username << endl << s.info.acc.password << endl
		<< s.info.fullName << endl << s.info.gender << endl;
}

bool saveListStaffs(const string& filePath, Staff*& listStaffs, const int& countStaff)
{
	ofstream fout(filePath);

	if (!fout.is_open())
		return false;

	fout << countStaff << endl;
	for (int i = 0; i < countStaff; i++)
		saveStaff(fout, listStaffs[i]);

	fout.close();
	return true;
}

string getInputClassName()
{
	string* listClassName = nullptr;
	string filePath = PATH_DATA, result;
	int countClassName = 0, choice;

	if (!loadListClassName(filePath + "Class.txt", listClassName, countClassName))
		return "";

	showListClassName(listClassName, countClassName);

	choice = getChoice(1, countClassName);
	result = listClassName[choice - 1];

	delete[] listClassName;
	return result;
}
void* pushBackArray(void* arr, int& numOfElements, const int& sizeItem, void* val, void* (*alloc)(const int&), void (*copyElement)(void*, void*), void (*release)(void*, const int&))
{
	void* newArray = resizeArray(arr, numOfElements, numOfElements + 1, sizeItem, alloc, copyElement, release);
	int distance = (numOfElements - 1) * sizeItem;

	copyElement((char*)newArray + distance, val);

	return newArray;
}
void* resizeArray(void* arr, int& oldSize, const int& newSize, const int& sizeItem,
	void* (*alloc)(const int&), void (*copyElement)(void*, void*), void (*release)(void*, const int&))
{
	void* newArray = alloc(newSize);
	int sz = min(oldSize, newSize), distance;

	for (int i = 0; i < sz; i++)
	{
		distance = i * sizeItem;
		copyElement((char*)newArray + distance, (char*)arr + distance);
	}

	release(arr, oldSize);
	oldSize = newSize;

	return newArray;
}
bool getInputGender()
{
	bool gen = FEMALE, flag;
	string s;

	do
	{
		flag = true;

		getline(cin, s);
		for (int i = 0; i < s.length(); i++)
			s[i] = tolower(s[i]);

		if (s != "male" && s != "female") {
			flag = false;
			cout << "Invalid!!. Please enter again." << endl;
		}
	} while (!flag);

	if (s == "male")
		gen = MALE;

	return gen;
}
bool checkElementInArray(void* arr, const int& numOfElements, const int& sizeItem,
	void* key, bool (*cmp)(void*, void*))
{
	if (arr == nullptr)
		return false;

	int index = findValue(arr, numOfElements, sizeItem, key, cmp);
	return (index != NOT_FOUND);
}
int findValue(void* arr, const int& n, const int& sizeItem, void* key, bool (*cmp)(void*, void*))
{
	if (arr != nullptr)
	{
		char* temp = (char*)arr;

		for (int i = 0; i < n; i++, temp += sizeItem)
			if (cmp(temp, key))
				return i;
	}

	return NOT_FOUND;
}
int findValue_AcademicYear(string* listAcademicYear, int countAY, string academicYear) {
	for (int i = 0; i < countAY; i++)
	{
		if (listAcademicYear[i] == academicYear)
		{
			return i;
		}
	}
	return NOT_FOUND;
}
//semester
bool ascendingString(void* str1, void* str2)
{
	return (*(string*)str1 > *(string*)str2);
}
void* allocArrayString(const int& sz)
{
	string* arrString = nullptr;

	if (sz > 0)
		arrString = new string[sz];

	return arrString;
}

void copyString(void* str1, void* str2) {
	*(string*)str1 = *(string*)str2;
}

void releaseArrayString(void* arrString, const int& sz) {
	if (arrString != nullptr)
		delete[](string*)arrString;
}
bool isEqualString(void* str1, void* str2)
{
	return (*(string*)str1 == *(string*)str2);
}
string* StringToArrayString(const string& str, const char& delim, int& numOfElements)
{
	string* temp = new string[MAX_SIZE], * arrString = nullptr;
	int start = 0, index, len;

	numOfElements = 0;

	do
	{
		index = str.find(delim, start);
		len = (index == string::npos) ? (index) : (index - start);

		temp[numOfElements++] = str.substr(start, len);

		start = (index == string::npos) ? (index) : (index + 1);
	} while (start != string::npos);

	if (numOfElements != 0)
	{
		arrString = new string[numOfElements];
		for (int i = 0; i < numOfElements; i++)
			arrString[i] = temp[i];
	}

	delete[] temp;
	return arrString;
}
void sortArray(void* arr, const int& n, const int& sizeItem, bool (*cmp)(void*, void*))
{
	char* data_i, * data_pos, * data_j, * temp;
	temp = new char[sizeItem];

	for (int i = 0; i < n - 1; i++)
	{
		data_i = (char*)arr + (i * sizeItem);
		data_pos = data_i;

		for (int j = i + 1; j < n; j++)
		{
			data_j = (char*)arr + (j * sizeItem);

			if (cmp(data_pos, data_j))
				data_pos = data_j;
		}

		if (data_pos != data_i) {
			memmove_s(temp, sizeItem, data_i, sizeItem);
			memmove_s(data_i, sizeItem, data_pos, sizeItem);
			memmove_s(data_pos, sizeItem, temp, sizeItem);
		}
	}

	delete[] temp;
}
string ArrayStringToString(string*& arrString, const int& numOfElements, const char& delim)
{
	string str = "";
	for (int i = 0; i < numOfElements; i++)
		str += arrString[i] + delim;

	str.pop_back();
	return str;
}
//
void releaseAttendanceList(AttendanceList& attendList)
{
	delete[] attendList.dateList;
	delete[] attendList.status;
}
void releaseStudentCourseInformation(StudentCourseInformation*& listInfo, const int& countStudent)
{
	for (int i = 0; i < countStudent; i++)
		releaseAttendanceList(listInfo[i].attendList);

	delete[] listInfo;
}

//
int calcNumberOfWeeks(const Course& course)
{
	Date startDate = course.startDate;
	int count = 0;

	while (compareTwoDates(startDate, course.endDate) >= 0)
	{
		startDate = nextWeek(startDate);
		count++;
	}

	return count;
}
bool isLeapYear(const int& year)
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int getDayInMonth(const int& year, const int& month)
{
	int dayInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (isLeapYear(year))
		dayInMonth[1] = 29;

	return dayInMonth[month - 1];
}
Date nextWeek(const Date& dt)
{
	Date result;
	int maxDay = getDayInMonth(dt.year, dt.month);

	result.day = dt.day + 7;
	result.month = dt.month;
	result.year = dt.year;

	if (result.day > maxDay)
	{
		result.day = result.day - maxDay;
		result.month++;

		if (result.month > 12)
		{
			result.year++;
			result.month = 1;
		}
	}

	return result;
}
string getInputCourseID()
{
	string s;
	getline(cin, s);

	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);

	return s;
}
//
string getInputPassword() {
	string password;
	bool flag;

	do {
		flag = true;
		getline(cin, password);

		if (password.length() < 8 || password.length() > 40 || checkPassword(password) == false) {
			cout << "Password lenght is invalid or contains spaces." << endl;
			flag = false;
			cout << "Enter again: ";
		}
	} while (!flag);

	return password;
}
int compareTwoDates(const Date& dt1, const Date& dt2) {
	int result = -1;

	if (dt2.year > dt1.year)
		result = 1;
	else if (dt2.year == dt1.year) {
		if (dt2.month > dt1.month)
			result = 1;
		else if (dt2.month == dt1.month) {
			if (dt2.day > dt1.day)
				result = 1;
			else if (dt2.day == dt1.day)
				result = 0;
		}
	}

	return result;
}
string toString(const Date& dt, const char& delim)
{
	string m, d;

	m = to_string(dt.month);
	m = (m.length() == 2) ? (m) : ("0" + m);

	d = to_string(dt.day);
	d = (d.length() == 2) ? (d) : ("0" + d);

	return to_string(dt.year) + delim + m + delim + d;
}
bool checkPassword(const string& password) {
	for (int i = 0; i < password.length(); i++)
		if (password[i] == ' ')
			return false;
	return true;
}
void getCurrentDateAndTime(Date& dt, Time& t)
{
	time_t realTime = time(nullptr);

	tm* dateAndTime = new tm;
	localtime_s(dateAndTime, &realTime);

	dt = { dateAndTime->tm_mday, dateAndTime->tm_mon + 1, dateAndTime->tm_year + 1900 };
	t = { dateAndTime->tm_hour, dateAndTime->tm_min };
	cout << dt.day << " " << dt.month << " " << dt.year << " " << t.hour << " " << t.minute;
	delete dateAndTime;
}
void viewAttendanceListStudent(const AttendanceList& attendList)
{
	string status;

	cout << "|" << setfill('-') << setw(28) << "-" << "|" << endl;
	cout << setfill(' ');

	cout << "|" << setw(5) << left << " No" << "| " << setw(12) << "    DATE    " << "|" << setw(8) << " STATUS " << "|" << endl;
	cout << "|" << setfill('-') << setw(28) << "-" << "|" << endl;
	cout << setfill(' ');

	for (int i = 0; i < attendList.countDate; i++)
	{
		status = "";
		cout << "| " << setw(4) << left << i + 1 << "| " << setw(12) << left << toString(attendList.dateList[i]) << "|";

		if (attendList.status[i])
			status = "X";

		cout << setw(4) << right << status << setw(5) << right << "|" << endl;
		cout << "|" << setfill('-') << setw(28) << "-" << "|" << endl;
		cout << setfill(' ');
	}
}
int convertWeekdayStringToNumber(const string& dayOfWeek)
{
	if (dayOfWeek == "MON")
		return MONDAY;
	else if (dayOfWeek == "TUE")
		return TUESDAY;
	else if (dayOfWeek == "WED")
		return WEDNESDAY;
	else if (dayOfWeek == "THU")
		return THURSDAY;
	else if (dayOfWeek == "FRI")
		return FRIDAY;
	else if (dayOfWeek == "SAT")
		return SATURDAY;
	return SUNDAY;
}
//import class 
bool ascendingClassName(void* ClassName1, void* ClassName2)
{
	return (*(string*)ClassName1 > *(string*)ClassName2);
}

bool saveListClassName(const string& filename, string* listClassName, const int& countClassName)
{
	ofstream fout(filename);

	if (!fout.is_open())
		return false;

	if (countClassName > 1)
		sortArray(listClassName, countClassName, sizeof(string), ascendingClassName);

	fout << countClassName << endl;
	for (int i = 0; i < countClassName; i++)
		fout << listClassName[i] << endl;

	fout.close();
	return true;
}
string convertWeekdayNumberToString(const int& dayOfWeek)
{
	switch (dayOfWeek)
	{
	case MONDAY:
		return "MONDAY";
	case TUESDAY:
		return "TUESDAY";
	case WEDNESDAY:
		return "WEDNESDAY";
	case THURSDAY:
		return "THURSDAY";
	case FRIDAY:
		return "FRIDAY";
	case SATURDAY:
		return "SATURDAY";
	case SUNDAY:
		return "SUNDAY";
	default:
		return "";
	}
}