#include "Tank.h"


using namespace std;

Tank::Tank(SDL_Texture* texture, SDL_Texture* projectile_texture, vector<Projectile*>* projectiles)
{
	this->texture = texture;
	this->projectile_texture = projectile_texture;
	this->projectiles = projectiles;
	collisionDirection = Constants::None;
	initTank();
	lives = Constants::LIFE_COUNT;
}


Tank::~Tank()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
	delete drawRect;
}

void Tank::Update(const Uint8* keyboardState)
{
	if (dead)
		return;

	x_speed = 0;
	y_speed = 0;

	if (keyboardState[SDL_SCANCODE_W])
	{
		adjustXPosition();
		y_speed = -speedMax;
		direction = Constants::Up;

	}
	else if (keyboardState[SDL_SCANCODE_S])
	{
		adjustXPosition();
		y_speed = speedMax;
		direction = Constants::Down;
	}
	else if (keyboardState[SDL_SCANCODE_A])
	{
		adjustYPosition();

		x_speed = -speedMax;
		direction = Constants::Left;

	}
	else if (keyboardState[SDL_SCANCODE_D])
	{
		adjustYPosition();

		x_speed = speedMax;
		direction = Constants::Right;

	}

	if (cur_direction_collision)
	{
		cur_direction_collision = false;
	}
	else
	{
		x += x_speed;
		y += y_speed;
	}

	//shooting
	if (keyboardState[SDL_SCANCODE_SPACE] && !shot)
	{
		shot = true;

		int proj_width;
		int proj_height;
		SDL_QueryTexture(projectile_texture, NULL, NULL, &proj_width, &proj_height);
		projectiles->push_back(new Projectile(projectile_texture, direction, drawRect->x + (drawRect->w / 2) - proj_width/2, drawRect->y + (drawRect->h / 2)-proj_height/2, Constants::Friendly));

	}
	else if (!keyboardState[SDL_SCANCODE_SPACE])
		shot = false;

	//clamp to borders of screent
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
	drawRect->x = Constants::START_X;
	drawRect->y = Constants::START_Y;

	x = Constants::START_X;
	y = Constants::START_Y;
	
	x_speed = 0;
	y_speed = 0;

	direction = Constants::Up;
}


bool Tank::collides(SDL_Rect* rectangle)
{
	SDL_Rect* rect = new SDL_Rect();
	bool collides = SDL_HasIntersection(rectangle, drawRect);
	
	

	return collides;
}


void Tank::setBlocked()
{
	cur_direction_collision = true;
}


SDL_Rect* Tank::getRect(){
	return drawRect;
}

void Tank::respawn()
{
	lives--;
	x = Constants::START_X;
	y = Constants::START_Y;
	direction = Constants::Up;

	dead = false;
}

void Tank::die()
{
	/*drawRect->x = Constants::START_X_1;
	drawRect->y = Constants::START_Y_1;
	x = Constants::START_X_1;
	y = Constants::START_Y_1;*/



	dead = true;
}


void Tank::adjustXPosition(){
	if (direction != Constants::Down && direction != Constants::Up){
		int leftX = ((int)x / 32) * 32;

		int rightX = (((int)x / 32) + 1) * 32;

		if (abs(x - leftX) < abs(x - rightX)){
			x = leftX;
		}
		else{
			x = rightX;
		}
	}
}

void Tank::adjustYPosition(){
	if (direction != Constants::Right && direction != Constants::Left){
		int topY = ((int)y / 32) * 32;
		int bottomY = (((int)y / 32) + 1) * 32;

		if (abs(y - topY) < abs(y - bottomY)){
			y = topY;
		}
		else{
			y = bottomY;
		}

	}
}