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
	

	bool active;

	int speedx;
	int speedy;
public:
	Projectile(SDL_Texture* texture, Constants::Direction dir);
	~Projectile();
	void Update();
	void Draw(SDL_Renderer* renderer);

	//accessors and mutators
	bool getActive(){ return active; }
	bool setActive(bool new_active){ active = new_active; }
	
};
#endif

