#include "Tile2.h"


Tile2::Tile2(SDL_Rect* rec, bool canInt, bool destroyable, int pos, int t)
{
	rect = rec;
	canIntersect = canInt;
	canDestroy = destroyable;
	position = pos;
	type = t;
}


Tile2::~Tile2()
{
}
