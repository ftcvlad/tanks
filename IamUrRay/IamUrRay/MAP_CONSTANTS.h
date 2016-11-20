#ifndef _MAP_CONSTANTS_H
#define _MAP_CONSTANTS_H
class Constants
{
public:

	enum Direction{ Up = 0, Right = 1, Down = 2, Left = 3, None = 4 };
	enum ProjectileOwner{ Friendly = 0, Enemy = 1 };

	static const int SCREEN_WIDTH = 832;
	static const int SCREEN_HEIGHT = 832;

	static const int NUM_TILES_VERTICAL = 13;
	static const int NUM_TILES_HORIZONTAL = 13;

	static const int TILE_WIDTH = 64;
	static const int TILE_HEIGHT = 64;

	static const int PROJECTILE_WIDTH = 5;
	static const int PROJECTILE_HEIGHT = 5;
	static const int PROJECTILE_SPEED = 1;


	static const int LIFE_COUNT = 10;

	static const int START_X = 9 * 32;
	static const int START_Y = (26 - 2) * 32;


	static const int START_X_1 = 0;
	static const int START_Y_1 = 0;

	static const int START_X_2 = 12*32;
	static const int START_Y_2 = 0;

	static const int START_X_3 = 24*32;
	static const int START_Y_3 = 0;


	

	static const int LIFE_COUNT = 5;

};


#endif

