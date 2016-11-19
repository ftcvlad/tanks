#ifndef _MAP_CONSTANTS_H
#define _MAP_CONSTANTS_H
class Constants
{
public:

	enum Direction{ Up = 0, Right = 1, Down = 2, Left = 3 };


	static const int SCREEN_WIDTH = 832;
	static const int SCREEN_HEIGHT = 832;

	static const int NUM_TILES_VERTICAL = 13;
	static const int NUM_TILES_HORIZONTAL = 13;




	static const int TILE_WIDTH = 64;
	static const int TILE_HEIGHT = 64;

	static const int PROJECTILE_WIDTH = 5;
	static const int PROJECTILE_HEIGHT = 5;
	static const int PROJECTILE_SPEED = 5;
};


#endif

