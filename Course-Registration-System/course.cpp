#include"course.h"

string createCourseDirectoryWithFileName(const string& academicYear, const string& semester, const string& ClassName, const string& argLast, const string& FileExtension)
{
	string result = PATH_DATA;
	result += academicYear + "-" + semester + "-" + ClassName + "-" + argLast + "." + FileExtension;

	return result;
}

void loadCourse(ifstream& fin, Course& course)
{
	Lecturer& lec = course.lecturer;

	getline(fin, course.courseId);
	getline(fin, course.courseName);
	getline(fin, course.ClassName);
	fin >> course.NumberOfCredits;
	fin.ignore();
	getline(fin, lec.info.acc.username);
	getline(fin, lec.info.fullName);
	getline(fin, lec.degree);
	fin >> lec.info.gender;
	fin.ignore();
	fin >> course.startDate.year >> course.startDate.month >> course.startDate.day;
	fin >> course.endDate.year >> course.endDate.month >> course.endDate.day;
	fin >> course.dayOfWeek;
	fin.ignore();

	fin >> course.startTime.hour >> course.startTime.minute;
	fin >> course.endTime.hour >> course.endTime.minute;
	fin.ignore();

	getline(fin, course.room);
	fin >> course.status;
}

bool loadListCourses(const string& filePath, Course*& listCourses, int& countCourse)
{
	ifstream fin(filePath);

	if (!fin.is_open())
		return false;

	fin >> countCourse;
	fin.ignore();

	listCourses = new Course[countCourse];

	for (int i = 0; i < countCourse; i++)
	{
		loadCourse(fin, listCourses[i]);
		fin.ignore();
	}

	fin.close();
	return true;
}

void initAttendanceList(AttendanceList& listAttends, const int& numberOfWeeks)
{
	listAttends.countDate = numberOfWeeks;
	listAttends.dateList = new Date[listAttends.countDate];
	listAttends.status = new bool[listAttends.countDate]{ false };
}

void loadScoreboard(ifstream& fin, Scoreboard& scoreboard, const string& FileExtension)
{
	bool flag = (FileExtension == "csv") ? (true) : (false);
	char delim;

	fin >> scoreboard.midterm;
	if (flag)
		fin >> delim;

	fin >> scoreboard._final;
	if (flag)
		fin >> delim;

	fin >> scoreboard.bonus;
	if (flag)
		fin >> delim;

	fin >> scoreboard.total;
}

void loadAttendanceList(ifstream& fin, AttendanceList& listAttends)
{
	for (int i = 0; i < listAttends.countDate; i++)
	{
		fin >> listAttends.dateList[i].year >> listAttends.dateList[i].month >> listAttends.dateList[i].day;
		fin >> listAttends.startTime.hour >> listAttends.startTime.minute;
		fin >> listAttends.endTime.hour >> listAttends.endTime.minute;
		fin >> listAttends.status[i];
	}
}

bool loadStudentCourseInformationList(const string& filePath, StudentCourseInformation*& listInfo, int& countStudent)
{
	ifstream fin(filePath);
	int countWeek;

	if (!fin.is_open())
		return false;

	fin >> countStudent;
	fin >> countWeek;
	fin.ignore();

	listInfo = new StudentCourseInformation[countStudent];

	for (int i = 0; i < countStudent; i++)
	{
		initAttendanceList(listInfo[i].attendList, countWeek);

		getline(fin, listInfo[i].st.id);
		getline(fin, listInfo[i].st.info.fullName);
		getline(fin, listInfo[i].st.ClassName, DELIMIT_TXT);

		loadScoreboard(fin, listInfo[i].scoreList, "txt");
		loadAttendanceList(fin, listInfo[i].attendList);
		fin >> listInfo[i].status;
		fin.ignore();
	}

	fin.close();
	return true;
}

void releaseAttendanceList(AttendanceList& attendList)
{
	delete[] attendList.dateList;
	delete[] attendList.status;
}

void releaseStudentCourseInformation(StudentCourseInformation*& listInfo, const int& countStudent)
{
	for (int i = 0; i < countStudent; i++)
		releaseAttendanceList(listInfo[i].attendList);

	delete[] listInfo;
}

void releaseStudentCourseInformationList(void* listInfo, const int& countStudent)
{
	if (listInfo)
	{
		StudentCourseInformation* arr = (StudentCourseInformation*)listInfo;
		releaseStudentCourseInformation(arr, countStudent);
	}
}
bool getInputCourseFromSemester(const string& academicYear, const string& semester, string& ClassName,
	Course& course, Course*& listCourses, int& countCourse)
{
	string filePath;
	int choice = 0;

	ClassName = getInputClassName();
	filePath = createCourseDirectoryWithFileName(academicYear, semester, ClassName, "Schedule", "txt");

	if (!loadListCourses(filePath, listCourses, countCourse))
		return false;

	showListCourses(listCourses, countCourse, ClassName);
	choice = getChoice(1, countCourse);
	course = listCourses[choice - 1];

	return true;
}
bool saveListCourses(const string& filePath, Course* listCourses, const int& countCourse)
{
	ofstream fout(filePath);
	int idx = 0;

	if (!fout.is_open())
		return false;

	fout << countCourse << endl;
	for (int i = 0; i < countCourse; i++, idx++)
	{
		if (listCourses[idx].status)
			saveCourse(fout, listCourses[idx]);
		else
			i--;
	}

	fout.close();
	return true;
}

void showAttendaceListOfCourse(StudentCourseInformation*& listInfo, const int& countStudent) {
	int len = 59 + (15 * listInfo[0].attendList.countDate);
	string status;

	cout << "| " << setw(4) << left << "No" << " | " << setw(12) << "Student ID"
		<< " | " << setw(35) << "Full name" << endl;

	for (int i = 0; i < countStudent; i++)
	{
		cout << "| " << setw(4) << left << i + 1
			<< " | " << setw(12) << left << listInfo[i].st.id
			<< " | " << setw(35) << left << listInfo[i].st.info.fullName << endl;
	}
}


void showListScoreboardsOfCourse(StudentCourseInformation*& listInfo, const int& countStudent)
{
	cout << "|" << setfill('-') << setw(112) << "-" << "|" << endl;
	cout << setfill(' ');

	cout << "| " << setw(5) << left << " No"
		<< " | " << setw(12) << left << "Student ID" << " | " << setw(35) << left << "Full name"
		<< " | " << setw(10) << left << "  Midterm" << " | " << setw(10) << left << "  Final"
		<< " | " << setw(10) << left << "  Bonus" << " | " << setw(10) << left << "  Total" << " |" << endl;

	cout << "|" << setfill('-') << setw(112) << "-" << "|" << endl;
	cout << setfill(' ');

	for (int i = 0; i < countStudent; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << "  ";
		viewScoreboardOfStudent(listInfo[i].st, listInfo[i].scoreList);

		cout << "|" << setfill('-') << setw(112) << "-" << "|" << endl;
		cout << setfill(' ');
	}
}


void saveCourse(ofstream& fout, Course& course)
{
	Lecturer& lec = course.lecturer;

	fout << course.courseId << endl << course.courseName << endl << course.ClassName << endl;
	fout << course.NumberOfCredits << endl;
	fout << lec.info.acc.username << endl << lec.info.fullName << endl << lec.degree << endl << lec.info.gender << endl;
	fout << toString(course.startDate, ' ') << endl;
	fout << toString(course.endDate, ' ') << endl;
	fout << course.dayOfWeek << endl;
	fout << course.startTime.hour << " " << course.startTime.minute << endl;
	fout << course.endTime.hour << " " << course.endTime.minute << endl;
	fout << course.room << endl << course.status << endl;
}
bool isEqualCourseId(void* val1, void* val2)
{
	Course* course1, * course2;

	course1 = (Course*)val1;
	course2 = (Course*)val2;

	return (course1->courseId == course2->courseId);
}
void viewScoreboardOfStudent(const Student& st, const Scoreboard& score)
{
	cout << " | " << setw(12) << left << st.id << " | " << setw(35) << left << st.info.fullName;
	cout << " | " << setw(6) << right << score.midterm << "     | " << setw(6) << right << score._final
		<< "     | " << setw(6) << right << score.bonus << "     | " << setw(6) << right << score.total
		<< "     |" << endl;
}

bool ascendingStudentIdOfCourse(void* val1, void* val2)
{
	StudentCourseInformation* st1 = (StudentCourseInformation*)val1;
	StudentCourseInformation* st2 = (StudentCourseInformation*)val2;

	return ascendingString(&st1->st.id, &st2->st.id);
}

void saveScoreboard(ofstream& fout, const Scoreboard& scoreboard)
{
	fout << scoreboard.midterm << endl
		<< scoreboard._final << endl
		<< scoreboard.bonus << endl
		<< scoreboard.total << endl;
}

bool saveStudentCourseInformationList(const string& filePath, StudentCourseInformation* listInfo, const int& countStudent)
{
	ofstream fout(filePath);
	int  nStudent = 0;

	if (!fout.is_open())
		return false;

	for (int i = 0; i < countStudent; i++)
		if (listInfo[i].status)
			nStudent++;

	fout << nStudent << endl;
	fout << listInfo[0].attendList.countDate << endl;

	sortArray(listInfo, countStudent, sizeof(StudentCourseInformation), ascendingStudentIdOfCourse);

	for (int i = 0; i < countStudent; i++)
	{
		if (listInfo[i].status)
		{
			fout << listInfo[i].st.id << endl << listInfo[i].st.info.fullName << endl << listInfo[i].st.ClassName << endl;
			saveScoreboard(fout, listInfo[i].scoreList);
			//saveAttendanceList(fout, listInfo[i].attendList);
			fout << listInfo[i].status << endl;
		}
	}

	fout.close();
	return true;
}