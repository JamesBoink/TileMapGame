#pragma once

enum class BuildingType;
enum class PlayerMode;

class Hero {
public:
	int x;
	int y;
	int health;
	int wood;
	int stone;
	int water;
	BuildingType buildingType;
	PlayerMode mode;

	void initialize();
	const char* getMode();
	const char* getBuild();
};