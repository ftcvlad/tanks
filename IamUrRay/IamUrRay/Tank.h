#ifndef _TANK_H
#define _TANK_H
#include <SDL.h>
#include <iostream>
#include "Projectile.h"
#include <vector>
#include "MAP_CONSTANTS.h"

using namespace std;
class Tank
{
private:

	Constants::Direction direction;
	Constants::Direction prevDirection;
	Constants::Direction collisionDirection;

	float x;
	float y;
	
	int lives;

	SDL_Rect* drawRect;
	SDL_Texture* texture;

	SDL_Texture* projectile_texture;
	vector<Projectile*>* projectiles;

	//constants
	float speedMax = 0.1;

	bool cur_direction_collision = false;
	bool shot = false;

	bool dead = false;

public:
	float x_speed;
	float y_speed;
	Tank(SDL_Texture* texture, SDL_Texture* projectile_texture, vector<Projectile*>* peojectiles);
	~Tank();
	void Update(const Uint8* keyboardState);
	void Draw(SDL_Renderer* main_renderer);
	void initTank();
	bool collides(SDL_Rect* rectangle);
	void setBlocked();
	SDL_Rect* getRect();
	void die();
	void respawn();

	bool isDead(){ return dead; }
	void adjustXPosition();
	void adjustYPosition();
};
#endif