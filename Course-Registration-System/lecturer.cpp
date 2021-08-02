#include "leturer.h"

bool isEqualLecturer(void* val1, void* val2)
{
	Lecturer* lec1, * lec2;
	lec1 = (Lecturer*)val1;
	lec2 = (Lecturer*)val2;

	if (lec1->info.acc.username == lec2->info.acc.username)
		return true;

	return false;
}

void* allocListLecturers(const int& countLecturer)
{
	Lecturer* arr = new Lecturer[countLecturer];
	return arr;
}