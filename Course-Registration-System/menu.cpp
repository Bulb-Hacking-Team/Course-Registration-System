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
					showMenuOfStudent();
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

void showMenuOfStudent()
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

