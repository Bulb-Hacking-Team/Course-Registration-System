#include "staff.h"

bool loadListClassName(const string& filename, string*& listClassName, int& countClassName)
{
	ifstream fin(filename);

	if (!fin.is_open())
		return false;

	fin >> countClassName;
	fin.ignore();

	if (countClassName > 0)
	{
		listClassName = new string[countClassName];

		for (int i = 0; i < countClassName; i++)
			getline(fin, listClassName[i]);
	}

	fin.close();
	return true;
}
bool isEqualAcademicYears(void* year1, void* year2)
{
	return isEqualString(year1, year2);
}
bool loadAcademicYearsAndSemester(const string& filePath, string*& listAcademicYears, string*& listSemesters, int& countAcademicYears)
{
	ifstream fin(filePath);

	if (!fin.is_open())
		return false;

	fin >> countAcademicYears;
	fin.ignore();

	if (countAcademicYears != 0)
	{
		listAcademicYears = new string[countAcademicYears];
		listSemesters = new string[countAcademicYears];

		for (int i = 0; i < countAcademicYears; i++)
		{
			getline(fin, listAcademicYears[i]);
			getline(fin, listSemesters[i]);
		}
	}

	fin.close();
	return true;
}