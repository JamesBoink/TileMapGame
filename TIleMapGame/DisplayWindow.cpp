#include "DisplayWindow.h"

DisplayWindow::DisplayWindow(int w, int h) {
	width = w;
	height = h;

    mainWin = newwin(width, height, 0, 0);
    mapWin = derwin(mainWin, width-5, height-5, 3, 3);
	

	box(mainWin, 0, 0);
	wrefresh(mainWin);
	wrefresh(mapWin);

	mvwaddstr(mainWin, 0, 0, "Wood: ");
	mvwaddstr(mainWin, 1, 0, "Stones: ");

	wcolor_set(mainWin, 1, nullptr);
	wcolor_set(mapWin, 2, nullptr);
}

DisplayWindow::~DisplayWindow() {
	delete mainWin;
	delete mapWin;
}

void DisplayWindow::createWindow() {

}