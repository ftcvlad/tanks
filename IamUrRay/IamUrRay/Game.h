#ifndef _GAME_H
#define _GAME_H

#include <SDL.h>
#include <SDL_image.h>
<<<<<<< HEAD
#include "Player.h"
#include "Tile2.h"
=======
#include "Tank.h"
#include "Projectile.h"
>>>>>>> aae48b5162fd4d5a7aba93ae10a25dd9f9fda30d
#include <vector>

class Game
{
private:
	SDL_Window* main_window = NULL;
	SDL_Renderer* main_renderer = NULL;
	SDL_Surface* buffer_surface = NULL;

	SDL_Surface* texture1 = NULL;
<<<<<<< HEAD
	SDL_Surface* bg_texture = NULL;
	SDL_Surface* brickTexture = NULL;
	SDL_Surface* grassTexture = NULL;
	SDL_Surface* wallTexture = NULL;
	SDL_Surface* emptyTexture = NULL;
	SDL_Surface* base_1_Texture = NULL;
	SDL_Surface* base_2_Texture = NULL;
	SDL_Surface* base_3_Texture = NULL;
	SDL_Surface* base_4_Texture = NULL;

	std::vector<Tile2*> allTiles;
	

	
=======
	SDL_Texture* bg_texture = NULL;

>>>>>>> aae48b5162fd4d5a7aba93ae10a25dd9f9fda30d
	SDL_Rect* bg_rect;

	Tank* player;

	SDL_Texture* projectileTexture;
	std::vector<Projectile*>* projectiles;

	int textMap[26][26];


	bool gameOver;
	bool GAME_Init();
	bool GAME_Load();
	void GAME_Update();
	void GAME_Draw();
<<<<<<< HEAD
	void GAME_initializeMap();
	void GAME_drawLandscape();
=======
	bool initPlayer();
>>>>>>> aae48b5162fd4d5a7aba93ae10a25dd9f9fda30d
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

