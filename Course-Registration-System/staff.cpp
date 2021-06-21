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
void viewAcademicYearsAndSemester() 
{
	string filePath(PATH_DATA);
	string* listAcademicYears = nullptr, * listSemesters = nullptr;
	int countAcademicYears = 0;

	filePath += "SchoolYear.txt";

	if (loadAcademicYearsAndSemester(filePath, listAcademicYears, listSemesters, countAcademicYears)) {
		cout << "|" << setfill('-') << setw(43) << "-" << "|" << endl;
		cout << setfill(' ');

		cout << "| " << setw(4) << left << "No" << " | " << setw(16) << left << "Academic Years" << " | "
			<< setw(15) << left << "Semesters" << " |" << endl;

		cout << "|" << setfill('-') << setw(43) << "-" << "|" << endl;
		cout << setfill(' ');

		for (int i = 0; i < countAcademicYears; i++) {
			cout << "| " << setw(4) << left << i + 1 << " | " << setw(16) << left << listAcademicYears[i]
				<< " | " << setw(15) << left << listSemesters[i] << " |" << endl;

			cout << "|" << setfill('-') << setw(43) << "-" << "|" << endl;
			cout << setfill(' ');
		}

		delete[] listSemesters;
		delete[] listAcademicYears;
	}
	else
		cout << "Can not open file." << endl;
}

void showListClassName(string*& listClassName, const int& countClassName)
{
	cout << "List of classes:" << endl;

	cout << "|" << setfill('-') << setw(19) << "-" << "|" << endl;
	cout << setfill(' ');

	cout << "| " << setw(4) << left << "No" << " | " << setw(10) << "Class name" << " |" << endl;

	cout << "|" << setfill('-') << setw(19) << "-" << "|" << endl;
	cout << setfill(' ');

	for (int i = 0; i < countClassName; i++)
	{
		cout << "| " << setw(4) << left << i + 1
			<< " | " << setw(10) << left << listClassName[i] << " |" << endl;

		cout << "|" << setfill('-') << setw(19) << "-" << "|" << endl;
		cout << setfill(' ');
	}
}