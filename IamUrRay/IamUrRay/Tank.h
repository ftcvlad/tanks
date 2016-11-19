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
	float x;
	float y;
	float x_speed;
	float y_speed;

	SDL_Rect* drawRect;
	SDL_Texture* texture;

	SDL_Texture* projectile_texture;
	vector<Projectile*>* projectiles;

	//constants
	float speedMax = 0.5;
public:
	Tank(SDL_Texture* texture, SDL_Texture* projectile_texture, vector<Projectile*>* peojectiles);
	~Tank();
	void Update(const Uint8* keyboardState);
	void Draw(SDL_Renderer* main_renderer);
	void initTank();
};

#endif