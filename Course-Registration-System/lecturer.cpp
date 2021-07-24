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
void editGradeStudent(const string& academicYear, const string& semester, const Lecturer& lec)
{
	string filePath;
	StudentCourseInformation* listInfo = nullptr;
	Student st;
	Course course;
	Scoreboard newScoreboard;
	int countStudent = 0;

	if (getInputCourseOfLecturer(academicYear, semester, course, lec))
	{
		filePath = createCourseDirectoryWithFileName(academicYear, semester, course.ClassName, course.courseId, "txt");
		if (loadStudentCourseInformationList(filePath, listInfo, countStudent))
		{
			viewStudentListFromCourse(listInfo, countStudent);
			cout << "Enter a number between 1 and " << countStudent << " or 0 if no student are selected." << endl;
			int idx = getChoice(0, countStudent) - 1;

			if (idx != NOT_FOUND)
			{
				cout << "Do you want to edit score?(0/1)" << endl;
				bool flag = getChoice(0, 1);

				if (flag) {
					char delim;

					cout << "\n |" << setfill('-') << setw(104) << "-" << "|" << endl;
					cout << setfill(' ');
					viewScoreboardOfStudent(listInfo[idx].st, listInfo[idx].scoreList);
					cout << " |" << setfill('-') << setw(104) << "-" << "|\n" << endl;
					cout << setfill(' ');

					cout << "Enter a new scoreboard (midterm, final, bonus, total separated by commas): ";
					cin >> newScoreboard.midterm >> delim >> newScoreboard._final >> delim >> newScoreboard.bonus >> delim >> newScoreboard.total;

					listInfo[idx].scoreList = newScoreboard;

					if (saveStudentCourseInformationList(filePath, listInfo, countStudent))
						cout << "Scoreboard has been updated." << endl;
					else
						cout << "Update scoreboard failed." << endl;

					system("pause");
				}
			}

			releaseStudentCourseInformation(listInfo, countStudent);
		}
		else
			cout << "Can not open course file" << endl;
	}
}
void viewListCourses(const string& academicYear, const string& semester, Lecturer& lec)
{
	string filePath, filePathOfClassName = PATH_DATA;
	string* listClassName = nullptr;
	Course* listCourses = nullptr;
	int countCourse = 0, countClassName = 0;

	filePathOfClassName += "Class.txt";
	if (loadListClassName(filePathOfClassName, listClassName, countClassName)) {
		for (int i = 0; i < countClassName; i++) {
			filePath = createCourseDirectoryWithFileName(academicYear, semester, listClassName[i], "Schedule", "txt");

			if (loadListCourses(filePath, listCourses, countCourse))
			{
				cout << "\nCourses of class " << listClassName[i] << ":\n" << endl;

				if (countCourse != 0)
				{
					int idx = 0;

					cout << "|" << setfill('-') << setw(121) << "-" << "|" << endl;
					cout << setfill(' ');

					cout << "| " << setw(10) << left << " Credits" << " | " << setw(50) << left << "Course name" << " | "
						<< setw(15) << left << "Course ID" << " | " << setw(35) << left << "Full name" << " |" << endl;

					cout << "|" << setfill('-') << setw(121) << "-" << "|" << endl;
					cout << setfill(' ');

					for (int i = 0; i < countCourse; i++, idx++)
					{
						if (isEqualLecturer(&lec, &listCourses[i].lecturer))
						{
							cout << "| " << setw(3) << right << listCourses[i].NumberOfCredits
								<< "   | " << setw(50) << left << listCourses[i].courseName
								<< " | " << setw(15) << left << listCourses[i].courseId << " | "
								<< setw(35) << left << listCourses[i].lecturer.info.fullName << " |" << endl;

							cout << "|" << setfill('-') << setw(121) << "-" << "|" << endl;
							cout << setfill(' ');
						}
					}
				}
				else {
					cout << "\nClass " << listClassName[i] << " does not have a course of lecturer "
						<< lec.info.fullName << endl;
				}

				delete[] listCourses;
			}
			else
				cout << "\nCan not open course file of class " << listClassName[i] << "." << endl;
		}

		delete[] listClassName;
	}
	else
		cout << "Can not open file containing list of class names." << endl;
}
void viewScoreboardOfCourse(const string& academicYear, const string& semester, const Lecturer& lec)
{
	string filePath;
	Course course;
	StudentCourseInformation* listInfo = nullptr;
	int countStudent = 0;

	if (getInputCourseOfLecturer(academicYear, semester, course, lec))
	{
		filePath = createCourseDirectoryWithFileName(academicYear, semester, course.ClassName, course.courseId, "txt");
		if (loadStudentCourseInformationList(filePath, listInfo, countStudent))
		{
			cout << "Scoreboard of class " << course.ClassName << " (Course ID: " << course.courseId << "): \n" << endl;
			showListScoreboardsOfCourse(listInfo, countStudent);
			releaseStudentCourseInformation(listInfo, countStudent);
		}
		else
			cout << "Can not open course file" << endl;
	}
}
void viewAttendanceListOfCourseForLecturer(const string& academicYear,
	const string& semester, Lecturer& lec)
{
	string filePath;
	Course course;
	StudentCourseInformation* listInfo = nullptr;
	int countStudent = 0;

	if (getInputCourseOfLecturer(academicYear, semester, course, lec))
	{
		filePath = createCourseDirectoryWithFileName(academicYear, semester, course.ClassName, course.courseId, "txt");
		if (loadStudentCourseInformationList(filePath, listInfo, countStudent))
		{
			cout << "Attendance list of class " << course.ClassName << " (Course ID: " << course.courseId << "): \n" << endl;
			showAttendaceListOfCourse(listInfo, countStudent);

			releaseStudentCourseInformation(listInfo, countStudent);
		}
		else
			cout << "Can not open course file" << endl;
	}
}
void editAttendance(const string& academicYear, const string& semester, const Lecturer& lec)
{
	string filePath;
	StudentCourseInformation* listInfo = nullptr;
	Course course;
	Student* listStudents = nullptr, st;
	int countStudent = 0;

	if (getInputCourseOfLecturer(academicYear, semester, course, lec))
	{
		filePath = createCourseDirectoryWithFileName(academicYear, semester, course.ClassName, course.courseId, "txt");
		if (loadStudentCourseInformationList(filePath, listInfo, countStudent))
		{
			viewStudentListFromCourse(listInfo, countStudent);
			cout << "Enter a number between 1 and " << countStudent << " or 0 if no student are selected." << endl;
			int idx = getChoice(0, countStudent) - 1;

			if (idx != NOT_FOUND)
			{
				bool flag;
				do
				{
					system("cls");
					cout << "\nAttendance list of " << listInfo[idx].st.info.fullName
						<< " (" << listInfo[idx].st.id << "):" << endl;
					viewAttendanceListStudent(listInfo[idx].attendList);

					cout << "Do you want to edit attendances?(0/1)" << endl;
					flag = getChoice(0, 1);

					if (flag)
					{
						int choice;
						cout << "Enter the number corresponding to the date:" << endl;
						choice = getChoice(1, listInfo[idx].attendList.countDate);

						bool confirm;
						cout << "Do you want to change the status of this date?(0/1)" << endl;
						confirm = getChoice(0, 1);

						if (confirm)
						{
							listInfo[idx].attendList.status[choice - 1] = !listInfo[idx].attendList.status[choice - 1];
							cout << "Change check in status successfully!" << endl;

							system("pause");
						}
					}
				} while (flag);

				saveStudentCourseInformationList(filePath, listInfo, countStudent);
			}

			releaseStudentCourseInformation(listInfo, countStudent);
		}
		else
			cout << "Can not open course file" << endl;
	}
}
void* allocListLecturers(const int& countLecturer)
{
	Lecturer* arr = new Lecturer[countLecturer];
	return arr;
}
void importScoreboardsOfCourse(const string& academicYear, const string& semester, const Lecturer& lec)
{
	string filePath, filePathToOutputData;
	Course course;

	if (getInputCourseOfLecturer(academicYear, semester, course, lec))
	{
		StudentCourseInformation* listInfo = nullptr, * currentListInfo = nullptr;
		int countStudent = 0, countCurrentStudent = 0;

		cout << "Path of the csv file: ";
		cin.ignore();
		getline(cin, filePath);

		if (loadListScoreboardFromCsv(filePath, listInfo, countStudent))
		{
			filePathToOutputData = createCourseDirectoryWithFileName(academicYear, semester, course.ClassName, course.courseId, "txt");

			if (loadStudentCourseInformationList(filePathToOutputData, currentListInfo, countCurrentStudent))
			{
				for (int i = 0; i < countCurrentStudent; i++)
					currentListInfo[i].scoreList = listInfo[i].scoreList;

				if (saveStudentCourseInformationList(filePathToOutputData, currentListInfo, countCurrentStudent))
					cout << "Import successful." << endl;
				else
					cout << "Import failed." << endl;

				releaseStudentCourseInformation(currentListInfo, countCurrentStudent);
			}

			delete[] listInfo;
		}
	}
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

void releaseListlecturers(void* listLecturers, const int& countLecturer)
{
	if (listLecturers)
	{
		Lecturer* arr = (Lecturer*)listLecturers;
		delete[] arr;
	}
}

bool loadListLecturers(const string& filePath, Lecturer*& listLecturers, int& countLecturer)
{
	ifstream fin(filePath);

	if (!fin.is_open())
		return false;

	fin >> countLecturer;
	fin.ignore();
	listLecturers = new Lecturer[countLecturer];

	for (int i = 0; i < countLecturer; i++)
	{
		loadLecturer(fin, listLecturers[i]);
		fin.ignore();
	}

	fin.close();
	return true;
}

void loadLecturer(ifstream& fin, Lecturer& lec)
{
	getline(fin, lec.info.acc.username);
	getline(fin, lec.info.acc.password);
	getline(fin, lec.info.fullName);
	getline(fin, lec.degree);
	fin >> lec.info.gender;
}

void saveLecturer(ofstream& fout, const Lecturer& lec)
{
	fout << lec.info.acc.username << endl << lec.info.acc.password << endl;
	fout << lec.info.fullName << endl << lec.degree << endl;
	fout << lec.info.gender << endl;
}

bool saveListLecturers(const string& filePath, Lecturer*& listLecturers, int& countLecturer)
{
	ofstream fout(filePath);

	if (!fout.is_open())
		return false;

	fout << countLecturer << endl;

	for (int i = 0; i < countLecturer; i++)
		saveLecturer(fout, listLecturers[i]);

	fout.close();
	return true;
}

void loadScoreboardFromCsv(ifstream& fin, StudentCourseInformation& scoreInfo)
{
	char comma;

	getline(fin, scoreInfo.st.id, DELIMIT_CSV);
	getline(fin, scoreInfo.st.info.fullName, DELIMIT_CSV);
	fin >> scoreInfo.scoreList.midterm >> comma;
	fin >> scoreInfo.scoreList._final >> comma;
	fin >> scoreInfo.scoreList.bonus >> comma;
	fin >> scoreInfo.scoreList.total;
}