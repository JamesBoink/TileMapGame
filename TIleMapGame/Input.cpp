#include "Input.h"

#include "TileMap.h"
#include "Tile.h"
#include "TileType.h"

#include "Hero.h"
#include "PlayerMode.h"
#include "BuildingType.h"

#include "curses.h"

#include <iostream>

bool Input::handleInput() {
    map.oldHeroX = hero.x;
    map.oldHeroY = hero.y;

    playerInput = getch();
    if (playerInput == 'q') {
        return false;
    }

    switch (playerInput) {
    case 'm':
        mode = PlayerMode::Move;
        wmove(map.mapWin, hero.x, hero.y);
        waddch(map.mapWin, int('@') | COLOR_PAIR(3) | A_BOLD);
        break;

    case 'b':
        wmove(map.mapWin, hero.x, hero.y);
        if (mode == PlayerMode::Build) {
            mode = PlayerMode::Move;
            waddch(map.mapWin, int('@') | COLOR_PAIR(3) | A_BOLD);
        }
        else {
            mode = PlayerMode::Build;
            waddch(map.mapWin, int('@') | COLOR_PAIR(8) | A_BOLD);
        }
        break;

    case 'g':
        wmove(map.mapWin, hero.x, hero.y);
        if (mode == PlayerMode::Gather) {
            mode = PlayerMode::Move;
            waddch(map.mapWin, int('@') | COLOR_PAIR(3) | A_BOLD);
        }
        else {
            mode = PlayerMode::Gather;
            waddch(map.mapWin, int('@') | COLOR_PAIR(7) | A_BOLD);
        }
        break;

    case '1':
        hero.buildingType = BuildingType::WoodWall;
        break;

    case '2':
        hero.buildingType = BuildingType::WoodDoor;
        break;

    case '3':
        hero.buildingType = BuildingType::StoneWall;
        break;

    case '4':
        hero.buildingType = BuildingType::Floor;
        break;
    }

    hero.mode = mode;
    handleActions();

    return true;
}

Input::Input(TileMap& m, Hero& h) : map(m), hero(h), mode(PlayerMode::Move) {
    
} 

//@TODO - refactor this monstrosity :D 
void Input::handleActions() {
    int dx = 0, dy = 0;

    switch (playerInput) {
    case 'a': dy = -1; break;
    case 'd': dy = 1; break;
    case 'w': dx = -1; break;
    case 's': dx = 1; break;
    default: return; // Invalid input, do nothing
    }

    int newX = hero.x + dx;
    int newY = hero.y + dy;

    // Safety check
    if (newX < 0 || newY < 0 || newX >= map.columns || newY >= map.rows)
        return;

    TileType targetTile = map.map[newX][newY].tType;

    if (mode == PlayerMode::Move) {
        if (targetTile == TileType::Dirt || targetTile == TileType::Door || targetTile == TileType::Floor) {
            hero.x = newX;
            hero.y = newY;
        }
    }
    else if (mode == PlayerMode::Gather) {
        if (targetTile != TileType::Dirt) {
            map.gather(newX, newY);
        }
    }
    else { // Build mode
        if (targetTile == TileType::Dirt) {
            map.build(newX, newY);
        }
    }
}

