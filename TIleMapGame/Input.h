#pragma once
#include "TileMap.h"
#include "Hero.h"
#include "PlayerMode.h"

class Input {
public:
	char playerInput;
	TileMap* map;
    Hero& hero;

	PlayerMode mode;
	
	Input(TileMap* m, Hero& h);
	bool handleInput();
	void handleActions();
};
