#include "TileMap.h"
#include <stdlib.h>
#include <iostream>


TileMap::TileMap(int r, int c, MapParameters* mp, WINDOW* win, Hero& h) : rows(r), columns(c), hero(h) {
    map = new Tile * [columns];
    int randomInt = 0;
    
    mapWin = win;
   // int resources = 0;
    for (int x = 0; x < columns; x++) {
      
        map[x] = new Tile[rows];
    
        for (int y = 0; y < rows; y++) {

            wmove(mapWin, x, y);

            if (x == hero.x && y == hero.y) {
                map[x][y].assignTileData(x, y, TileType::Dirt, '.', 4, 0);
                waddch(mapWin, int('@') | COLOR_PAIR(3) | A_BOLD);
                continue;
            }

             randomInt = rand() % 100;
           
             //@TODO redo the entire loop - after creating entire map
             //in the next step apply the resources using various algorithms
             //perlin for water and some random shit for other stuff 

     /*       if (randomInt <= mp->treeSpawnChance && resources < mp->totalResourceSpawns) {
                resources++;

                if (randomInt < mp->treeSpawnChance && randomInt >  mp->bigTreeSpawnChance) {
                    map[x][y].assignTileData(x, y, TileType::Tree, 't', 5, mp->treeYield);
                    waddch(mapWin, int('t') | COLOR_PAIR(5));
                }
                else if (randomInt < mp->bigTreeSpawnChance && randomInt > mp->rockSpawnChance) {
                    map[x][y].assignTileData(x, y, TileType::Tree, 'T', 5, mp->bigTreeYield);
                    waddch(mapWin, int('T') | COLOR_PAIR(5) | A_BOLD);
                }
                else if (randomInt < mp->rockSpawnChance && randomInt > mp->bigRockSpawnChance) {
                    map[x][y].assignTileData(x, y, TileType::Rock, 'r', 6, mp->rockYield);
                    waddch(mapWin, int('r') | COLOR_PAIR(6));
                }
                else if (randomInt < mp->bigRockSpawnChance && randomInt > mp->waterSpawnChance) {
                    map[x][y].assignTileData(x, y, TileType::Rock, 'R', 6, mp->bigRockYield);
                    waddch(mapWin, int('R') | COLOR_PAIR(6) | A_BOLD);
                }
                else if (randomInt < mp->waterSpawnChance) {
                    map[x][y].assignTileData(x, y, TileType::Water, 'w', 5, mp->waterYield);
                    waddch(mapWin, int('w') | COLOR_PAIR(9)); 
                }
            }*/
            if (randomInt < mp->treeSpawnChance && randomInt >  mp->bigTreeSpawnChance) {
                map[x][y].assignTileData(x, y, TileType::Tree, 't', 5, mp->treeYield);
                waddch(mapWin, int('t') | COLOR_PAIR(5));
            }
            else if (randomInt < mp->bigTreeSpawnChance && randomInt > mp->rockSpawnChance) {
                map[x][y].assignTileData(x, y, TileType::Tree, 'T', 5, mp->bigTreeYield);
                waddch(mapWin, int('T') | COLOR_PAIR(5) | A_BOLD);
            }
            else if (randomInt < mp->rockSpawnChance && randomInt > mp->bigRockSpawnChance) {
                map[x][y].assignTileData(x, y, TileType::Rock, 'r', 6, mp->rockYield);
                waddch(mapWin, int('r') | COLOR_PAIR(6));
            }
            else if (randomInt < mp->bigRockSpawnChance && randomInt > mp->waterSpawnChance) {
                map[x][y].assignTileData(x, y, TileType::Rock, 'R', 6, mp->bigRockYield);
                waddch(mapWin, int('R') | COLOR_PAIR(6) | A_BOLD);
            }
            else if (randomInt < mp->waterSpawnChance) {
                map[x][y].assignTileData(x, y, TileType::Water, 'w', 5, mp->waterYield);
                waddch(mapWin, int('w') | COLOR_PAIR(9));
            }
            else {
                map[x][y].assignTileData(x, y, TileType::Dirt, '.', 4, 0);
                waddch(mapWin, int('.') | COLOR_PAIR(4));
            }
            
            
            wrefresh(mapWin);
            refresh();
        }
    }
}

TileMap::~TileMap() {
    for (int x = 0; x < columns; x++) {
        delete[] map[x];
    }
    delete[] map;
}

void TileMap::updatePlayerPosition() {
    if (oldHeroX != hero.x || oldHeroY != hero.y) {
        wmove(mapWin, oldHeroX, oldHeroY);
        waddch(mapWin, int(map[oldHeroX][oldHeroY].c) | COLOR_PAIR(map[oldHeroX][oldHeroY].col));

        wmove(mapWin, hero.x, hero.y);
        waddch(mapWin, int('@') | COLOR_PAIR(3) | A_BOLD);
    }
}

void TileMap::gather(int x, int y) {
    wmove(mapWin, x, y);
   
    if (map[x][y].tType == TileType::Tree || map[x][y].tType == TileType::WoodWall || map[x][y].tType == TileType::Floor || map[x][y].tType == TileType::Door) {
        hero.wood += map[x][y].yield;
    }
    else if (map[x][y].tType == TileType::Rock || map[x][y].tType == TileType::StoneWall) {
        hero.stone += map[x][y].yield;
    }
    else if (map[x][y].tType == TileType::Water) {
        hero.water += map[x][y].yield;
    }

    map[x][y].assignTileData(x, y, TileType::Dirt, '.', 4, 0);
    waddch(mapWin, int('.') | COLOR_PAIR(4));
}

void TileMap::build(int x, int y) {
    wmove(mapWin, x, y);

    switch (hero.buildingType) {
    case BuildingType::WoodWall:
        if (hero.wood > 0 && map[x][y].tType == TileType::Dirt) {
            hero.wood--;

            map[x][y].assignTileData(x, y, TileType::WoodWall, 'x', 10, 1);
            waddch(mapWin, int('x') | COLOR_PAIR(10) | A_BOLD);
        }
        break;
    case BuildingType::WoodDoor:
        if ((hero.wood - 2) >= 0 && map[x][y].tType == TileType::Dirt) {
            hero.wood -= 2;

            map[x][y].assignTileData(x, y, TileType::Door, 'D', 10, 2);
            waddch(mapWin, int('D') | COLOR_PAIR(10));
        }
        break;
    case BuildingType::StoneWall:
        if (hero.stone > 0 && map[x][y].tType == TileType::Dirt) {
            hero.stone--;

            map[x][y].assignTileData(x, y, TileType::StoneWall, 's', 11, 1);
            waddch(mapWin, int('s') | COLOR_PAIR(11));
        }
        break;
    case BuildingType::Floor:
        if (hero.wood > 0 && map[x][y].tType == TileType::Dirt) {
            hero.wood--;

            map[x][y].assignTileData(x, y, TileType::Floor, '.', 12, 1);
            waddch(mapWin, int('.') | COLOR_PAIR(12));
        }
        break;
    }
}
