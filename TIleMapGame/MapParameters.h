#pragma once

class MapParameters {
public:
	int rockSpawnChance;
	int bigRockSpawnChance;
	int rockYield;
	int bigRockYield;

	int treeSpawnChance;
	int bigTreeSpawnChance;
	int treeYield;
	int bigTreeYield;

	int waterSpawnChance;
	int waterYield;

	int totalResourceSpawns;
	MapParameters(int, int, int, int, int, int, int, int, int, int, int);
};