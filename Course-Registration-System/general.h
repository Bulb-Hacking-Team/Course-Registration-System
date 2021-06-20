#ifndef GENERAL_INFORMATION_H_
#define GENERAL_INFORMATION_H_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#pragma pack(1)

#define DELIMIT_TXT 	   '\n'
#define PATH_DATA		   "D:/Vector A/KHTN/Nam 1/HKII/Ky Thuat Lap Trinh/LT/Do An Cuoi Ky/Quay Video/2/Commit Strategy/Vuong/data/output/"

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