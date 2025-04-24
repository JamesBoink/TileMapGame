#include "MapParameters.h"

MapParameters::MapParameters( int tSC, int bTSC, int tY, int bTY, int rSC, int bRSC, int rY, int bRY, int wSC, int wY, int tR) {
	rockSpawnChance = rSC;
	bigRockSpawnChance = bRSC;
	rockYield = rY;
	bigRockYield = bRY;

	treeSpawnChance = tSC;
	treeYield = tY;
	bigTreeSpawnChance = bTSC;
	bigTreeYield = bTY;

	waterSpawnChance = wSC;
	waterYield = wY;

	totalResourceSpawns = tR;
}