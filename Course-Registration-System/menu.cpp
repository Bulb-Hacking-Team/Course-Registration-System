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

void showMenuOfStaff()
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

