#ifndef _TILE_zzz
#define _TILE_zzz
#include <SDL.h>


class Tile2
{
public:
	Tile2(SDL_Rect* rec, bool canIntersect, bool destroyable, int position, int type);
	~Tile2();

	SDL_Rect* rect;
	bool canIntersect;
	bool canDestroy;
	int position;
	int type;
};


#endif


