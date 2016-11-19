#include "Projectile.h"

#include <iostream>
using namespace std;
Projectile::Projectile(SDL_Texture* texture, Constants::Direction dir, int x, int y)
{
	this->texture = texture;
	active = true;
	drawRect = new SDL_Rect();
	drawRect->x = x;
	drawRect->y = y;

	SDL_QueryTexture(texture, NULL, NULL, &drawRect->w, &drawRect->h);

	switch (dir)
	{
	case Constants::Up:
		speedy = -Constants::PROJECTILE_SPEED;
		break;
	case Constants::Down:
		speedy = Constants::PROJECTILE_SPEED;
		break;
	case Constants::Left:
		speedx = -Constants::PROJECTILE_SPEED;
		break;
	case Constants::Right:
		speedx = Constants::PROJECTILE_SPEED;
		break;
	}
}


Projectile::~Projectile()
{
	SDL_DestroyTexture(texture);
	delete drawRect;
}

void Projectile::Update()
{
	drawRect->x += speedx;
	drawRect->y += speedy;
	if (drawRect->x >= Constants::SCREEN_WIDTH || drawRect->x+drawRect->h <= 0 || drawRect->y <= 0 || drawRect->y >= Constants::SCREEN_HEIGHT)
		active = false;
}

void Projectile::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, drawRect);
}
