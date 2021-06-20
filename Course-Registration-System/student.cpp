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