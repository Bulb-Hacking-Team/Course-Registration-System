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
void removeCourse(const string& academicYear, const string& semester)
{
	string ClassName, filePath;
	Course* listCourses = nullptr;
	Course key;
	int countCourse, idx, isRemove;

	if (getInputCourseFromSemester(academicYear, semester, ClassName, key, listCourses, countCourse))
	{
		filePath = createCourseDirectoryWithFileName(academicYear, semester, ClassName, "Schedule", "txt");
		idx = findValue(listCourses, countCourse, sizeof(Course), &key, isEqualCourseId);

		if (idx != NOT_FOUND)
		{
			cout << "==> Do you want to delete this course? (Yes: 1, No: 0)" << endl;
			isRemove = getChoice(0, 1);

			if (isRemove)
			{
				listCourses[idx].status = false;
				if (saveListCourses(filePath, listCourses, countCourse - 1))
					cout << "==> Remove successfully." << endl;
				else
					cout << "==> Remove failed." << endl;
			}
		}
		else
			cout << "This course was not found." << endl;

		delete[] listCourses;
	}
}
void showListCourses(Course* listCourses, const int& countCourse, const string& ClassName)
{
	cout << "Courses of class " << ClassName << ":\n" << endl;

	if (countCourse != 0)
	{
		int idx = 0;

		cout << "|" << setfill('-') << setw(116) << "-" << "|" << endl;
		cout << setfill(' ');

		cout << "| " << setw(5) << left << " No" << " | " << setw(50) << left << "Course name" << " | "
			<< setw(15) << left << "Course ID" << " | " << setw(35) << left << "Full name" << " |" << endl;

		cout << "|" << setfill('-') << setw(116) << "-" << "|" << endl;
		cout << setfill(' ');

		for (int i = 0; i < countCourse; i++, idx++)
		{
			if (listCourses[idx].status)
			{
				cout << "| " << setw(3) << right << idx + 1 << "   | " << setw(50) << left << listCourses[i].courseName
					<< " | " << setw(15) << left << listCourses[i].courseId << " | "
					<< setw(35) << left << listCourses[i].lecturer.info.fullName << " |" << endl;

				cout << "|" << setfill('-') << setw(116) << "-" << "|" << endl;
				cout << setfill(' ');
			}
			else
				i--;
		}
	}
	else
		cout << "There are no courses available." << endl;
}
