#include "general.h"

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
bool ascendingString(void* str1, void* str2)
{
	return (*(string*)str1 > *(string*)str2);
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
void copyString(void* str1, void* str2) {
	*(string*)str1 = *(string*)str2;
}
void* allocArrayString(const int& sz)
{
	string* arrString = nullptr;

	if (sz > 0)
		arrString = new string[sz];

	return arrString;
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

		// Swap the value of two variables.
		if (data_pos != data_i) {
			memmove_s(temp, sizeItem, data_i, sizeItem);
			memmove_s(data_i, sizeItem, data_pos, sizeItem);
			memmove_s(data_pos, sizeItem, temp, sizeItem);
		}
	}

	delete[] temp;
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
void releaseArrayString(void* arrString, const int& sz) {
	if (arrString != nullptr)
		delete[](string*)arrString;
}
string ArrayStringToString(string*& arrString, const int& numOfElements, const char& delim)
{
	string str = "";
	for (int i = 0; i < numOfElements; i++)
		str += arrString[i] + delim;

	str.pop_back();
	return str;
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

bool ascendingClassName(void* ClassName1, void* ClassName2)
{
	return (*(string*)ClassName1 > * (string*)ClassName2);
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

bool checkPassword(const string& password)
{
	for (int i = 0; i < password.length(); i++)
		if (password[i] == ' ')
			return false;
	return true;
}