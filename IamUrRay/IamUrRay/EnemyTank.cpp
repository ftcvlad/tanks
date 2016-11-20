#include "EnemyTank.h"

using namespace std;
EnemyTank::EnemyTank(SDL_Texture* lowTexture, SDL_Texture* middleTexture, SDL_Texture* highTexture, int x, int y, Constants::Direction direction, SDL_Texture* projectile_texture, vector<Projectile*>* projectiles, int lives)
{
	srand(time(NULL));
	this->lowTexture = lowTexture;
	this->middleTexture = middleTexture;
	this->highTexture = highTexture;
	this->projectile_texture = projectile_texture;
	this->projectiles = projectiles;
	drawRect = new SDL_Rect();
	drawRect->h = Constants::TILE_HEIGHT;
	drawRect->w = Constants::TILE_WIDTH;
	drawRect->x = x;
	drawRect->y = y;
	this->x = x;
	this->y = y;
	this->lives = lives;
	active = true;
	reloading = true;

	this->direction = direction;

	totalReloadTime = rand() % 1000 + 1000;
	elapsedReloadTime = 0;

	if (lives == 1)
		curTexture = lowTexture;
	else if (lives == 2)
		curTexture = middleTexture;
	else
		curTexture = highTexture;
}


EnemyTank::~EnemyTank()
{
	delete drawRect;
}

void EnemyTank::Update()
{
	x_speed = 0;
	y_speed = 0;
	switch (direction)
	{
	case Constants::Up:
		y_speed = -speedLimit;
		break;
	case Constants::Down:
		y_speed = speedLimit;
		break;
	case Constants::Left:
		x_speed = -speedLimit;
		break;
	case Constants::Right:
		x_speed = speedLimit;
		break;
	}
	
	x += x_speed;
	y += y_speed;

	//clamp to borders of screen
	if (x + drawRect->w >= Constants::SCREEN_WIDTH)
	{
		x = Constants::SCREEN_WIDTH - drawRect->w - 1;
		changeDirection();
	}
	else if (x <= 0)
	{
		x = 1;
		changeDirection();
	}

	if (y + drawRect->h >= Constants::SCREEN_HEIGHT)
	{
		y = Constants::SCREEN_HEIGHT - drawRect->h - 1;
		changeDirection();
	}
	else if (y <= 0)
	{
		y = 1;
		changeDirection();
	}

	drawRect->x = x;
	drawRect->y = y;

	elapsedReloadTime++;
	if (elapsedReloadTime == totalReloadTime)
	{
		shoot();
		elapsedReloadTime = 0;
	}
}

void EnemyTank::Draw(SDL_Renderer* renderer)
{
	switch (direction)
	{
	case Constants::Up:
		SDL_RenderCopyEx(renderer, curTexture, NULL, drawRect, 0, NULL, SDL_FLIP_NONE);
		break;
	case Constants::Down:
		SDL_RenderCopyEx(renderer, curTexture, NULL, drawRect, 180, NULL, SDL_FLIP_NONE);
		break;
	case Constants::Right:
		SDL_RenderCopyEx(renderer, curTexture, NULL, drawRect, 90, NULL, SDL_FLIP_NONE);
		break;
	case Constants::Left:
		SDL_RenderCopyEx(renderer, curTexture, NULL, drawRect, 270, NULL, SDL_FLIP_NONE);
		break;
	}
}

void EnemyTank::changeDirection()
{
	int dir = rand() % 4 + 1;

	while (true)
	{
		dir = rand() % 4 + 1;
		if (dir != direction)
			break;
	}
	switch (dir)
	{
	case 1:
		direction = Constants::Up;
		break;
	case 2:
		direction = Constants::Right;
		break;
	case 3:
		direction = Constants::Down;
		break;
	case 4:
		direction = Constants::Left;
		break;
	}
}

void EnemyTank::shoot()
{
	int proj_width;
	int proj_height;
	SDL_QueryTexture(projectile_texture, NULL, NULL, &proj_width, &proj_height);
	projectiles->push_back(new Projectile(projectile_texture, direction, drawRect->x + drawRect->w / 2 - proj_width/2, drawRect->y + drawRect->h / 2 - proj_height/2, Constants::Enemy));
	totalReloadTime = rand() % 1000 + 1000;
}

void EnemyTank::die()
{
	lives--;
	if (lives == 2)
		curTexture = middleTexture;
	else if (lives == 1)
		curTexture = lowTexture;
	if (lives <= 0)
		active = false;
}

