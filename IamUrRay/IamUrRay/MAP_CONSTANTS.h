#ifndef _MAP_CONSTANTS_H
#define _MAP_CONSTANTS_H
class Constants
{
public:
	enum Direction{ Up = 0, Right = 1, Down = 2, Left = 3, None = 4 };
	enum ProjectileOwner{ Friendly = 0, Enemy = 1 };

	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 850;

	static const int SCREEN_WIDTH = 832;
	static const int SCREEN_HEIGHT = 832;

	static const int NUM_TILES_VERTICAL = 13;
	static const int NUM_TILES_HORIZONTAL = 13;

	static const int TILE_WIDTH = 64;
	static const int TILE_HEIGHT = 64;

	static const int PROJECTILE_WIDTH = 5;
	static const int PROJECTILE_HEIGHT = 5;
	static const int PROJECTILE_SPEED = 1;

	static const int LIFE_COUNT = 5;

	static const int TARGET_KILLS = 20;

	static const int TANK_ICON_WIDTH = 40;
	static const int TANK_ICON_HEIGHT = 40;
	static const int TANK_ICON_FIRSTX = 842;
	static const int TANK_ICON_FIRSTY = 30;

	static const int FLAG_ICON_WIDTH = 40;
	static const int FLAG_ICON_HEIGHT = 40;
	static const int FLAG_ICON_FIRSTX = 842;
	static const int FLAG_ICON_FIRSTY = 400;

};


#endif

