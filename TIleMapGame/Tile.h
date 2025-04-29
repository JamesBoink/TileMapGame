#pragma once
#include "TileType.h"
#include "ColorPairs.h"


class Tile {
public:
	int x;
	int y;
	char c;
	short col;
	int yield;
	chtype chType;

	TileType tType;
		
	// Constructor with default enum value
	void assignTileData(int, int, TileType,chtype, char, short, int);
};