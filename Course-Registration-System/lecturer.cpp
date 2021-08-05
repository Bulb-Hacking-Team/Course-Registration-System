#include "leturer.h"

bool isEqualLecturer(void* val1, void* val2)
{
	Lecturer* lec1, * lec2;
	lec1 = (Lecturer*)val1;
	lec2 = (Lecturer*)val2;

	if (lec1->info.acc.username == lec2->info.acc.username)
		return true;

	return false;
}

void* allocListLecturers(const int& countLecturer)
{
	Lecturer* arr = new Lecturer[countLecturer];
	return arr;
}

bool getInputCourseOfLecturer(const string& academicYear, const string& semester, Course& course, Lecturer lec)
{
	string path = PATH_DATA, courseFilePath;
	string* listClassName = nullptr;
	Course* listCourses = nullptr, * tempCourse = nullptr;
	int countClassName = 0, countCourse = 0, count = 0, choice;
	bool res = false;

	if (loadListClassName(path + "Class.txt", listClassName, countClassName))
	{
		tempCourse = new Course[MAX_SIZE];

		for (int i = 0; i < countClassName; i++)
		{
			courseFilePath = createCourseDirectoryWithFileName(academicYear, semester, listClassName[i], "Schedule", "txt");

			if (loadListCourses(courseFilePath, listCourses, countCourse))
			{
				for (int j = 0; j < countCourse; j++)
					if (isEqualLecturer(&listCourses[j].lecturer, &lec))
						tempCourse[count++] = listCourses[j];

				delete[] listCourses;
			}
		}

		if (count != 0)
		{
			cout << "|" << setfill('-') << setw(77) << "-" << "|" << endl;
			cout << setfill(' ');

			cout << "| " << setw(4) << left << "No" << " | " << setw(12) << left << "Class name"
				<< " | " << setw(35) << left << "Course name" << " | " << setw(15) << left << "Course ID" << " |" << endl;

			cout << "|" << setfill('-') << setw(77) << "-" << "|" << endl;
			cout << setfill(' ');

			for (int i = 0; i < count; i++) {
				cout << "| " << setw(4) << left << i + 1 << " | " << setw(12) << left << tempCourse[i].ClassName
					<< " | " << setw(35) << left << tempCourse[i].courseName
					<< " | " << setw(15) << left << tempCourse[i].courseId << " |" << endl;

				cout << "|" << setfill('-') << setw(77) << "-" << "|" << endl;
				cout << setfill(' ');
			}

			choice = getChoice(1, count);
			course = tempCourse[choice - 1];

			res = true;
		}

		delete[] tempCourse;
		delete[] listClassName;
	}

	return res;
}

void copyLecturer(void* lec1, void* lec2)
{
	*(Lecturer*)lec1 = *(Lecturer*)lec2;
}