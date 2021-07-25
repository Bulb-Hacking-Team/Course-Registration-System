#include "student.h"

string createClassDirectoryWithFileName(const string& ClassName)
{
	string result = PATH_DATA;
	result += "Student-" + ClassName + ".txt";

	return result;
}
void loadStudentFromTxt(ifstream& fin, Student& st)
{
	getline(fin, st.id, DELIMIT_TXT);
	getline(fin, st.info.acc.password, DELIMIT_TXT);
	getline(fin, st.info.fullName, DELIMIT_TXT);
	getline(fin, st.dateOfBirth, DELIMIT_TXT);
	getline(fin, st.ClassName, DELIMIT_TXT);
	fin >> st.info.gender >> st.status;

	st.info.acc.username = st.id;
}
void viewStudentListFromCourse(StudentCourseInformation* listInfo, const int& countStudent)
{
	cout << "|" << setfill('-') << setw(74) << "-" << "|" << endl;
	cout << setfill(' ');

	cout << "| " << setw(4) << left << "No" << " | " << setw(12) << left << "ID"
		<< " | " << setw(35) << left << "Full name"
		<< " | " << setw(12) << left << "ClassName" << " |" << endl;

	cout << "|" << setfill('-') << setw(74) << "-" << "|" << endl;
	cout << setfill(' ');

	for (int i = 0; i < countStudent; i++)
	{
		cout << "| " << setw(4) << left << i + 1
			<< " | " << setw(12) << left << listInfo[i].st.id
			<< " | " << setw(35) << left << listInfo[i].st.info.fullName
			<< " | " << setw(12) << left << listInfo[i].st.ClassName << " |" << endl;

		cout << "|" << setfill('-') << setw(74) << "-" << "|" << endl;
		cout << setfill(' ');
	}
}
bool ascendingStudentId(void* Name1, void* Name2)
{
	return (*(string*)Name1 > *(string*)Name2);
}
bool loadStudentList(const string& filePath, Student*& listStudents, int& countStudent)
{
	ifstream fin(filePath);

	if (!fin.is_open())
		return false;

	fin >> countStudent;
	fin.ignore();

	listStudents = new Student[countStudent];

	for (int i = 0; i < countStudent; i++) {
		loadStudentFromTxt(fin, listStudents[i]);
		fin.ignore();
	}

	fin.close();
	return true;
}

bool isEqualStudentIdFromCourse(void* val1, void* val2)
{
	StudentCourseInformation* value1, * value2;

	value1 = (StudentCourseInformation*)val1;
	value2 = (StudentCourseInformation*)val2;

	return (value1->st.id == value2->st.id);
}
void importStudentListFromCsv(const string& filePath)
{
	ifstream fin(filePath);

	if (!fin.is_open())
	{
		cout << "Can not open file." << endl;
		return;
	}

	Student* listStudents = new Student[MAX_SIZE];
	int ignoreData, countStudent = 0;
	string ignoreLine;

	getline(fin, ignoreLine); // ignore the first line.

	while (!fin.eof())
	{
		fin >> ignoreData;
		fin.ignore();

		loadStudentFromCsv(fin, listStudents[countStudent]);
		createAccountStudent(listStudents[countStudent]);
		countStudent++;
	}

	fin.close();

	string filePathToSaveData = createClassDirectoryWithFileName(listStudents[0].ClassName);

	if (saveStudentList(filePathToSaveData, listStudents, countStudent))
		cout << "==> Import successfully!!" << endl;
	else
		cout << "==> Import failed." << endl;

	delete[] listStudents;
}
bool saveListScoreboardsToCsv(const string& filePath, StudentCourseInformation* listInfo, const int& countStudent)
{
	ofstream fout(filePath);

	if (!fout.is_open())
		return false;

	fout << "No,Student ID,Fullname,Midterm,Final,Bonus,Total" << endl;
	for (int i = 0; i < countStudent; i++)
	{
		fout << i + 1 << ",";
		fout << listInfo[i].st.id << "," << listInfo[i].st.info.fullName << ","
			<< listInfo[i].scoreList.midterm << "," << listInfo[i].scoreList._final << ","
			<< listInfo[i].scoreList.bonus << "," << listInfo[i].scoreList.total << endl;
	}

	fout.close();
	return true;
}
void createAccountStudent(Student& st)
{
	st.info.acc.username = st.id;

	for (const char& ch : st.dateOfBirth)
		if (ch != '-')
			st.info.acc.password += ch;
}

void loadStudentFromCsv(ifstream& fin, Student& st)
{
	string gender;

	getline(fin, st.id, DELIMIT_CSV);
	getline(fin, st.info.fullName, DELIMIT_CSV);
	getline(fin, st.dateOfBirth, DELIMIT_CSV);
	getline(fin, st.ClassName, DELIMIT_CSV);
	getline(fin, gender);

	st.info.gender = (gender == "Male") ? (MALE) : (FEMALE);
	st.status = true;
}

void viewStudent(const Student& st)
{

	cout << "| " << setw(12) << left << st.id << " | " << setw(35) << left << st.info.fullName
		<< " | " << setw(10) << left << ((st.info.gender == MALE) ? ("MALE") : ("FEMALE"))
		<< " | " << setw(15) << left << st.dateOfBirth
		<< " | " << setw(12) << left << st.ClassName << " |" << endl;
}

void viewStudentList(Student* listStudents, const int& countStudent)
{
	cout << "|" << setfill('-') << setw(105) << "-" << "|" << endl;
	cout << setfill(' ');

	cout << "| " << setw(4) << left << "No" << " | " << setw(12) << left << "ID"
		<< " | " << setw(35) << left << "Full name"
		<< " | " << setw(10) << left << "Gender"
		<< " | " << setw(15) << left << "Date Of Birth"
		<< " | " << setw(12) << left << "ClassName" << " |" << endl;

	cout << "|" << setfill('-') << setw(105) << "-" << "|" << endl;
	cout << setfill(' ');

	for (int i = 0; i < countStudent; i++)
	{
		cout << "| " << setw(4) << left << i + 1 << " ";
		viewStudent(listStudents[i]);

		cout << "|" << setfill('-') << setw(105) << "-" << "|" << endl;
		cout << setfill(' ');
	}

}


Schedule* getScheduleOfStudent(const string& academicYear, const string& semester, const Student& st, int& count) {
	string filename = PATH_DATA;
	string* listClassName;
	int countClassName, countCourse, countStudent;
	Course* listCourses;
	StudentCourseInformation* listInfo, key;
	Schedule* temp = new Schedule[MAX_SIZE], * listSchedule = nullptr;

	filename += "Class.txt";
	count = 0;

	if (loadListClassName(filename, listClassName, countClassName))
	{
		key.st = st;

		for (int i = 0; i < countClassName; i++)
		{
			string courseFilePath = createCourseDirectoryWithFileName(academicYear, semester, listClassName[i], "Schedule", "txt");
			if (loadListCourses(courseFilePath, listCourses, countCourse))
			{

				for (int j = 0; j < countCourse; j++)
				{

					string filePath = createCourseDirectoryWithFileName(academicYear, semester, listClassName[i], listCourses[j].courseId, "txt");
					if (loadStudentCourseInformationList(filePath, listInfo, countStudent))
					{
						int idx = findValue(listInfo, countStudent, sizeof(StudentCourseInformation), &key, isEqualStudentIdFromCourse);

						if (idx != NOT_FOUND)
						{
							temp[count].courseId = listCourses[j].courseId;
							temp[count].courseName = listCourses[j].courseName;
							temp[count].ClassName = listClassName[i];
							temp[count].dayOfWeek = listCourses[j].dayOfWeek;
							temp[count].room = listCourses[j].room;
							temp[count].startTime = listCourses[j].startTime;
							temp[count].endTime = listCourses[j].endTime;
							count++;
						}
						releaseStudentCourseInformationList(listInfo, countStudent);
					}
				}
				delete[] listCourses;
			}
		}
		delete[] listClassName;


		listSchedule = new Schedule[count];
		for (int i = 0; i < count; i++)
			listSchedule[i] = temp[i];
	}

	delete[] temp;
	return listSchedule;
}
void releaseListStudents(void* listStudents, const int& countStudent)
{
	Student* arr = (Student*)listStudents;
	delete[] arr;
}
void copyStudent(void* st1, void* st2)
{
	*(Student*)st1 = *(Student*)st2;
}
void* allocListStudents(const int& countStudent)
{
	Student* arr = new Student[countStudent];
	return arr;
}
void saveStudent(ofstream& fout, const Student& st)
{
	fout << st.id << endl << st.info.acc.password << endl;
	fout << st.info.fullName << endl << st.dateOfBirth << endl;
	fout << st.ClassName << endl << st.info.gender << endl << st.status << endl;
}

bool ascendingStudentId(void* Name1, void* Name2)
{
	return (*(string*)Name1 > * (string*)Name2);
}

bool saveStudentList(const string& filePath, Student* listStudents, const int& countStudent)
{
	ofstream fout(filePath);
	int idx = 0, nStudents = 0;

	if (!fout.is_open())
		return false;

	// sort student list with ascending id.
	sortArray(listStudents, countStudent, sizeof(Student), ascendingStudentId);
	//	sortArray_1(listStudents, countStudent);
	for (int i = 0; i < countStudent; i++)
		if (listStudents[i].status)
			nStudents++;

	fout << nStudents << endl;
	for (int i = 0; i < nStudents; i++, idx++)
	{
		if (listStudents[idx].status)
			saveStudent(fout, listStudents[idx]);
		else
			i--;
	}

	fout.close();
	return true;
}
bool isEqualStudentId(void* st1, void* st2)
{
	Student* value1, * value2;

	value1 = (Student*)st1;
	value2 = (Student*)st2;

	return (value1->id == value2->id);
}
void viewSchedule(const string& academicYear, const string& semester, const Student& st)
{
	cout << "|" << setfill('-') << setw(129) << "-" << "|" << endl;
	cout << setfill(' ');

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

		delete[] listSchedule;
	}
}
bool checkStudentOfCourse(const string& academicYear, const string& semester, const Course& c, const Student& st) {
	string filePath = createCourseDirectoryWithFileName(academicYear, semester, c.ClassName, c.courseId, "txt");
	StudentCourseInformation* listInfo = nullptr, key;
	int countStudent = 0;
	bool res = false;

	key.st = st;

	if (loadStudentCourseInformationList(filePath, listInfo, countStudent))
	{
		int idx = findValue(listInfo, countStudent, sizeof(StudentCourseInformation), &key, isEqualStudentIdFromCourse);

		if (idx != NOT_FOUND)
			res = true;
		releaseStudentCourseInformationList(listInfo, countStudent);
	}

	return res;
}
void viewScores(const string& academicYear, const string& semester, const Student& st)
{
	Course course;
	StudentCourseInformation* listInfo, key;
	int countStudent = 0;

	if (getInputCourseOfStudent(academicYear, semester, course, st))
	{
		string filePath = createCourseDirectoryWithFileName(academicYear, semester, course.ClassName, course.courseId, "txt");
		if (loadStudentCourseInformationList(filePath, listInfo, countStudent))
		{
			key.st = st;
			int idx = findValue(listInfo, countStudent, sizeof(StudentCourseInformation), &key, isEqualStudentIdFromCourse);

			cout << "|" << setfill('-') << setw(146) << "-" << "|" << endl;
			cout << setfill(' ');

			cout << "| " << setw(27) << left << "Course name"
				<< " | " << setw(9) << left << "Course ID"
				<< " | " << setw(12) << left << "ID"
				<< " | " << setw(35) << left << "Full name"
				<< " | " << setw(10) << left << "Midterm"
				<< " | " << setw(10) << left << "Final"
				<< " | " << setw(10) << left << "Bonus"
				<< " | " << setw(10) << left << "Total" << " |" << endl;

			cout << "|" << setfill('-') << setw(146) << "-" << "|" << endl;
			cout << setfill(' ');

			cout << "| " << setw(27) << left << course.courseName
				<< " | " << setw(9) << left << course.courseId;
			viewScoreboardOfStudent(listInfo[idx].st, listInfo[idx].scoreList);

			cout << "|" << setfill('-') << setw(146) << "-" << "|" << endl;
			cout << setfill(' ');

			releaseStudentCourseInformationList(listInfo, countStudent);
		}
		else
			cout << "Can't open student file." << endl;
	}
	else
		cout << "Can't open class file (or there are no course for this student)" << endl;
}
bool getInputCourseOfStudent(const string& academicYear, const string& semester, Course& course, const Student& st) {
	string filename = PATH_DATA;
	string* listClassName;
	Course* listCourses, * tempCourse = nullptr;
	StudentCourseInformation key;
	int countClassName, countCourse, count = 0;
	bool res = false;

	filename += "Class.txt";
	if (loadListClassName(filename, listClassName, countClassName))
	{
		tempCourse = new Course[MAX_SIZE];
		key.st = st;

		for (int i = 0; i < countClassName; i++)
		{
			string courseFilePath = createCourseDirectoryWithFileName(academicYear, semester, listClassName[i], "Schedule", "txt");

			if (loadListCourses(courseFilePath, listCourses, countCourse))
			{
				for (int j = 0; j < countCourse; j++)
					if (checkStudentOfCourse(academicYear, semester, listCourses[i], st))
						tempCourse[count++] = listCourses[j];

				delete[] listCourses;
			}
			else
				break;
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

			int choice = getChoice(1, count);
			course = tempCourse[choice - 1];

			res = true;
		}

		delete[] tempCourse;
		delete[] listClassName;
	}

	return res;
}
bool checkStudent(Student st)
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
				if (checkElementInArray(studentList, countStudent, sizeof(Student), &st, isEqualStudentId))
					flag = true;

				delete[] studentList;
			}

			if (flag)
				break;
		}

		delete[] className;
	}

	return flag;
}