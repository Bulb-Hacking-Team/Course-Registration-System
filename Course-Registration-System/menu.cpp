#include "menu.h"

int getChoice(const int& minValue, const int& maxValue)
{
	int choice = 0;
	bool check;

	do
	{
		check = true;

		cout << "Enter your choice: ";
		cin >> choice;

		if (choice < minValue || maxValue < choice) {
			check = false;
			cout << "Invalid!!. Please enter again." << endl;
		}
	} while (check == false);

	return choice;
}

void loadStaff(ifstream& fin, Staff& s)
{
	getline(fin, s.info.acc.username);
	getline(fin, s.info.acc.password);
	getline(fin, s.info.fullName);
	fin >> s.info.gender;
}

bool loadListStaffs(const string& filePath, Staff*& listStaffs, int& countStaff)
{
	ifstream fin(filePath);

	if (!fin.is_open())
		return false;

	fin >> countStaff;
	fin.ignore();
	listStaffs = new Staff[countStaff];

	for (int i = 0; i < countStaff; i++)
	{
		loadStaff(fin, listStaffs[i]);
		fin.ignore();
	}

	fin.close();
	return true;
}

bool checkStaff(Staff& s)
{
	string staffFilePath;
	Staff* staffList = nullptr;
	int countStaff;
	bool flag = false;

	staffFilePath = PATH_DATA;
	staffFilePath += "Staff.txt";
	if (loadListStaffs(staffFilePath, staffList, countStaff))
	{
		for (int i = 0; i < countStaff; i++)
		{
			if (staffList[i].info.acc.username == s.info.acc.username)
				if (staffList[i].info.acc.password == s.info.acc.password)
				{
					s = staffList[i];
					flag = true;
					break;
				}
		}

		delete[] staffList;
	}

	return flag;
}

bool checkAcademicYearAndSemester(string academicYear, string semester)
{
	string filePath = PATH_DATA;
	string* listAcademicYears = nullptr, * listSemesters = nullptr;
	int countAcademicYear = 0;

	filePath += "SchoolYear.txt";

	if (loadAcademicYearsAndSemester(filePath, listAcademicYears, listSemesters, countAcademicYear))
	{
		for (int i = 0; i < countAcademicYear; i++)
			if (isEqualAcademicYears(&academicYear, &listAcademicYears[i]))
				for (int j = 0; j < countAcademicYear; j++)
				{
					int nSemester = 0;
					string* semesters = StringToArrayString(listSemesters[j], ',', nSemester);

					for (int k = 0; k < nSemester; k++)
						if (semester == semesters[k])
						{
							delete[] semesters;
							return true;
						}

					delete[] semesters;
				}

		delete[] listSemesters;
		delete[] listAcademicYears;
	}

	return false;
}

void getInputAcademicYearAndSemester(string& academicYear, string& semester)
{
	bool flag;

	viewAcademicYearsAndSemester();

	do {
		flag = true;

		cout << "\nEnter academic year: ";
		getline(cin, academicYear);
		cout << "Enter semester: ";
		getline(cin, semester);

		if (!checkAcademicYearAndSemester(academicYear, semester))
		{
			flag = false;
			cout << "The academic year and semester are invalid or do not exist." << endl;
		}

	} while (!flag);
}

bool checkStudentForLogin(Student& st)
{
	string classPath, * className, listClassPath = "";
	Student* studentList = nullptr;
	int countStudent = 0, number_of_classes;
	bool flag = false;

	listClassPath = PATH_DATA;
	listClassPath += "Class.txt";
	if (loadListClassName(listClassPath, className, number_of_classes))
	{
		for (int i = 0; i < number_of_classes; i++)
		{
			classPath = createClassDirectoryWithFileName(className[i]);

			if (loadStudentList(classPath, studentList, countStudent))
			{
				for (int j = 0; j < countStudent; j++)
				{
					if (studentList[j].id == st.info.acc.username)
						if (studentList[j].info.acc.password == st.info.acc.password)
						{
							st = studentList[j];
							flag = true;
							break;
						}
				}

				delete[] studentList;
			}

			if (flag)
				break;
		}

		delete[] className;
	}

	return flag;
}
void addNewStudent2(Student st)
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

	newStudent = st;
	listStudents = (Student*)pushBackArray(listStudents, countStudent, sizeof(Student),
		&newStudent, allocListStudents, copyStudent, releaseListStudents);

	if (saveStudentList(filePathStudent, listStudents, countStudent))
		cout << "Enroll successfully." << endl;
	else
		cout << "Fail!!!" << endl;

	delete[] listStudents;
}
void viewSchedule2(const string& academicYear, const string& semester, const Student& st)
{
	cout << "|" << setfill('-') << setw(129) << "-" << "|" << endl;
	cout << setfill(' ');
	fstream f;
	string filePath = "";
	filePath += st.id;
	cout << "| " << setw(5) << left << "  No" << " | " << setw(50) << left << "Course name" << " | "
		<< setw(15) << left << "Course ID" << " | " << setw(10) << left << "Class name" << " | "
		<< setw(4) << left << "Room" << " | " << setw(12) << left << "   Day" << " | "
		<< setw(13) << left << "    Time" << " |" << endl;

	cout << "|" << setfill('-') << setw(129) << "-" << "|" << endl;
	cout << setfill(' ');

	int count = 0;
	Schedule* listSchedule = getScheduleOfStudent(academicYear, semester, st, count);

	if (listSchedule != nullptr) {
		for (int i = 0; i < count; i++) {
			string dayString = convertWeekdayNumberToString(listSchedule[i].dayOfWeek);

			cout << "| " << setw(3) << right << i + 1 << "   | " << setw(50) << left << listSchedule[i].courseName
				<< " | " << setw(15) << left << listSchedule[i].courseId << " |   " << setw(8) << left << listSchedule[i].ClassName
				<< " | " << setw(4) << left << listSchedule[i].room << " |  " << setw(11) << left << dayString
				<< " | " << setw(2) << right << listSchedule[i].startTime.hour << ":" << setw(2) << left << listSchedule[i].startTime.minute
				<< " - " << setw(2) << right << listSchedule[i].endTime.hour << ":" << setw(2) << left << listSchedule[i].endTime.minute
				<< " |" << endl;

			cout << "|" << setfill('-') << setw(129) << "-" << "|" << endl;
			cout << setfill(' ');
		}
		getChoice(1, count);
		addNewStudent2(st);
		delete[] listSchedule;
	}
}
bool login(short role, Staff& s, Student& st)
{
	Account log;
	void* info = nullptr;
	cout << "Login. Please enter these information." << endl;
	cout << "Username: ";
	getline(cin, log.username);
	cout << "Password (8 <= length <= 40): ";
	getline(cin, log.password);

	s.info.acc = log;
	st.info.acc = log;

	if (checkStaff(s) == true && role == 1) 
	{
		return true;
	}
	else if (checkStudentForLogin(st) && role == 2) 
	{
		return true;
	}

	return false;
}

void showMenu()
{
	short role;
	int choice;
	Staff s;
	Student st;
	void* info = nullptr;

	while (true)
	{
		system("cls");
		cout << "|------------------------|" << endl;
		cout << "|        MAIN MENU       |" << endl;
		cout << "|------------------------|" << endl;
		cout << "| No |      Option       |" << endl;
		cout << "|------------------------|" << endl;
		cout << "| 1  | Log in            |" << endl;
		cout << "|------------------------|" << endl;
		cout << "| 2  | Exit              |" << endl;
		cout << "|------------------------|" << endl;
		
		choice = getChoice(1, 2);
		switch (choice)
		{
		case 1:
			system("cls");
			cin.ignore();
			cout << "|------------------------|" << endl;
			cout << "|          Role          |" << endl;
			cout << "|------------------------|" << endl;
			cout << "| No |      Option       |" << endl;
			cout << "|------------------------|" << endl;
			cout << "| 1  | Staff             |" << endl;
			cout << "|------------------------|" << endl;
			cout << "| 2  | Student           |" << endl;
			cout << "|------------------------|" << endl;
			cout << "\nBan la: ";
			cin >> role;
			cin.ignore();	
			if (login(role, s, st)) {
				switch (role)
				{
				case 1:
					showMenuOfStaff(s);
					break;
				case 2:
					showMenuOfStudent(st);
					break;
				default:
					cout << "Can't find account" << endl;
					break;
				}
			}
			else {
				cout << "\nFAILED! ";
			}
		case 2:
			system("pause");
			exit(0);
		}

		system("pause");
	}
}

void showMenuOfStudent(Student& st)
{
	string academicYear, semester;
	int choice;
	system("cls");
	getInputAcademicYearAndSemester(academicYear, semester);
	while (true)
	{
		system("cls");
		cout << "|--------------------------------------|" << endl;
		cout << "|                STUDENT               |" << endl;
		cout << "|--------------------------------------|" << endl;
		cout << "| No |             Option              |" << endl;
		cout << "|--------------------------------------|" << endl;
		cout << "| 1  | Enroll                          |" << endl;
		cout << "|--------------------------------------|" << endl;
		cout << "| 2  | View enrolling result           |" << endl;
		cout << "|--------------------------------------|" << endl;
		cout << "| 3  | Remove course                   |" << endl;
		cout << "|--------------------------------------|" << endl;
		cout << "| 4  | View his/her scores of a course |" << endl;
		cout << "|--------------------------------------|" << endl;
		cout << "| 5  | View profile info               |" << endl;
		cout << "|--------------------------------------|" << endl;
		cout << "| 6  | Change password                 |" << endl;
		cout << "|--------------------------------------|" << endl;
		cout << "| 7  | Log out                         |" << endl;
		cout << "|--------------------------------------|" << endl;

		choice = getChoice(1, 7);

		system("cls");

		switch (choice)
		{
		case 1:
			cin.ignore();
			viewSchedule2(academicYear, semester, st);
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:	

			break;
		case 7:
			showMenu();
			return;
		}

		system("pause");
	}
}
void showMenuOfStaff(Staff& staff)
{
	system("cls");
	cout << "|------------------------------------------------|" << endl;
	cout << "|                     STAFF                      |" << endl;
	cout << "|------------------------------------------------|" << endl;
	cout << "| No |      Option                               |" << endl;
	cout << "|------------------------------------------------|" << endl;
	cout << "| 1  | Class                                     |" << endl;
	cout << "|------------------------------------------------|" << endl;
	cout << "| 2  | Create academic year and semester         |" << endl;
	cout << "|------------------------------------------------|" << endl;
	cout << "| 3  | Enter existing academic year and semester |" << endl;
	cout << "|------------------------------------------------|" << endl;
	cout << "| 4  | Scoreboards                               |" << endl;
	cout << "|------------------------------------------------|" << endl;
	cout << "| 5  | Attendance list                           |" << endl;
	cout << "|------------------------------------------------|" << endl;
	cout << "| 6  | For input of lecturer                     |" << endl;
	cout << "|------------------------------------------------|" << endl;
	cout << "| 7  | View profile info                         |" << endl;
	cout << "|------------------------------------------------|" << endl;
	cout << "| 8  | Change password                           |" << endl;
	cout << "|------------------------------------------------|" << endl;
	cout << "| 9  | Log out                                   |" << endl;
	cout << "|------------------------------------------------|" << endl;

}

