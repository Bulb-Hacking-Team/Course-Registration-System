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
void editCourseName(Course& course)
{
	int check;

	cout << "\nCurrent course name: " << course.courseName << endl;
	cout << "==> Do you want to edit this course's name? (Yes: 1, No: 0)" << endl;
	check = getChoice(0, 1);

	if (check)
	{
		string newName;

		cout << "\nEnter new course name: ";
		cin.ignore();
		getline(cin, newName);

		course.courseName = newName;
	}
}
void editCourseLecturer(Course& course)
{
	int check;

	cout << "\nCurrent course lecturer: " << course.lecturer.info.fullName << endl;
	cout << "==> Do you want to edit this course's lecturer? (Yes: 1, No: 0)" << endl;
	check = getChoice(0, 1);

	if (check) {
		cin.ignore();
		course.lecturer = addNewLecturer();
	}
}
void editDate(Course& course)
{
	int check;

	cout << "\nCurrent course start date: " << toString(course.startDate) << endl;
	cout << "Current course end date: " << toString(course.endDate) << endl;
	cout << "==> Do you want to edit this course's start date and end date? (Yes: 1, No: 0)" << endl;
	check = getChoice(0, 1);

	if (check)
	{
		Date newStartDate, newEndDate;

		cout << "\nEnter new course start date (YYYY MM DD): " << endl;
		cin >> newStartDate.year >> newStartDate.month >> newStartDate.day;

		cout << "\nEnter new course end date (YYYY MM DD): " << endl;
		cin >> newEndDate.year >> newEndDate.month >> newEndDate.day;

		course.startDate = newStartDate;
		course.endDate = newEndDate;
	}
}
void editTime(Course& course)
{
	int check;

	cout << "\nCurrent course start time: " << course.startTime.hour << ":" << course.startTime.minute << endl;
	cout << "Current course start time: " << course.endTime.hour << ":" << course.endTime.minute << endl;
	cout << "==> Do you want to edit this course's start time and end time? (Yes: 1, No: 0)" << endl;
	check = getChoice(0, 1);

	if (check)
	{
		Time newStartTime, newEndTime;

		cout << "\nEnter new course start time (HH MM): " << endl;
		cin >> newStartTime.hour >> newStartTime.minute;

		cout << "\nEnter new course end time (HH MM): " << endl;
		cin >> newEndTime.hour >> newEndTime.minute;

		course.startTime = newStartTime;
		course.endTime = newEndTime;
	}
}
void editRoom(Course& course)
{
	int check;

	cout << "\nCurrent course room: " << course.room << endl;
	cout << "==> Do you want to edit this course's room? (Yes: 1, No: 0)" << endl;
	check = getChoice(0, 1);

	if (check)
	{
		string newRoom;

		cout << "\nEnter new course room: ";
		cin.ignore();
		getline(cin, newRoom);

		course.room = newRoom;
	}
}
void editDayOfWeek(Course& course)
{
	int check;

	cout << "\nCurrent course day of week: " << course.dayOfWeek << endl;
	cout << "==> Do you want to edit this course's day of week? (Yes: 1, No: 0)" << endl;
	check = getChoice(0, 1);

	if (check)
	{
		int newDayOfWeek;

		cout << "\nEnter new course day of week (1: SUNDAY, 2: MONDAY,..., 7: SATURDAY): ";
		newDayOfWeek = getChoice(1, 7);

		course.dayOfWeek = newDayOfWeek;
	}
}
void editAnExistingCourse(const string& academicYear, const string& semester)
{
	string ClassName, filePath;
	Course* listCourses = nullptr;
	Course key;
	int countCourse, idx;

	if (getInputCourseFromSemester(academicYear, semester, ClassName, key, listCourses, countCourse))
	{
		filePath = createCourseDirectoryWithFileName(academicYear, semester, ClassName, "Schedule", "txt");
		idx = findValue(listCourses, countCourse, sizeof(Course), &key, isEqualCourseId);

		if (idx != NOT_FOUND)
		{
			int choice;

			system("cls");

			do
			{
				cout << "|------------------------------|" << endl;
				cout << "|          EDIT COURSE         |" << endl;
				cout << "|------------------------------|" << endl;
				cout << "| No |        Option           |" << endl;
				cout << "|------------------------------|" << endl;
				cout << "| 1  | Course ID               |" << endl;
				cout << "|------------------------------|" << endl;
				cout << "| 2  | Course Name             |" << endl;
				cout << "|------------------------------|" << endl;
				cout << "| 3  | Lecturer                |" << endl;
				cout << "|------------------------------|" << endl;
				cout << "| 4  | Date                    |" << endl;
				cout << "|------------------------------|" << endl;
				cout << "| 5  | Day of week             |" << endl;
				cout << "|------------------------------|" << endl;
				cout << "| 6  | Time                    |" << endl;
				cout << "|------------------------------|" << endl;
				cout << "| 7  | Room                    |" << endl;
				cout << "|------------------------------|" << endl;
				cout << "| 8  | Number of credits       |" << endl;
				cout << "|------------------------------|" << endl;
				cout << "| 9  | Return to previous menu |" << endl;
				cout << "|------------------------------|" << endl;

				choice = getChoice(1, 8);

				switch (choice)
				{
				case 1:
					editCourseID(listCourses[idx], academicYear, semester);
					break;
				case 2:
					editCourseName(listCourses[idx]);
					break;
				case 3:
					editCourseLecturer(listCourses[idx]);
					break;
				case 4:
					editDate(listCourses[idx]);
					break;
				case 5:
					editDayOfWeek(listCourses[idx]);
					break;
				case 6:
					editTime(listCourses[idx]);
					break;
				case 7:
					editRoom(listCourses[idx]);
					break;
				case 8:
					editCredits(listCourses[idx]);
					break;
				case 9:
					break;
				}

				if (choice != 9) {
					system("pause");
					system("cls");
				}
			} while (choice != 9);

			saveListCourses(filePath, listCourses, countCourse);
		}
		else
			cout << "This course was not found." << endl;

		delete[] listCourses;
	}
}
bool ascendingSemester(void* semester1, void* semester2)
{
	return ascendingString(semester1, semester2);
}
void importListCoursesFromCsv(const string& filePath, const string& academicYear, const string& semester)
{
	Course* listCourses = nullptr;
	int countCourse = 0;

	if (loadListCoursesFromCsv(filePath, listCourses, countCourse))
	{
		string fileCourse, fileSchedule;
		int countCourseImportSuccessful = countCourse;

		for (int i = 0; i < countCourse; i++)
		{
			fileCourse = createCourseDirectoryWithFileName(academicYear, semester, listCourses[i].ClassName,
				listCourses[i].courseId, "txt");

			if (!EnrollClassToCourse(fileCourse, listCourses[i]))
				countCourseImportSuccessful--;

			addLecturer(listCourses[i].lecturer);
		}

		fileSchedule = createCourseDirectoryWithFileName(academicYear, semester, listCourses[0].ClassName, "Schedule", "txt");
		if (saveListCourses(fileSchedule, listCourses, countCourse))
			cout << "Import successful (" << countCourseImportSuccessful << " / " << countCourse << ")." << endl;
		else
			cout << "Import failed." << endl;

		delete[] listCourses;
	}
	else
		cout << "Can not open file." << endl;
}
bool isEqualAcademicYears(void* year1, void* year2)
{
	return isEqualString(year1, year2);
}
bool addAcademicYearsAndSemester(string& academicYears, string& semester)
{
	string* listAcademicYears = nullptr, * listSemesters = nullptr;
	string filePath = PATH_DATA;
	int countAcademicYears = 0;
	bool result = false;

	filePath += "SchoolYear.txt";
	if (loadAcademicYearsAndSemester(filePath, listAcademicYears, listSemesters, countAcademicYears))
	{
		int idx = findValue_AcademicYear(listAcademicYears, countAcademicYears, academicYears);
		if (idx == NOT_FOUND)
		{
			int count = countAcademicYears;

			listAcademicYears = (string*)pushBackArray(listAcademicYears, countAcademicYears, sizeof(string),
				&academicYears, allocArrayString, copyString, releaseArrayString);

			listSemesters = (string*)pushBackArray(listSemesters, count, sizeof(string), &semester,
				allocArrayString, copyString, releaseArrayString);

			result = true;
		}
		else if (listSemesters[idx].find(semester) == string::npos)
		{
			listSemesters[idx] += "," + semester;
			result = true;
		}

		saveAcademicYearsAndSemester(filePath, listAcademicYears, listSemesters, countAcademicYears);

		delete[] listSemesters;
		delete[] listAcademicYears;
	}

	return result;
}
void viewScoreboardOfCourse(const string& academicYear, const string& semester)
{
	string ClassName, filePath;
	Course course, * listCourses = nullptr;
	StudentCourseInformation* listInfo = nullptr;
	int countStudent = 0, countCourse = 0;

	if (getInputCourseFromSemester(academicYear, semester, ClassName, course, listCourses, countCourse))
	{
		delete[] listCourses;

		filePath = createCourseDirectoryWithFileName(academicYear, semester, ClassName, course.courseId, "txt");
		if (loadStudentCourseInformationList(filePath, listInfo, countStudent))
		{
			cout << "Scoreboard of class " << ClassName << " (Course ID: " << course.courseId << "): \n" << endl;
			showListScoreboardsOfCourse(listInfo, countStudent);
			releaseStudentCourseInformation(listInfo, countStudent);
		}
		else
			cout << "Can not open course file" << endl;
	}
}
void importCourses(const string& academicYear, const string& semester) {
	string filePath, ClassName;

	cout << "Enter class name: ";
	getline(cin, ClassName);
	cout << "==> Path of the csv file: ";
	getline(cin, filePath);

	importListCoursesFromCsv(filePath, academicYear, semester);
}
bool EnrollClassToCourse(const string& filePath, const Course& course)
{
	StudentCourseInformation* listInfo = nullptr;
	Student* listStudents = nullptr;
	string fileClass;
	int countStudent = 0;
	bool flag = false;

	fileClass = createClassDirectoryWithFileName(course.ClassName);

	if (loadStudentList(fileClass, listStudents, countStudent))
	{
		listInfo = new StudentCourseInformation[countStudent];

		for (int i = 0; i < countStudent; i++)
		{
			initAttendanceList(listInfo[i].attendList, course);
			initScoreboard(listInfo[i].scoreLbool EnrollClassToCourse(const string& filePath, const Course& course)
{
	StudentCourseInformation* listInfo = nullptr;
	Student* listStudents = nullptr;
	string fileClass;
	int countStudent = 0;
	bool flag = false;

	fileClass = createClassDirectoryWithFileName(course.ClassName);

	if (loadStudentList(fileClass, listStudents, countStudent))
	{
		listInfo = new StudentCourseInformation[countStudent];

		for (int i = 0; i < countStudent; i++)
		{
			initAttendanceList(listInfo[i].attendList, course);
			initScoreboard(listInfo[i].scoreList);
			listInfo[i].st = listStudents[i];
			listInfo[i].status = true;
		}

		if (saveStudentCourseInformationList(filePath, listInfo, countStudent))
			flag = true;bool EnrollClassToCourse(const string& filePath, const Course& course)
{
	StudentCourseInformation* listInfo = nullptr;
	Student* listStudents = nullptr;
	string fileClass;
	int countStudent = 0;
	bool flag = false;

	fileClass = createClassDirectoryWithFileName(course.ClassName);

	if (loadStudentList(fileClass, listStudents, countStudent))
	{
		listInfo = new StudentCourseInformation[countStudent];

		for (int i = 0; i < countStudent; i++)
		{
			initAttendanceList(listInfo[i].attendList, course);
			initScoreboard(listInfo[i].scoreList);
			listInfo[i].st = listStudents[i];
			listInfo[i].status = true;
		}

		if (saveStudentCourseInformationList(filePath, listInfo, countStudent))
			flag = true;

		releaseStudentCourseInformation(listInfo, countStudent);
	}

	delete[] listStudents;
	return flag;
}

		releaseStudentCourseInformation(listInfo, countStudent);
	}

	delete[] listStudents;
	return flag;
}ist);
			listInfo[i].st = listStudents[i];
			listInfo[i].status = true;
		}

		if (saveStudentCourseInformationList(filePath, listInfo, countStudent))
			flag = true;

		releaseStudentCourseInformation(listInfo, countStudent);
	}

	delete[] listStudents;
	return flag;
}
void viewAttendanceListOfCourse(const string& academicYear, const string& semester) {
	string ClassName, filePath;
	Course course, * listCourses = nullptr;
	StudentCourseInformation* listInfo = nullptr;
	int countStudent = 0, countCourse = 0;

	if (getInputCourseFromSemester(academicYear, semester, ClassName, course, listCourses, countCourse))
	{
		delete[] listCourses;

		filePath = createCourseDirectoryWithFileName(academicYear, semester, ClassName, course.courseId, "txt");
		if (loadStudentCourseInformationList(filePath, listInfo, countStudent))
		{
			cout << "Attendance list of class " << ClassName << " (Course ID: " << course.courseId << "): \n" << endl;
			showAttendaceListOfCourse(listInfo, countStudent);

			releaseStudentCourseInformation(listInfo, countStudent);
		}
		else
			cout << "Can not open course file" << endl;
	}
}
void editCourseID(Course& course, const string academicYear, const string semester)
{
	int check;

	cout << "\nCurrent course ID: " << course.courseId << endl;
	cout << "==> Do you want to edit this course's ID? (Yes: 1, No: 0)" << endl;
	check = getChoice(0, 1);

	if (check)
	{
		string newID;

		cout << "\nEnter new course ID: ";
		cin.ignore();
		newID = getInputCourseID();

		string currentFilePath = createCourseDirectoryWithFileName(academicYear, semester, course.ClassName, course.courseId, "txt");
		string newFilePath = createCourseDirectoryWithFileName(academicYear, semester, course.ClassName, newID, "txt");
		StudentCourseInformation* listInfo = nullptr;
		int countStudent = 0;

		if (currentFilePath != newFilePath) {
			if (loadStudentCourseInformationList(currentFilePath, listInfo, countStudent))
			{
				if (saveStudentCourseInformationList(newFilePath, listInfo, countStudent))
					course.courseId = newID;
				else
					cout << "Can't open student file." << endl;
			}
			else
				cout << "Can't open student file." << endl;
		}
	}
}
bool saveAcademicYearsAndSemester(const string& filePath, string* listAcademicYears, string* listSemesters, const int& countAcademicYears)
{
	ofstream fout(filePath);

	if (!fout.is_open())
		return false;

	for (int i = 0; i < countAcademicYears - 1; i++)
		for (int j = i + 1; j < countAcademicYears; j++)
			if (listAcademicYears[i] > listAcademicYears[j])
			{
				swap(listAcademicYears[i], listAcademicYears[j]);
				swap(listSemesters[i], listSemesters[j]);
			}

	for (int i = 0; i < countAcademicYears; i++)
	{
		int n;

		string* temp = StringToArrayString(listSemesters[i], ',', n);
		sortArray(temp, n, sizeof(string), ascendingSemester);
		listSemesters[i] = ArrayStringToString(temp, n, ',');

		delete[] temp;
	}

	fout << countAcademicYears << endl;
	for (int i = 0; i < countAcademicYears; i++)
	{
		fout << listAcademicYears[i] << endl;
		fout << listSemesters[i] << endl;
	}

	fout.close();
	return true;
}
void ExportScoreboardToCsv(const string& academicYear, const string& semester)
{
	string ClassName, filePath, destFilePath(PATH_DATA);
	Course course, * listCourses = nullptr;
	StudentCourseInformation* listInfo = nullptr;
	int countStudent = 0, countCourse = 0;

	if (getInputCourseFromSemester(academicYear, semester, ClassName, course, listCourses, countCourse))
	{
		delete[] listCourses;

		filePath = createCourseDirectoryWithFileName(academicYear, semester, ClassName, course.courseId, "txt");

		if (loadStudentCourseInformationList(filePath, listInfo, countStudent))
		{
			destFilePath = createCourseDirectoryWithFileName(academicYear, semester, ClassName,
				course.courseId + "-Scoreboard", "csv");

			if (saveListScoreboardsToCsv(destFilePath, listInfo, countStudent))
				cout << "Export successfully" << endl;
			else
				cout << "Export failed" << endl;

			releaseStudentCourseInformation(listInfo, countStudent);
		}
		else
			cout << "Can not open course file" << endl;
	}
}
void createAcademicYearsAndSemester()
{
	string academicYears, semester;

	cout << "Enter academic years: ";
	getline(cin, academicYears);

	cout << "Enter semester: ";
	getline(cin, semester);

	if (addAcademicYearsAndSemester(academicYears, semester))
		cout << "Successful." << endl;
	else
		cout << "Failed (This school year already exists)." << endl;

	system("pause");
}
bool checkElementInArray(void* arr, const int& numOfElements, const int& sizeItem,
	void* key, bool (*cmp)(void*, void*))
{
	if (arr == nullptr)
		return false;

	int index = findValue(arr, numOfElements, sizeItem, key, cmp);
	return (index != NOT_FOUND);
}

void viewStudentsOfClass()
{
	string filePath = PATH_DATA, ClassName;
	Student* listStudents = nullptr;
	int countStudent = 0;

	ClassName = getInputClassName();
	filePath = createClassDirectoryWithFileName(ClassName);
	loadStudentList(filePath, listStudents, countStudent);
	viewStudentList(listStudents, countStudent);

	delete[] listStudents;
}

bool addClassName(string ClassName)
{
	string filePath = PATH_DATA;
	string* listClassName = nullptr;
	int countClassName = 0;
	bool flag = true;

	filePath += "Class.txt";

	if (loadListClassName(filePath, listClassName, countClassName))
	{
		if (!checkElementInArray(listClassName, countClassName, sizeof(string), &ClassName, isEqualString))
		{
			listClassName = (string*)pushBackArray(listClassName, countClassName, sizeof(string),
				&ClassName, allocArrayString, copyString, releaseArrayString);

			flag = saveListClassName(filePath, listClassName, countClassName);
		}
		else flag = false;

		delete[] listClassName;
	}
	else flag = false;

	return flag;
}
void importClass()
{
	string ClassName, filePath;

	cout << "==> Enter class: ";
	getline(cin, ClassName);
	if (!addClassName(ClassName))
	{
		cout << "Add class name failed or this class already exists." << endl;
		return;
	}

	cout << "==> Path of the csv file: ";
	getline(cin, filePath);

	importStudentListFromCsv(filePath);
}
void viewClassList()
{
	string* listClassName = nullptr;
	string filePath = PATH_DATA;
	int countClassName = 0;

	filePath += "Class.txt";

	if (!loadListClassName(filePath, listClassName, countClassName))
	{
		cout << "Can not open class file." << endl;
		return;
	}

	showListClassName(listClassName, countClassName);
	delete[] listClassName;
}
void createClass() {
	ifstream f;
	string s = PATH_DATA;
	s += "Class.txt";
	f.open(s, ios::in);
	int countClass;
	int n;
	cout << "\nHOW MANY: ";
	cin >> n;
	f >> countClass;
	string* ClassRoom = new string[countClass + n];
	for (int i = 0; i < countClass; i++) {
		f >> ClassRoom[i];
	}
	f.close();

	cin.ignore();
	for (int i = 0; i < n; i++) {
		string NameClass;
		cout << "\nClass[" << i + 1 << "]: ";
		getline(cin, ClassRoom[countClass++]);
	}
	ofstream fout;
	fout.open(s, ios::out);
	fout << countClass << endl;
	for (int i = 0; i < countClass; i++) {
		fout << ClassRoom[i] << endl;
	}
	fout.close();

}

void addNewStudent()
{
	string filePathStudent, ClassName;
	Student* listStudents = nullptr, newStudent;
	int countStudent(0);

	ClassName = getInputClassName();
	filePathStudent = createClassDirectoryWithFileName(ClassName);

	if (!loadStudentList(filePathStudent, listStudents, countStudent))
	{
		cout << "Can not open student file." << endl;
		return;
	}

	cin.ignore();
	cout << "Enter new student's information: " << endl;
	cout << "ID: ";
	getline(cin, newStudent.id);
	cout << "Full name: ";
	getline(cin, newStudent.info.fullName);
	cout << "Date of birth (yyyy-mm-dd): ";
	getline(cin, newStudent.dateOfBirth);
	cout << "Gender (Male or Female): ";
	newStudent.info.gender = getInputGender();

	newStudent.status = true;
	newStudent.ClassName = ClassName;
	createAccountStudent(newStudent);

	if (!checkStudent(newStudent)) {
		listStudents = (Student*)pushBackArray(listStudents, countStudent, sizeof(Student),
			&newStudent, allocListStudents, copyStudent, releaseListStudents);

		if (saveStudentList(filePathStudent, listStudents, countStudent))
			cout << "Add new student successfully." << endl;
		else
			cout << "Can not open student file." << endl;
	}
	else
		cout << "This student is already on the list." << endl;

	delete[] listStudents;
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
