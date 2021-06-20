#ifndef GENERAL_INFORMATION_H_
#define GENERAL_INFORMATION_H_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Account
{
	string username, password;
};

struct GeneralInformation
{
	string fullName;
	bool gender;
	Account acc;
};

struct Staff
{
	GeneralInformation info;
};

struct Student
{
	GeneralInformation info;
	string id, dateOfBirth, ClassName;
	bool status;
};

#endif