// TIleMapGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TileMap.h"
#include "MapParameters.h"
#include "Input.h"
#include "DisplayWindow.h"
#include "Hero.h"
#include "ColorPairs.h"

int main(){
    initscr();      // Initialize the screen
    start_color();  // Enable colors
    cbreak();       // Line buffering disabled
    noecho();       // Don't echo keystrokes
    keypad(stdscr, TRUE); // Enable special keys
    raw();          // Raw input mode
    curs_set(0);

    PDC_set_blink(true);
    PDC_set_bold(true);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);    // MainWindow
    init_pair(2, COLOR_WHITE, COLOR_BLACK);    // MapWindow

    init_pair(3, COLOR_CYAN , COLOR_BLACK);    // Player Move
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);  // Player Gather
    init_pair(8, COLOR_RED, COLOR_BLACK);      // Player Build
    init_pair(10, COLOR_YELLOW, COLOR_CYAN);   // Player Wooden Build
    init_pair(11, COLOR_BLACK, COLOR_CYAN);    // Player Stone Build
    init_pair(12, COLOR_BLACK, COLOR_YELLOW);  // Player Wooden Floor Build

    init_pair(4, COLOR_YELLOW, COLOR_BLACK);   // Ground
    init_pair(5, COLOR_GREEN, COLOR_BLACK);    // Tree
    init_pair(6, COLOR_WHITE, COLOR_BLACK);    // Rock
    init_pair(9, COLOR_BLUE, COLOR_BLUE);     // Water

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);  // Gets terminal dimensions      
       
    DisplayWindow* window = new DisplayWindow(max_y, max_x);
   
    Hero hero;
    hero.initialize();
   
    //int totalResources = ((max_x - 5) * (max_y - 5)) / 5;
    MapParameters* mapParams = new MapParameters
    (25, 18, 4, 10,   // tree spawn chance, big tree spawn chance, tree yield, big tree yield
     10, 5, 3, 6,     // rock spawn chance, big rock spawn chance, rock yield, big rock yield 
     2, 3,            // water spawn chance, water yield
     0);              // total resources - unused now

    TileMap* tileMap = new TileMap(max_x - 5, max_y - 5, mapParams, window->mapWin, hero);
    delete mapParams;

    Input input(tileMap, hero);

    bool isRunning = true;
    while (isRunning) {
        //since quitting is dependent on 'q' button
        //listen to player input and make it decisive of game running
        isRunning = input.handleInput();
        tileMap->updatePlayerPosition();

        mvwprintw(window->mainWin, 0, 0, "                                    ");  // Clear with spaces
        mvwprintw(window->mainWin, 1, 0, "                                    ");
        mvwprintw(window->mainWin, 0, 0, "Wood: %d", hero.wood);
        mvwprintw(window->mainWin, 1, 0, "Stones: %d", hero.stone);
        mvwprintw(window->mainWin, 2, 0, "Water: %d", hero.water);
        mvwprintw(window->mainWin, 0, 15, "Mode: %s", hero.getMode());
        mvwprintw(window->mainWin, 1, 15, "Build: %s", hero.getBuild());



        wrefresh(window->mainWin);
        wrefresh(window->mapWin);
        refresh();
    }

    delete tileMap;
    delete window;
    clear();
    endwin();

    return 0;
}

