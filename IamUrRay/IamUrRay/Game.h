#ifndef _GAME_H
#define _GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include "Tank.h"
#include "Projectile.h"
#include <vector>

class Game
{
private:
	SDL_Window* main_window = NULL;
	SDL_Renderer* main_renderer = NULL;
	SDL_Surface* buffer_surface = NULL;

	SDL_Surface* texture1 = NULL;
	SDL_Texture* bg_texture = NULL;

	SDL_Rect* bg_rect;

	Tank* player;

	SDL_Texture* projectileTexture;
	std::vector<Projectile*>* projectiles;

	bool gameOver;
	bool GAME_Init();
	bool GAME_Load();
	void GAME_Update();
	void GAME_Draw();
	bool initPlayer();
public:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	void run();
	Game();
	~Game();

	void addProjectile(Projectile* new_projectile);
	void removeInactiveObjects();
};
#endif

