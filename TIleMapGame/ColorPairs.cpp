#include "ColorPairs.h"


void ColorPairs::initializeColors() {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);    // MapWindow

    init_pair(2, COLOR_CYAN, COLOR_BLACK);     // Player Move
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);  // Player Gather
    init_pair(4, COLOR_RED, COLOR_BLACK);      // Player Build
    init_pair(5, COLOR_YELLOW, COLOR_CYAN);   // Player Wooden Build
    init_pair(6, COLOR_BLACK, COLOR_CYAN);    // Player Stone Build
    init_pair(7, COLOR_BLACK, COLOR_YELLOW);  // Player Wooden Floor Build

    init_pair(8, COLOR_YELLOW, COLOR_BLACK);   // Ground
    init_pair(9, COLOR_GREEN, COLOR_BLACK);    // Tree
    init_pair(10, COLOR_WHITE, COLOR_BLACK);    // Rock
    init_pair(11, COLOR_BLUE, COLOR_BLACK);     // Water
}

short ColorPairs::getColor(ColorType type) {
    switch(type) {
    case(ColorType::MapWindow):
        return 1;
    case(ColorType::PlayerMoveMode):
        return 2;
    case(ColorType::PlayerGatherMode):
        return 3;
    case(ColorType::PlayerBuildMode):
        return 4;
    case(ColorType::WoodenBuilding):
        return 5;
    case(ColorType::StoneBuilding):
        return 6;
    case(ColorType::Floor):
        return 7;
    case(ColorType::Ground):
        return 8;
    case(ColorType::Tree):
        return 9;
    case(ColorType::Rock):
        return 10;
    case(ColorType::Water):
        return 11;
    }
}