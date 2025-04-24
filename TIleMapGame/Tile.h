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

	TileType tType;
		
	// Constructor with default enum value
	void assignTileData(int, int, TileType, char, short, int);
};