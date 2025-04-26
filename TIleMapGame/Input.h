#pragma once

class TileMap;
class Hero;
enum class PlayerMode;

class Input {
public:
	char playerInput;
	TileMap& map;
    Hero& hero;

	PlayerMode mode;
	
	Input(TileMap& m, Hero& h);
	bool handleInput();
	void handleActions();
};
