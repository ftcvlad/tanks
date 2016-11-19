#include "Tile2.h"


Tile2::Tile2(SDL_Rect* rec, bool canInt)
{
	rect = rec;
	canIntersect = canInt;
}


Tile2::~Tile2()
{
}
