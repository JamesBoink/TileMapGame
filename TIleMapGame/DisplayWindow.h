#pragma once
#include "curses.h" 

class DisplayWindow {
public:
	int width;
	int height;
	WINDOW* mainWin;
	WINDOW* mapWin;

	DisplayWindow(int, int);
	~DisplayWindow();
};
