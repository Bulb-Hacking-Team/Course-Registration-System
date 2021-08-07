#include "menu.h"
#include "staff.h"
void changePassword(Account& acc)
{
	string newPassword[2], curPassword;

	cout << "Password length: 8 <= length <= 40" << endl;

	cout << "Enter current password: ";
	curPassword = getInputPassword();

	cout << "Enter new password: ";
	newPassword[0] = getInputPassword();

	cout << "Enter new password again: ";
	newPassword[1] = getInputPassword();

	if (acc.password == curPassword) {
		if (newPassword[0] == newPassword[1]) {
			acc.password = newPassword[0];
			cout << "==> Password was successfully changed." << endl;
		}
		else cout << "The two new passwords are not the same." << endl;
	}
	else cout << "The current password is incorrect." << endl;
}
void viewLecturerInfo(Lecturer lec)
{
	viewGeneralInfo(lec.info);
	cout << "- Degree: " << lec.degree << endl << endl;
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
void showMenuOfClass()
{
	int choice;

	system("cls");

	while (true)
	{
		cout << "|-------------------------------------------------|" << endl;
		cout << "|                      CLASS                      |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "| No |                   Option                   |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "| 1  | Import students of a class from a csv file |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "| 2  | Add a new student to a class               |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "| 3  | Create Class                               |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "| 4  | View list of students in a class           |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "| 5  | View list of classes                       |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "| 6  | Return to previous menu                    |" << endl;
		cout << "|-------------------------------------------------|" << endl;

		choice = getChoice(1, 6);

		system("cls");

		switch (choice)
		{
		case 1:
			cin.ignore();
			importClass();
			break;
		case 2:
			addNewStudent();
			break;
		case 3:
			createClass();
			break;
		case 4:
			viewStudentsOfClass();
			break;
		case 5:
			viewClassList();
			break;
		case 6:
			return;
		}
		system("pause");
		system("cls");
	}
}
//Option for Staff
void showMenuOfCourse(const string& academicYear, const string& semester)
{
	int choice;

	while (true)
	{
		system("cls");

		cout << "|-------------------------------------------------------------------|" << endl;
		cout << "|                               COURSE                              |" << endl;
		cout << "|-------------------------------------------------------------------|" << endl;
		cout << "| No |                          Option                              |" << endl;
		cout << "|-------------------------------------------------------------------|" << endl;
		cout << "| 1  | Create / view academic years, and semesters                  |" << endl;
		cout << "|-------------------------------------------------------------------|" << endl;
		cout << "| 2  | Add a new course                                             |" << endl;
		cout << "|-------------------------------------------------------------------|" << endl;
		cout << "| 3  | Update course                                                |" << endl;
		cout << "|-------------------------------------------------------------------|" << endl;
		cout << "| 4  | Remove a course                                              |" << endl;
		cout << "|-------------------------------------------------------------------|" << endl;
		cout << "| 5  | View list of courses in the current semester                 |" << endl;
		cout << "|-------------------------------------------------------------------|" << endl;
		cout << "| 6  | View list of students of a course                            |" << endl;
		cout << "|-------------------------------------------------------------------|" << endl;
		cout << "| 7  | Return to previous menu                                      |" << endl;
		cout << "|-------------------------------------------------------------------|" << endl;

		choice = getChoice(1, 8);

		system("cls");

		switch (choice)
		{
		case 1:
			showFunctionsOfAcademicYearAndSemester();
			break;
		case 2:
			addNewCourse(academicYear, semester);
			break;
		case 3:
			editAnExistingCourse(academicYear, semester);
			break;
		case 4:
			removeCourse(academicYear, semester);
			break;
		case 5:
			viewListCourses(academicYear, semester);
			break;
		case 6:
			viewListStudentsOfCourse(academicYear, semester);
			break;
		case 7:
			showMenu();
			return;
		}

		system("pause");
	}
}
void showMenuOfAttendanceList(const string& academicYear, const string& semester)
{
	int choice;

	while (true)
	{
		system("cls");

		cout << "|--------------------------------------------------|" << endl;
		cout << "|                 ENROLLING LIST                   |" << endl;
		cout << "|--------------------------------------------------|" << endl;
		cout << "| No |                    Option                   |" << endl;
		cout << "|--------------------------------------------------|" << endl;
		cout << "| 1  | Search and view attendance list of a course |" << endl;
		cout << "|--------------------------------------------------|" << endl;
		cout << "| 2  | Export a attendance list to a csv file      |" << endl;
		cout << "|--------------------------------------------------|" << endl;
		cout << "| 3  | Return to previous menu                     |" << endl;
		cout << "|--------------------------------------------------|" << endl;

		choice = getChoice(1, 3);

		system("cls");

		switch (choice)
		{
		case 1:
			viewAttendanceListOfCourse(academicYear, semester);
			break;
		case 2:
			ExportAttendanceListToCsv(academicYear, semester);
			break;
		case 3:
			return;
		}

		system("pause");
	}
}
void showMenuOfScoreboard(const string& academicYear, const string& semester)
{
	int choice;

	while (true)
	{
		system("cls");

		cout << "|-------------------------------------------------|" << endl;
		cout << "|                    SCOREBOARD                   |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "| No |                  Option                    |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "| 1  | Search and view the scoreboard of a course |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "| 2  | Export a scoreboard to a csv file          |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "| 3  | Return to previous menu                    |" << endl;
		cout << "|-------------------------------------------------|" << endl;

		choice = getChoice(1, 3);

		system("cls");

		switch (choice)
		{
		case 1:
			viewScoreboardOfCourse(academicYear, semester);
			break;
		case 2:
			ExportScoreboardToCsv(academicYear, semester);
			break;
		case 3:
			return;
		}

		system("pause");
	}
}

//Staff
void viewGeneralInfo(GeneralInformation info)
{
	cout << "\n- Full name: " << info.fullName << endl;
	cout << "- Gender: " << ((info.gender == MALE) ? ("Male") : ("Female")) << endl;
}

void viewStaffInfo(Staff s)
{
	viewGeneralInfo(s.info);
	cout << endl;
}
void showMenuOfStaff(Staff& staff)
{
	system("cls");
	Lecturer lec;
	string academicYear, semester, filePath = PATH_DATA;
	Staff* listStaffs = nullptr;
	int choice, countStaff = 0, idx;

	filePath += "Staff.txt";

	while (true)
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
		cout << "| 5  | Enrolling list                            |" << endl;
		cout << "|------------------------------------------------|" << endl;
		cout << "| 6  | For input of lecturer                     |" << endl;
		cout << "|------------------------------------------------|" << endl;
		cout << "| 7  | View profile info                         |" << endl;
		cout << "|------------------------------------------------|" << endl;
		cout << "| 8  | Change password                           |" << endl;
		cout << "|------------------------------------------------|" << endl;
		cout << "| 9  | Log out                                   |" << endl;
		cout << "|------------------------------------------------|" << endl;

		choice = getChoice(1, 9);

		system("cls");

		switch (choice)
		{
		case 1:
			showMenuOfClass();
			break;
		case 2:
			cin.ignore();
			createAcademicYearsAndSemester();
			showMenuOfCourse(academicYear, semester);
			break;
		case 3:
			cin.ignore();
			getInputAcademicYearAndSemester(academicYear, semester);
			showMenuOfCourse(academicYear, semester);
			break;
		case 4:
			showMenuOfScoreboard(academicYear, semester);
			break;
		case 5:
			showMenuOfAttendanceList(academicYear, semester);
			break;
		case 6:
		{
			string name;
			cin.ignore();
			cout << "Enter lecturer's name: ";
			getline(cin, lec.info.fullName);
			cout << "\nEnter ID: ";
			getline(cin, lec.info.acc.password);
			if (checkLecturer(lec)) {
				showMenuOfLecturer(lec);
			}
			system("pause");
			break;
		}
		case 7:
			viewStaffInfo(staff);
			system("pause");
			break;
		case 8:
			cin.ignore();
			changePassword(staff.info.acc);

			if (loadListStaffs(filePath, listStaffs, countStaff)) {
				idx = findValue(listStaffs, countStaff, sizeof(Staff), &staff, isEqualStaff);
				listStaffs[idx].info.acc.password = staff.info.acc.password;

				saveListStaffs(filePath, listStaffs, countStaff);
				delete[] listStaffs;
				listStaffs = nullptr;
			}

			system("pause");
			break;
		case 9:
			showMenu();
			return;
		}
	}
}
void viewStudentInfo(Student st)
{
	viewGeneralInfo(st.info);
	cout << "- Student ID: " << st.id << endl;
	cout << "- Date of birth: " << st.dateOfBirth << endl;
	cout << "- Status: " << ((st.status) ? ("Available") : ("Expelled")) << endl << endl;
}
void viewListStudentsOfCourse2(const string& academicYear, const string& semester, const Lecturer& lec)
{
	string filePath;
	Course course;
	StudentCourseInformation* listInfo = nullptr;
	int countStudent = 0;

	if (getInputCourseOfLecturer(academicYear, semester, course, lec))
	{
		filePath = createCourseDirectoryWithFileName(academicYear, semester, course.ClassName, course.courseId, "txt");
		if ((filePath, listInfo, countStudent))
		{
			viewStudentListFromCourse(listInfo, countStudent);
			releaseStudentCourseInformation(listInfo, countStudent);
		}
		else
			cout << "Can not open course file" << endl;
	}
}

void showMenuOfLecturer(Lecturer& lec)
{
	string academicYear, semester, filePath = PATH_DATA;
	Lecturer* listLecturers = nullptr;
	int choice, countLecturer = 0;

	filePath += "Lecturer.txt";

	system("cls");
	getInputAcademicYearAndSemester(academicYear, semester);

	while (true)
	{
		system("cls");

		cout << "|----------------------------------------------------|" << endl;
		cout << "|                      STAFF-2                       |" << endl;
		cout << "|----------------------------------------------------|" << endl;
		cout << "| No |                   Option                      |" << endl;
		cout << "|----------------------------------------------------|" << endl;
		cout << "| 1  | View enrolling list of a course               |" << endl;
		cout << "|----------------------------------------------------|" << endl;
		cout << "| 2  | Import scoreboard of a course from a csv file |" << endl;
		cout << "|----------------------------------------------------|" << endl;
		cout << "| 3  | Edit grade of a student                       |" << endl;
		cout << "|----------------------------------------------------|" << endl;
		cout << "| 4  | View a scoreboard                             |" << endl;
		cout << "|----------------------------------------------------|" << endl;
		cout << "| 5  | View profile info                             |" << endl;
		cout << "|----------------------------------------------------|" << endl;
		cout << "| 6  | Return                                        |" << endl;
		cout << "|----------------------------------------------------|" << endl;

		choice = getChoice(1, 6);

		system("cls");

		switch (choice)
		{
		case 1:
			viewListStudentsOfCourse2(academicYear, semester, lec);
			system("pause");
			break;
		case 2:
			importScoreboardsOfCourse(academicYear, semester, lec);
			system("pause");
			break;
		case 3:
			editGradeStudent(academicYear, semester, lec);
			system("pause");
			break;
		case 4:
			viewScoreboardOfCourse(academicYear, semester, lec);
			system("pause");
			break;
		case 5:
			viewLecturerInfo(lec);
			system("pause");
			break;
		case 6:
			showMenu();
			return;
		}
	}
}
void addNewStudent2(Student st)
{
	string filePathStudent, ClassName;
	Student* listStudents = nullptr, newStudent;
	int countStudent(0);

	ClassName = st.ClassName;
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
		cout << "Fail!!! " << endl;

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
void showListCourses2(Course* listCourses, const int& countCourse, const string& ClassName)
{
	cout << "Courses of class " << ClassName << ":\n" << endl;

	if (countCourse != 0)
	{
		int idx = 0;
		cout << "| " << setw(5) << left << "  No" << " | " << setw(50) << left << "Course name" << " | "
			<< setw(15) << left << "Course ID" << " | " << setw(10) << left << "Class name" << " | "
			<< setw(4) << left << "Room" << " | " << setw(12) << left << "   Day" << " | "
			<< setw(13) << left << "    Time" << " |" << endl;

		cout << "|" << setfill('-') << setw(129) << "-" << "|" << endl;
		cout << setfill(' ');
		for (int i = 0; i < countCourse; i++, idx++)
		{
			if (listCourses[idx].status)
			{
				string dayString = convertWeekdayNumberToString(listCourses[i].dayOfWeek);

				cout << "| " << setw(3) << right << i + 1 << "   | " << setw(50) << left << listCourses[i].courseName
					<< " | " << setw(15) << left << listCourses[i].courseId << " |   " << setw(8) << left << listCourses[i].ClassName
					<< " | " << setw(4) << left << listCourses[i].room << " |  " << setw(11) << left << dayString
					<< " | " << setw(2) << right << listCourses[i].startTime.hour << ":" << setw(2) << left << listCourses[i].startTime.minute
					<< " - " << setw(2) << right << listCourses[i].endTime.hour << ":" << setw(2) << left << listCourses[i].endTime.minute
					<< " |" << endl;

				cout << "|" << setfill('-') << setw(129) << "-" << "|" << endl;
				cout << setfill(' ');
			}
			else
				i--;
		}
	}
	else
		cout << "There are no courses available." << endl;
}
void viewListCourses2(const string& academicYear, const string& semester, Student st)
{
	string ClassName, filePath;
	Course* listCourses = nullptr;
	int countCourse;

	ClassName = st.ClassName;
	filePath = createCourseDirectoryWithFileName(academicYear, semester, ClassName, "Schedule", "txt");

	if (loadListCourses(filePath, listCourses, countCourse))
	{
		showListCourses2(listCourses, countCourse, ClassName);
		delete[] listCourses;
	}
	else
		cout << "Can not open course file." << endl;
}
void viewListCourses3(const string& academicYear, const string& semester, Student st)
{
	string ClassName, filePath;
	Course* listCourses = nullptr;
	int countCourse;

	ClassName = st.ClassName;
	filePath = createCourseDirectoryWithFileName(academicYear, semester, ClassName, "Schedule", "txt");

	if (loadListCourses(filePath, listCourses, countCourse))
	{
		showListCourses(listCourses, countCourse, ClassName);
		getChoice(1, countCourse);
		addNewStudent2(st);
		delete[] listCourses;
	}
	else
		cout << "Can not open course file." << endl;
}
void showMenuOfStudent(Student& st)
{
	string academicYear, semester, filePath;
	Student* listStudents = nullptr;
	int choice, countStudent = 0;

	filePath = createClassDirectoryWithFileName(st.ClassName);

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
			viewListCourses3(academicYear, semester, st);
			break;
		case 2:
			cin.ignore();
			viewListCourses2(academicYear, semester, st);
			break;
		case 3:
			removeCourse(academicYear, semester);
			break;
		case 4:
			viewScores(academicYear, semester, st);
			break;
		case 5:
			viewStudentInfo(st);
			break;
		case 6:
			cin.ignore();
			changePassword(st.info.acc);

			if (loadStudentList(filePath, listStudents, countStudent)) {
				int idx = findValue(listStudents, countStudent, sizeof(Student), &st, isEqualStudentId);
				listStudents[idx].info.acc.password = st.info.acc.password;

				saveStudentList(filePath, listStudents, countStudent);
				delete[] listStudents;
				listStudents = nullptr;
			}
			break;
		case 7:
			showMenu();
			return;
		}

		system("pause");
	}
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
bool checkLecturer(Lecturer& lec)
{
	string lectFilePath;
	Lecturer* lecturerList = nullptr;
	int countLect = 0;
	bool flag = false;
	lectFilePath = PATH_DATA;
	lectFilePath += "Lecturer.txt";
	if (loadListLecturers(lectFilePath, lecturerList, countLect))
	{
		for (int i = 0; i < countLect; i++)
		{
			if (lecturerList[i].info.fullName == lec.info.fullName)
				if (lecturerList[i].info.acc.password == lec.info.acc.password)
				{
					lec = lecturerList[i];
					flag = true;
					break;
				}
		}

		delete[] lecturerList;
	}

	return flag;
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
//Enter&&Update Academic Year and Semester
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
//
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

	if (checkStaff(s) == true && role == 1) {
		return true;
	}
	else if (checkStudentForLogin(st) && role == 2) {
		return true;
	}

	return false;
}
void showMenu()
{
	short role;
	int choice;
	Staff s;
	Lecturer lec;
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
				cout << "\nFAILED";
			}

		case 2:
			system("pause");
			exit(0);
		}

		system("pause");
	}
}
