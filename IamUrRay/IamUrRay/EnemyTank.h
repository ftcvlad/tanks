#ifndef _ENEMY_TANK_H
#define _ENEMY_TANK_H
#include <SDL.h>
#include <SDL_image.h>
#include "MAP_CONSTANTS.h"
#include <cstdlib>
#include <time.h>
#include "Projectile.h"
#include <iostream>
#include <vector>

using namespace std;
class EnemyTank
{
private:
	SDL_Texture* curTexture;
	SDL_Texture* lowTexture;
	SDL_Texture* middleTexture;
	SDL_Texture* highTexture;

	SDL_Rect* drawRect;

	SDL_Texture* projectile_texture;
	vector<Projectile*>* projectiles;
	
	bool active;
	bool reloading;

	Constants::Direction direction;

	

	int lives;

	float speedLimit = 0.1;

	int totalReloadTime;
	int elapsedReloadTime;

	void shoot();

public:
	EnemyTank(SDL_Texture* lowTexture, SDL_Texture* middleTexture, SDL_Texture* highTexture, int x, int y, Constants::Direction direction, SDL_Texture* projectile_texture, vector<Projectile*>* projectiles, int lives);
	~EnemyTank();

	void Update();
	void Draw(SDL_Renderer* renderer);
	void changeDirection();

	SDL_Rect* getRect(){ return drawRect; }
	float x_speed;
	float y_speed;
	void die();
	bool isActive(){ return active; }


	float x;
	float y;
};

#endif