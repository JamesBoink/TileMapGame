#include "Tile.h"

void Tile::assignTileData(int x, int y, TileType type,chtype chType, char c, short col, int yield) {
	this->x = x;
	this->y = y;
	this->tType = type;
	this->chType = chType;
	this->c = c;
	this->col = col;
	this->yield = yield;
}