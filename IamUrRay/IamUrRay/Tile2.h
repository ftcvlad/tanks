#ifndef _TILE_zzz
#define _TILE_zzz
#include <SDL.h>


class Tile2
{
public:
	Tile2(SDL_Rect* rec, bool canIntersect);
	~Tile2();

	SDL_Rect* rect;
	bool canIntersect;
};


#endif


