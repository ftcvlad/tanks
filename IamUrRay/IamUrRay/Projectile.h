#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include <SDL.h>
#include <SDL_image.h>
#include "MAP_CONSTANTS.h"

class Projectile
{
private:
	SDL_Texture* texture;
	SDL_Rect* drawRect;
	
	Constants::ProjectileOwner owner;
	bool active;

	int speedx;
	int speedy;
public:

	Projectile(SDL_Texture* texture, Constants::Direction dir, int x, int y, Constants::ProjectileOwner owner);

	~Projectile();
	void Update();
	void Draw(SDL_Renderer* renderer);

	//accessors and mutators
	bool getActive(){ return active; }
	void setActive(bool new_active){ active = new_active; }
	Constants::ProjectileOwner getOwner(){ return owner; }
	SDL_Rect* getRect(){ return drawRect; }
	
	int updateEvetyNthTime = 2;
};
#endif

