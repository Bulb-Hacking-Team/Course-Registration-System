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