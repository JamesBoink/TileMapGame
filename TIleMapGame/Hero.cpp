#include "Hero.h"

void Hero::initialize() {
	x = 5;
	y = 5;
	wood = 0;
	stone = 0;
	water = 0;
	health = 10;
	buildingType = BuildingType::WoodWall;
	mode = PlayerMode::Move;
}

const char* Hero::getMode() {
	switch (mode) {
	case PlayerMode::Move:
		return "Move";
	case PlayerMode::Gather:
		return "Gather";
	case PlayerMode::Build:
		return "Build";
	default:
		return "";
	}
}

const char* Hero::getBuild() {
	switch (buildingType) {
	case BuildingType::WoodWall:
		return "Wood Wall";
	case BuildingType::StoneWall:
		return "Stone Wall";
	case BuildingType::WoodDoor:
		return "Wood Door";
	case BuildingType::Floor:
		return "Floor";
	}
}