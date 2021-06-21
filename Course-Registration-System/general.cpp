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