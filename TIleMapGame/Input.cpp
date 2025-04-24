#include <iostream>
#include "curses.h"

#include "Input.h"

bool Input::handleInput() {
    map->oldHeroX = hero.x;
    map->oldHeroY = hero.y;

	playerInput = getch();
	if (playerInput == 'q') {
		return false;
	}

    if (playerInput == 'm') {
        // changing mode to move
        mode = PlayerMode::Move;
        
        wmove(map->mapWin, hero.x, hero.y);
        waddch(map->mapWin, int('@') | COLOR_PAIR(3) | A_BOLD);
    }

    if (playerInput == 'b') {
        wmove(map->mapWin, hero.x, hero.y);

        // changing mode to build
        if (mode == PlayerMode::Build) {
            mode = PlayerMode::Move;
            waddch(map->mapWin, int('@') | COLOR_PAIR(3) | A_BOLD);
        }
        else {
            mode = PlayerMode::Build;
            waddch(map->mapWin, int('@') | COLOR_PAIR(8) | A_BOLD);
        }

    }

    if (playerInput == 'g') {
        wmove(map->mapWin, hero.x, hero.y);

        // changing mode to gather
        if (mode == PlayerMode::Gather) {
            mode = PlayerMode::Move;
            waddch(map->mapWin, int('@') | COLOR_PAIR(3) | A_BOLD);
        }
        else {
            mode = PlayerMode::Gather;
            waddch(map->mapWin, int('@') | COLOR_PAIR(7) | A_BOLD);
        }
    }

    if (playerInput == '1') {
        hero.buildingType = BuildingType::WoodWall;
    }
    if (playerInput == '2') {
        hero.buildingType = BuildingType::WoodDoor;
    }
    if (playerInput == '3') {
        hero.buildingType = BuildingType::StoneWall;
    }
    if (playerInput == '4') {
        hero.buildingType = BuildingType::Floor;
    }

    hero.mode = mode;

    handleActions();
   

	return true;
}

Input::Input(TileMap* m, Hero& h) : map(m), hero(h), mode(PlayerMode::Move) {
    
} 

void Input::handleActions() {
    if (mode == PlayerMode::Move) {
        if (playerInput == 'a' && hero.y > 0 && (map->map[hero.x][hero.y - 1].tType == TileType::Dirt || map->map[hero.x][hero.y - 1].tType == TileType::Door || map->map[hero.x][hero.y - 1].tType == TileType::Floor)) {// a
            hero.y -= 1;
        }
        if (playerInput == 'd' && hero.y < map->rows - 1 && (map->map[hero.x][hero.y + 1].tType == TileType::Dirt|| map->map[hero.x][hero.y + 1].tType == TileType::Door || map->map[hero.x][hero.y + 1].tType == TileType::Floor)) {//d
            hero.y++;
        }
        if (playerInput == 'w' && hero.x > 0 && (map->map[hero.x - 1][hero.y].tType == TileType::Dirt || map->map[hero.x - 1][hero.y].tType == TileType::Door || map->map[hero.x - 1][hero.y].tType == TileType::Floor)) {//w
            hero.x -= 1;
        }
        if (playerInput == 's' && hero.x < map->columns - 1 && (map->map[hero.x + 1][hero.y].tType == TileType::Dirt || map->map[hero.x + 1][hero.y].tType == TileType::Door || map->map[hero.x + 1][hero.y].tType == TileType::Floor)) {// s
            hero.x++;
        }
    }
    else if (mode == PlayerMode::Gather) {
        if (playerInput == 'a' &&  map->map[hero.x][hero.y - 1].tType != TileType::Dirt) {// a
            map->gather(hero.x, hero.y - 1);
        }
        if (playerInput == 'd' &&  map->map[hero.x][hero.y + 1].tType != TileType::Dirt) {//d
            map->gather(hero.x, hero.y + 1);
        }
        if (playerInput == 'w' &&  map->map[hero.x - 1][hero.y].tType != TileType::Dirt) {//w
            map->gather(hero.x - 1, hero.y);
        }
        if (playerInput == 's' &&  map->map[hero.x + 1][hero.y].tType != TileType::Dirt) {// s
            map->gather(hero.x + 1, hero.y);
        }
    }
    else {
        if (playerInput == 'a' && map->map[hero.x][hero.y - 1].tType == TileType::Dirt) {// a
            map->build(hero.x, hero.y - 1);
        }
        if (playerInput == 'd' && map->map[hero.x][hero.y + 1].tType == TileType::Dirt) {//d
            map->build(hero.x, hero.y + 1);
        }
        if (playerInput == 'w' && map->map[hero.x - 1][hero.y].tType == TileType::Dirt) {//w
            map->build(hero.x - 1, hero.y);
        }
        if (playerInput == 's' && map->map[hero.x + 1][hero.y].tType == TileType::Dirt) {// s
            map->build(hero.x + 1, hero.y);
        }
    }
}
