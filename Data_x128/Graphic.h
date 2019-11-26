#pragma once
#pragma warning(disable:4996)

#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class Color : char {
	BLACK,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	LIGHT_WHITE,
	GREY,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	YELLOW,
	WHITE
};

void gotoXY(const int& column, const int& line);
int whereX();
int whereY();

void textColor(const Color& color = Color::WHITE);
void textSize(const int& size);

void zoomFullConsoleWindow();
void removeScrollBar();
void fixConsoleWindow();

int getConsoleWidth();
int getConsoleHeight();

void printTextAtMiddle(int y, string text, Color color, bool endline);
void showConsoleCursor(bool show_flag);