#include "Tank.h"


using namespace std;

Tank::Tank(SDL_Texture* texture, SDL_Texture* projectile_texture, vector<Projectile*>* projectiles)
{
	this->texture = texture;
	this->projectile_texture = projectile_texture;
	this->projectiles = projectiles;
	initTank();
}


Tank::~Tank()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
	delete drawRect;
}

void Tank::Update(const Uint8* keyboardState)
{
	x_speed = 0;
	y_speed = 0;
	if (keyboardState[SDL_SCANCODE_W])
	{
		y_speed = -speedMax;
		direction = Constants::Up;
	}
	else if (keyboardState[SDL_SCANCODE_S])
	{
		y_speed = speedMax;
		direction = Constants::Down;
	}
	else if (keyboardState[SDL_SCANCODE_A])
	{
		x_speed = -speedMax;
		direction = Constants::Left;
	}
	else if (keyboardState[SDL_SCANCODE_D])
	{
		x_speed = speedMax;
		direction = Constants::Right;
	}

	if (!cur_direction_collision)
	{
		x += x_speed;
		y += y_speed;
	}
	else
	{
		if (prevDirection == direction)
		{
			x_speed = 0;
			y_speed = 0;
		}
	}
	cur_direction_collision = false;

	if (keyboardState[SDL_SCANCODE_SPACE] && !shot)
	{
		shot = true;
		projectiles->push_back(new Projectile(projectile_texture, direction, drawRect->x + (drawRect->w / 2), drawRect->y + (drawRect->h / 2), Constants::Friendly));
	}
	else if (!keyboardState[SDL_SCANCODE_SPACE])
		shot = false;

	if (x + drawRect->w >= Constants::SCREEN_WIDTH)
		x = Constants::SCREEN_WIDTH - drawRect->w;
	else if (x <= 0)
		x = 0;

	if (y + drawRect->h >= Constants::SCREEN_HEIGHT)
		y = Constants::SCREEN_HEIGHT - drawRect->h;
	else if (y <= 0)
		y = 0;


	drawRect->x = x;
	drawRect->y = y;

	prevDirection = direction;

//	cout << "PlayerX: " << drawRect->x << "\nPlayerY: " << drawRect->y << endl;
}

void Tank::Draw(SDL_Renderer* renderer)
{
	switch (direction)
	{
	case Constants::Up:
		SDL_RenderCopyEx(renderer, texture, NULL, drawRect, 0, NULL, SDL_FLIP_NONE);
		break;
	case Constants::Down:
		SDL_RenderCopyEx(renderer, texture, NULL, drawRect, 180, NULL, SDL_FLIP_NONE);
		break;
	case Constants::Right:
		SDL_RenderCopyEx(renderer, texture, NULL, drawRect, 90, NULL, SDL_FLIP_NONE);
		break;
	case Constants::Left:
		SDL_RenderCopyEx(renderer, texture, NULL, drawRect, 270, NULL, SDL_FLIP_NONE);
		break;
	}
	
}

void Tank::initTank()
{
	drawRect = new SDL_Rect();
	drawRect->h = Constants::TILE_HEIGHT;
	drawRect->w = Constants::TILE_WIDTH;
	drawRect->x = 1;
	drawRect->y =1;

	x_speed = 0;
	y_speed = 0;

	direction = Constants::Down;
}

bool Tank::collides(SDL_Rect* rectangle)
{
	bool collides = true;

	//tank sides
	int tankLeft = drawRect->x;
	int tankRight = drawRect->x + drawRect->w;
	int tankTop = drawRect->y;
	int tankBottom = drawRect->y + drawRect->h;

	//object sides
	int objLeft = rectangle->x;
	int objRight = rectangle->x + rectangle->w;
	int objTop = rectangle->y;
	int objBottom = rectangle->y + rectangle->h;

	if (tankBottom+3 < objTop)
		collides = false;
	else if (tankTop-3 > objBottom)
		collides = false;
	else if (tankLeft-3 > objRight)
		collides = false;
	else if (tankRight+3 < objLeft)
		collides = false;


	return collides;
}

void Tank::setBlocked()
{
	cur_direction_collision = true;
}

