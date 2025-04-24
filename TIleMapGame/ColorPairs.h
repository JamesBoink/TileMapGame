#pragma once
#include "curses.h"
#include "ColorType.h"

class ColorPairs {
public:
	void initializeColors();
	short getColor(ColorType);
};