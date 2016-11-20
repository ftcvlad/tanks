#ifndef _GAME_H
#define _GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include "Tile2.h"
#include "Tank.h"
#include "Projectile.h"
#include <vector>
#include "EnemyTank.h"
#include "GUI.h"

class Game
{
private:
	SDL_Window* main_window = NULL;
	SDL_Renderer* main_renderer = NULL;
	SDL_Surface* buffer_surface = NULL;

	SDL_Surface* texture1 = NULL;

	SDL_Texture* highHpTank = NULL;
	SDL_Texture* middleHpTank = NULL;
	SDL_Texture* lowHpTank = NULL;

	SDL_Texture* projectileTexture;

	SDL_Texture* gameOverScreen = NULL;

	//SDL_Surface* bg_texture = NULL;
	SDL_Texture* brickTexture = NULL;
	SDL_Texture* grassTexture = NULL;
	SDL_Texture* wallTexture = NULL;
	SDL_Texture* base_1_Texture = NULL;
	SDL_Texture* base_2_Texture = NULL;
	SDL_Texture* base_3_Texture = NULL;
	SDL_Texture* base_4_Texture = NULL;

	std::vector<Tile2*> allTiles;

	SDL_Texture* bg_texture = NULL;

	SDL_Rect* bg_rect;

	Tank* player;

	
	std::vector<Projectile*>* projectiles;

	GUI* gui;
	vector<EnemyTank*>* enemies;

	bool lost = false;
	bool pause = false;
	bool pausepressed = false;

	int textMap[26][26];

	bool gameOver;
	bool GAME_Init();
	bool GAME_Load();
	void GAME_Update();
	void GAME_Draw();

	bool GAME_initializeMap();
	void GAME_drawLandscape();

	bool initPlayer();
	bool initEnemies();
	void checkCollisions();
	void init();
	void reset();
	void spawnEnemies();
public:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	void run();
	Game();
	~Game();

	void addProjectile(Projectile* new_projectile);
	void removeInactiveObjects();

	void Game::bulletDestroy(Projectile* target);
};
#endif

