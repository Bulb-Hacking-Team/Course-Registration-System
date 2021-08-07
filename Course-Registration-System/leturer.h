#ifndef LECTURER_H_
#define LECTURER_H_
#include "student.h"
// Not compare password.
bool isEqualLecturer(void* val1, void* val2);

// Hàm hiển thị danh sách lớp và môn học mà giảng viên đang dạy.
// Học kỳ được nhập từ người dùng và lưu vào semester.
// Mã môn học và lớp được chọn sẽ lưu vào biến course.
// Hàm sẽ trả về true nếu chọn được courseID và ClassName, ngược lại trả về false.
bool getInputCourseOfLecturer(const string& academicYear, const string& semester, Course& course, Lecturer lec);

void* allocListLecturers(const int& countLecturer);

void copyLecturer(void* lec1, void* lec2);

void releaseListlecturers(void* listLecturers, const int& countLecturer);

Lecturer addNewLecturer();

void loadLecturer(ifstream& fin, Lecturer& lec);

void saveLecturer(ofstream& fout, const Lecturer& lec);

bool loadListLecturers(const string& filePath, Lecturer*& listLecturers, int& countLecturer);

bool saveListLecturers(const string& filePath, Lecturer*& listLecturers, int& countLecturer);

void loadScoreboardFromCsv(ifstream& fin, StudentCourseInformation& scoreInfo);

bool loadListScoreboardFromCsv(const string& filePath, StudentCourseInformation*& listInfo, int& countStudent);

void viewListStudentsOfCourse(const string& academicYear, const string& semester, const Lecturer& lec);

void viewScoreboardOfCourse(const string& academicYear, const string& semester, const Lecturer& lec);

void viewAttendanceListOfCourseForLecturer(const string& academicYear,
	const string& semester, Lecturer& lec);

void viewListCourses(const string& academicYear, const string& semester, Lecturer& lec);

void editGradeStudent(const string& academicYear, const string& semester, const Lecturer& lec);

void editAttendance(const string& academicYear, const string& semester, const Lecturer& lec);

void importScoreboardsOfCourse(const string& academicYear, const string& semester, const Lecturer& lec);

#endif