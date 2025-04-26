#pragma once
#include"curses.h"

class Tile;
class Hero;
class MapParameters;

class TileMap {
private:
public:
	int rows;
	int columns;
	Tile** map;

	WINDOW* mapWin;

	Hero& hero;

	int oldHeroX;
	int oldHeroY;


	//Constructor without default values
	TileMap(int rows, int columns, MapParameters& mP, WINDOW* win, Hero& h);
	//Destructor that cleans up the tilemap
	~TileMap();
	void updatePlayerPosition();
	void gather(int x, int y);
	void build(int x, int y);
};