#include "Graphic.h"

void gotoXY(const int& column, const int& line) {
	COORD coord = { SHORT(column), SHORT(line) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int whereX() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}


int whereY() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}


void textColor(const Color& color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(color));
}


void textSize(const int& size) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;						// Width of each character in the font
	cfi.dwFontSize.Y = size;					// Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Consolas");			// Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


void zoomFullConsoleWindow() {
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}


void removeScrollBar() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size = { SHORT(getConsoleWidth()), SHORT(getConsoleHeight()) };
	SetConsoleScreenBufferSize(handle, new_size);
}


void fixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}


int getConsoleWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	return columns;
}


int getConsoleHeight() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return rows;
}


void printTextAtMiddle(int y, string text, Color color, bool endline)
{
	textColor(color);
	gotoXY(getConsoleWidth() / 2 - int(text.length()) / 2, y);
	cout << text;
	if (endline == true) {
		std::cout << endl;
	}
	textColor();
}


void showConsoleCursor(bool showFlag)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set cursor's visibility
	SetConsoleCursorInfo(output, &cursorInfo);
}