#ifndef MENU_H_
#define MENU_H_
#include "general.h"


#include<iostream>
using namespace std;

void showMenu();
void showMenuOfStudent();
void showMenuOfStaff();
int getChoice(const int& minValue, const int& maxValue);

#endif