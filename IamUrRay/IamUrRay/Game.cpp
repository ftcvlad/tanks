#include "Game.h"
#include "MAP_CONSTANTS.h"
#include <iostream>

#include <fstream>
#include <string>



using namespace std;

Game::Game()
{
	init();
}


Game::~Game()
{
	reset();
	SDL_Quit();
}

void Game::init()
{

	SCREEN_WIDTH = Constants::SCREEN_WIDTH;
	SCREEN_HEIGHT = Constants::SCREEN_HEIGHT;

	bg_rect = new SDL_Rect();
	bg_rect->w = SCREEN_WIDTH;
	bg_rect->h = SCREEN_HEIGHT;
	bg_rect->x = 0;
	bg_rect->y = 0;
	projectiles = new vector<Projectile*>();
	gameOver = false;
	lost = false;
	won = false;
	if (!GAME_Init())
	{
		cout << "Game could not initialise properly!" << endl;
		exit(0);
	}
	if (!GAME_Load())
	{
		cout << "Game could not load content!" << endl;
	}

	initEnemies();
	initPlayer();

}

void Game::reset()
{
	SDL_FreeSurface(texture1);
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(highHpTank);
	SDL_DestroyTexture(middleHpTank);
	SDL_DestroyTexture(lowHpTank);
	SDL_DestroyTexture(projectileTexture);
	SDL_DestroyTexture(gameOverScreen);
	SDL_DestroyTexture(brickTexture);
	SDL_DestroyTexture(grassTexture);
	SDL_DestroyTexture(wallTexture);
	SDL_DestroyTexture(base_1_Texture);
	SDL_DestroyTexture(base_2_Texture);
	SDL_DestroyTexture(base_3_Texture);
	SDL_DestroyTexture(base_4_Texture);
	SDL_DestroyTexture(pauseText);
	SDL_DestroyTexture(realBGTexture);
	SDL_DestroyTexture(tank_icon);
	SDL_DestroyTexture(flag_icon);

	texture1 = NULL;
	bg_texture = NULL;
	highHpTank = NULL;
	middleHpTank = NULL;
	lowHpTank = NULL;
	projectileTexture = NULL;
	gameOverScreen = NULL;
	brickTexture = NULL;
	grassTexture = NULL;
	wallTexture = NULL;
	base_1_Texture = NULL;
	base_2_Texture = NULL;
	base_3_Texture = NULL;
	base_4_Texture = NULL;
	pauseText = NULL;
	realBGTexture = NULL;
	tank_icon = NULL;
	flag_icon = NULL;


	SDL_FreeSurface(buffer_surface);
	buffer_surface = NULL;
	SDL_DestroyWindow(main_window);
	main_window = NULL;

	delete bg_rect;
	delete player;
	delete realBGRect;

	for (int i = 0; i < projectiles->size(); i++)
	{
		delete projectiles->at(i);
	}
	delete projectiles;

	for (int i = 0; i < enemies->size(); i++)
	{
		delete enemies->at(i);
	}
	delete enemies;

	for (int i = 0; i < allTiles.size(); i++)
	{
		Tile2* temp = allTiles.at(i);
		allTiles.erase(allTiles.begin() + i);
		delete temp;
	}
	delete gui;
}

bool Game::initPlayer()
{
	SDL_Surface* temp_surface = IMG_Load("graphics/playerTank.png");
	if (temp_surface == NULL)
	{
		cout << "Failed to load player texture! Error: " << IMG_GetError() << endl;
		return false;
	}
	SDL_Texture* player_texture = SDL_CreateTextureFromSurface(main_renderer, temp_surface);
	if (player_texture == NULL)
	{
		cout << "Failed to convert player surface into texture! Error: " << IMG_GetError() << endl;
		return false;
	}

	SDL_Surface* projectileSurf = IMG_Load("graphics/projectile.png");
	if (temp_surface == NULL)
	{
		cout << "Failed to load projectile surface! Error: " << IMG_GetError() << endl;
		return false;
	}
	SDL_Texture* projectileTexture = SDL_CreateTextureFromSurface(main_renderer, projectileSurf);
	if (projectileTexture == NULL)
	{
		cout << "Failed to convert projectile surface into texture! Error: " << IMG_GetError() << endl;
		return false;
	}

	player = new Tank(player_texture, projectileTexture, projectiles);

	SDL_FreeSurface(temp_surface);
	return true;
}

bool Game::initEnemies()
{
	enemies = new vector<EnemyTank*>();

	SDL_Surface* temp_surface = IMG_Load("graphics/enemyTank1.png");
	if (temp_surface == NULL)
	{
		cout << "Couldn't load enemy texture! Error: " << SDL_GetError() << endl;
		return false;
	}
	highHpTank = SDL_CreateTextureFromSurface(main_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	if (highHpTank == NULL)
	{
		cout << "Couldn't parse enemy texture! Error: " << SDL_GetError() << endl;
	}

	SDL_Surface* temp_surface1 = IMG_Load("graphics/enemyTank3.png");
	if (temp_surface1 == NULL)
	{
		cout << "Couldn't load enemy texture! Error: " << SDL_GetError() << endl;
		return false;
	}
	middleHpTank = SDL_CreateTextureFromSurface(main_renderer, temp_surface1);
	SDL_FreeSurface(temp_surface1);
	if (middleHpTank == NULL)
	{
		cout << "Couldn't parse enemy texture! Error: " << SDL_GetError() << endl;
	}

	SDL_Surface* temp_surface2 = IMG_Load("graphics/enemyTank2.png");
	if (temp_surface2 == NULL)
	{
		cout << "Couldn't load enemy texture! Error: " << SDL_GetError() << endl;
		return false;
	}
	lowHpTank = SDL_CreateTextureFromSurface(main_renderer, temp_surface2);
	SDL_FreeSurface(temp_surface2);
	if (lowHpTank == NULL)
	{
		cout << "Couldn't parse enemy texture! Error: " << SDL_GetError() << endl;
	}

	SDL_Surface* projectileSurf = IMG_Load("graphics/projectile.png");
	if (temp_surface == NULL)
	{
		cout << "Failed to load projectile surface! Error: " << IMG_GetError() << endl;
		return false;
	}
	projectileTexture = SDL_CreateTextureFromSurface(main_renderer, projectileSurf);
	SDL_FreeSurface(projectileSurf);
	if (projectileTexture == NULL)
	{
		cout << "Failed to convert projectile surface into texture! Error: " << IMG_GetError() << endl;
		return false;
	}


	enemies->push_back(new EnemyTank(lowHpTank, middleHpTank, highHpTank, Constants::START_X_1, Constants::START_Y_1, Constants::Down, projectileTexture, projectiles, 2));
	enemies->push_back(new EnemyTank(lowHpTank, middleHpTank, highHpTank, Constants::START_X_2, Constants::START_Y_2, Constants::Down, projectileTexture, projectiles, 3));
	enemies->push_back(new EnemyTank(lowHpTank, middleHpTank, highHpTank, Constants::START_X_3, Constants::START_Y_3, Constants::Down, projectileTexture, projectiles, 1));



	return true;
}

bool Game::GAME_Init()
{
	bool success = true;
	//initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO)!=0)
	{
		cout << "Couldn't initialise SDL! Error: \n" << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//create window
		main_window = SDL_CreateWindow("IamUrRay - maingame!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (main_window == NULL)
		{
			cout << "Couldn't initialise window! Error: \n" << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			buffer_surface = SDL_GetWindowSurface(main_window);
			main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
			if (main_renderer == NULL)
			{
				SDL_SetRenderDrawColor(main_renderer, 0xFA, 0xFF, 0xFF, 0xFF);
				cout << "Couldn't initialise renderer! Error: \n" << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				int img_flags = IMG_INIT_PNG;
				if (!IMG_Init(img_flags) && img_flags)
				{
					cout << "Couldn't initialise image flags! Error: \n" << SDL_GetError() << endl;
					success = false;
				}
			}
		}
	}

	SDL_Surface* temp = IMG_Load("graphics/gameOverScreen.png");
	if (temp == NULL)
	{
		cout << "Couldn't load gameOverScreen! Error: " << SDL_GetError() << endl;

		success = false;
	}

	gameOverScreen = SDL_CreateTextureFromSurface(main_renderer, temp);
	SDL_FreeSurface(temp);

	SDL_Surface* temp1 = IMG_Load("graphics/pause.png");
	if (temp1 == NULL)
	{
		cout << "Couldn't load pause text! Error: " << SDL_GetError() << endl;
		success = false;
	}
	pauseText = SDL_CreateTextureFromSurface(main_renderer, temp1);
	if (pauseText == NULL)
	{
		cout << "Couldn't convert pause text! Error: " << SDL_GetError() << endl;
		success = false;
	}
	SDL_FreeSurface(temp1 );

	SDL_Surface* tank_ico = IMG_Load("graphics/tank_icon.png");
	if (tank_ico == NULL)
	{
		cout << "Couldn't load tank icon! Error: " << SDL_GetError() << endl;
		success = false;
	}
	tank_icon = SDL_CreateTextureFromSurface(main_renderer, tank_ico);
	if (tank_icon == NULL)
	{
		cout << "Failed to parse tank icon! Error: " << SDL_GetError() << endl;
		success = false;
	}


	SDL_Surface* flag_ico = IMG_Load("graphics/life.png");
	if (flag_ico == NULL)
	{
		cout << "Couldn't load flag icon! Error: " << SDL_GetError() << endl;
		success = false;
	}
	flag_icon = SDL_CreateTextureFromSurface(main_renderer, flag_ico);
	if (flag_icon == NULL)
	{
		cout << "Failed to parse flag icon! Error: " << SDL_GetError() << endl;
		success = false;
	}
	SDL_FreeSurface(flag_ico);


	SDL_Surface*  temp5 = IMG_Load("graphics/victory.png");
	if (temp5 == NULL)
	{
		cout << "Couldn't load victory text! Error: " << SDL_GetError() << endl;
		success = false;
	}
	winScreen = SDL_CreateTextureFromSurface(main_renderer, temp5);
	if (winScreen == NULL)
	{
		cout << "Couldn't convert winScreen text! Error: " << SDL_GetError() << endl;
		success = false;
	}
	SDL_FreeSurface(temp5);



	GAME_initializeMap();
	gui = new GUI(tank_icon, flag_icon);
	//SDL_Delay(5000);
	return success;
}

bool Game::GAME_Load()
{
	bool success = true;
	SDL_Surface* realBG = SDL_LoadBMP("graphics/realBG.bmp");
	SDL_Surface* realBGStretched = SDL_ConvertSurface(realBG, buffer_surface->format, NULL);
	realBGTexture = SDL_CreateTextureFromSurface(main_renderer, realBGStretched);
	SDL_FreeSurface(realBG);
	if (realBGTexture == NULL)
	{
		cout << "Couldn't load realBG texture! Error: " << SDL_GetError() << endl;
		success = false;
	}
	realBGRect = new SDL_Rect();
	realBGRect->w = Constants::WINDOW_WIDTH;
	realBGRect->h = Constants::WINDOW_HEIGHT;
	realBGRect->x = 0;
	realBGRect->y = 0;

	SDL_Surface* temp = SDL_LoadBMP("graphics/splashBG.bmp");
	SDL_Surface* temp1 = SDL_ConvertSurface(temp, buffer_surface->format, NULL);
	bg_texture = SDL_CreateTextureFromSurface(main_renderer, temp1);
	SDL_FreeSurface(temp);
	if (bg_texture == NULL)
	{
		cout << "Couldn't load background! Error: \n" << SDL_GetError() << endl;
		success = false;
	}

	return success;
}

void Game::run()
{
	while (!gameOver)
	{
		GAME_Update();
		GAME_Draw();
	}

}

void Game::GAME_Update()
{

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			gameOver = true;

	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_F]){
		SDL_SetWindowFullscreen(main_window,SDL_WINDOW_FULLSCREEN);
	}
	else if (state[SDL_SCANCODE_P]){
		SDL_SetWindowFullscreen(main_window, 0);
	}


	if (!lost && !won)
	{
		if (!pause)
		{
			for (int i = 0; i < projectiles->size(); i++)
			{
				projectiles->at(i)->Update();
				bulletDestroy(projectiles->at(i));
			}


			checkCollisions();
			player->Update(SDL_GetKeyboardState(NULL));
			for (int i = 0; i < enemies->size(); i++)
			{
				enemies->at(i)->Update();
			}
			removeInactiveObjects();

			if (player->isDead())
			{
				//respawn player if dead and spawn unoccupied
				SDL_Rect* r = new SDL_Rect();
				r->x = 0;
				r->y = 0;
				r->w = Constants::TILE_WIDTH;
				r->h = Constants::TILE_HEIGHT;
				bool intersects = false;
				for (int i = 0; i < enemies->size(); i++)
				{
					if (SDL_HasIntersection(enemies->at(i)->getRect(), r))
						intersects = true;
				}
				if (!intersects)
					player->respawn();
			}
			//spawnEnemies();


			if (player->getLives() <= 0)
				lost = true;
			gui->Update(player->getLives(), Constants::TARGET_KILLS-player->getKills());
		}


		//pause the game (toggles by pressing escape)
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE])
		{
			if (pause && !pausepressed)
			{
				pause = false;
				pausepressed = true;
			}
			else if (!pause && !pausepressed)
			{
				pause = true;
				pausepressed = true;
			}
			
		}
		else if (!state[SDL_SCANCODE_ESCAPE])
		{
			pausepressed = false;
		}

		//WIN
		if (player->getKills() == Constants::TARGET_KILLS){///targetKills

			won = true;

		
		}
		//ADD NEW ENEMY
		else if (enemies->size() < 4 && player->getKills()<= Constants::TARGET_KILLS-4){//targetKills-3
			int randInd = rand() % (3);

			SDL_Rect r;
			r.w = Constants::TILE_WIDTH;
			r.h = Constants::TILE_HEIGHT;
			if (randInd == 0){
				r.x = Constants::START_X_1;
				r.y = Constants::START_Y_1;
			}
			else if (randInd == 1){
				r.x = Constants::START_X_2;
				r.y = Constants::START_Y_2;
			}
			else if (randInd == 2){
				r.x = Constants::START_X_3;
				r.y = Constants::START_Y_3;
			}

			bool intersects = false;
			if (SDL_HasIntersection(player->getRect(), &r)){
				intersects = true;
			}
			else{
				for (unsigned int k = 0; k < (*enemies).size(); k++){

					if (SDL_HasIntersection(enemies->at(k)->getRect(), &r)){
						intersects = true;
						break;
					}
				}
			}

			if (!intersects){
				enemies->push_back(new EnemyTank(lowHpTank, middleHpTank, highHpTank, r.x, r.y, Constants::Down, projectileTexture, projectiles, rand() % (3) + 1));
			}

		}



	}
	else if (won){
		//game over window - restart/quit
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_R])

		{
			reset();
			init();
		}
		else if (state[SDL_SCANCODE_Q])
		{
			gameOver = true;
		}
	}
	else{

		//game over window - restart/quit
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_R])

		{
			reset();
			init();
		}
		else if (state[SDL_SCANCODE_Q])
		{
			gameOver = true;
		}
		
	}

	//cout << "enemies alive: " << enemies->size() << endl;


}

void Game::GAME_Draw()
{
	SDL_RenderClear(main_renderer);

	SDL_RenderCopy(main_renderer, realBGTexture, NULL, realBGRect);//!!!
	if (!lost && !won)

	{
		
		SDL_RenderCopy(main_renderer, bg_texture, NULL, bg_rect);
		for (int i = 0; i < projectiles->size(); i++)
		{
			if (projectiles->at(i)->getActive())
				projectiles->at(i)->Draw(main_renderer);
		}

		for (int i = 0; i < enemies->size(); i++)
		{
			enemies->at(i)->Draw(main_renderer);
		}

		player->Draw(main_renderer);
		GAME_drawLandscape();

		
		

		gui->Draw(main_renderer);
		
		if (pause)
			SDL_RenderCopy(main_renderer, pauseText, NULL, bg_rect);

		SDL_RenderPresent(main_renderer);
	}
	else if (won){
		
		SDL_RenderCopy(main_renderer, winScreen, NULL, realBGRect);
		SDL_RenderPresent(main_renderer);
	}
	else
	{
		SDL_RenderCopy(main_renderer, gameOverScreen, NULL, realBGRect);
		SDL_RenderPresent(main_renderer);
	}
	
}


bool Game::GAME_initializeMap(){


	//load textures
	bool success = true;
	//load brick
	SDL_Surface* temp = SDL_LoadBMP("graphics/brickWall2.bmp");
	if (temp == NULL)
	{
		cout << "Couldn't load brick texture! Error: \n" << SDL_GetError() << endl;
		return false;
	}
	brickTexture = SDL_CreateTextureFromSurface(main_renderer, temp);
	SDL_FreeSurface(temp);
	if (brickTexture == NULL)
	{
		cout << "Couldn't parse brick texture from surface! Error: \n" << SDL_GetError() << endl;
		return false;
	}

	//load bush
	temp = SDL_LoadBMP("graphics/bush2.bmp");
	if (temp == NULL)
	{
		cout << "Couldn't load bush texture! Error: \n" << SDL_GetError() << endl;
		return false;
	}
	grassTexture = SDL_CreateTextureFromSurface(main_renderer, temp);
	SDL_FreeSurface(temp);
	if (grassTexture == NULL)
	{
		cout << "Couldn't parse bush texture from surface! Error: \n" << SDL_GetError() << endl;
		return false;
	}

	//load halfSteelWall
	temp = SDL_LoadBMP("graphics/halfSteelWall2.bmp");
	if (temp == NULL)
	{
		cout << "Couldn't load steel wall texture! Error: \n" << SDL_GetError() << endl;
		return false;
	}
	wallTexture = SDL_CreateTextureFromSurface(main_renderer, temp);
	SDL_FreeSurface(temp);
	if (wallTexture == NULL)
	{
		cout << "Couldn't parse wall texture from file! Error: \n" << SDL_GetError() << endl;

	}


	//load base 1 texture
	temp = SDL_LoadBMP("graphics/base_1.bmp");
	if (temp == NULL)
	{
		cout << "Couldn't load base 1 texture! Error: \n" << SDL_GetError() << endl;
		return false;
	}
	base_1_Texture = SDL_CreateTextureFromSurface(main_renderer, temp);
	SDL_FreeSurface(temp);
	if (base_1_Texture == NULL)
	{
		cout << "Couldn't parse base 1 texture! Error: \n" << SDL_GetError() << endl;

	}

	//load base 2 texture
	temp = SDL_LoadBMP("graphics/base_2.bmp");
	if (temp == NULL)
	{
		cout << "Couldn't load base 2 texture! Error: \n" << SDL_GetError() << endl;
		return false;
	}
	base_2_Texture = SDL_CreateTextureFromSurface(main_renderer, temp);
	SDL_FreeSurface(temp);
	if (base_2_Texture == NULL)
	{
		cout << "Couldn't parse background4! Error: \n" << SDL_GetError() << endl;

	}

	//load base 3 texture
	temp = SDL_LoadBMP("graphics/base_3.bmp");
	if (temp == NULL)
	{
		cout << "Couldn't load base 3 texture! Error: \n" << SDL_GetError() << endl;
		return false;
	}
	base_3_Texture = SDL_CreateTextureFromSurface(main_renderer, temp);
	SDL_FreeSurface(temp);
	if (base_3_Texture == NULL)
	{
		cout << "Couldn't parse background4 texture! Error: \n" << SDL_GetError() << endl;

	}

	//load base 4 texture
	temp = SDL_LoadBMP("graphics/base_4.bmp");
	if (temp == NULL)
	{
		cout << "Couldn't load base 4 texture! Error: \n" << SDL_GetError() << endl;
		return false;
	}
	base_4_Texture = SDL_CreateTextureFromSurface(main_renderer, temp);
	SDL_FreeSurface(temp);
	if (base_4_Texture == NULL)
	{
		cout << "Couldn't parse background4 texture! Error: \n" << SDL_GetError() << endl;

	}

	
	ifstream file("map2.txt");
	std::string str;
	int row = 0;
	while (std::getline(file, str))
	{

		for (unsigned int c = 0; c < str.length(); c++){
			textMap[row][c] = (str[c] - '0');

			SDL_Rect* nextRect = new SDL_Rect();
			nextRect->x = c * 32;
			nextRect->y = row * 32;
			nextRect->w = 32;
			nextRect->h = 32;

			if (textMap[row][c] == 0){//empty

			}
			else if (textMap[row][c] == 2){//grass
				allTiles.push_back(new Tile2(nextRect, true, false, row * 26 + c, textMap[row][c]));
			}
			else {//other

				if (textMap[row][c] == 1){//brick
					allTiles.push_back(new Tile2(nextRect, false, true, row * 26 + c, textMap[row][c]));
				}
				else if (textMap[row][c] == 3){//wall

					allTiles.push_back(new Tile2(nextRect, false, false, row * 26 + c, textMap[row][c]));
				}
				else{// other


					allTiles.push_back(new Tile2(nextRect, false, false, row * 26 + c, textMap[row][c]));
				}


			}

		}
		row++;

	}

	return true;


}


void Game::GAME_drawLandscape(){

	int arrSize = 26;
	int nextType;

	for (unsigned int i = 0; i < allTiles.size(); i++){

		nextType = allTiles.at(i)->type;

		if (nextType == 1){//brick
			SDL_RenderCopy(main_renderer, brickTexture, NULL, allTiles.at(i)->rect);
		}
		else if (nextType == 2){//grass
			SDL_RenderCopy(main_renderer, grassTexture, NULL, allTiles.at(i)->rect);
		}
		else if (nextType == 3){//wall
			SDL_RenderCopy(main_renderer, wallTexture, NULL, allTiles.at(i)->rect);
		}
		else if (nextType == 6){//top left
			SDL_RenderCopy(main_renderer, base_1_Texture, NULL, allTiles.at(i)->rect);
		}
		else if (nextType == 7){//top right
			SDL_RenderCopy(main_renderer, base_2_Texture, NULL, allTiles.at(i)->rect);
		}
		else if (nextType == 8){//bottom left
			SDL_RenderCopy(main_renderer, base_3_Texture, NULL, allTiles.at(i)->rect);
		}
		else if (nextType == 9){//skip
			SDL_RenderCopy(main_renderer, base_4_Texture, NULL, allTiles.at(i)->rect);
		}

	}
}

void Game::checkCollisions()
{
	SDL_Rect* r1 = new SDL_Rect();
	SDL_Rect* r2 = new SDL_Rect();
	//check player and tile collisions
	for (int i = 0; i < allTiles.size(); i++)
	{
		if (!allTiles.at(i)->canIntersect)
		{
			r1->x = player->getRect()->x + (player->x_speed)*10;
			r1->y = player->getRect()->y + (player->y_speed)*10;
			r1->w = Constants::TILE_WIDTH;
			r1->h = Constants::TILE_HEIGHT;

			if (SDL_HasIntersection(allTiles.at(i)->rect, r1)){
				player->setBlocked();
			}
		}
	}

	//check for player and projectile collisions
	for (int i = 0; i < projectiles->size(); i++)
	{
		if (projectiles->at(i)->getOwner() != Constants::Friendly)
			if (SDL_HasIntersection(projectiles->at(i)->getRect(), player->getRect()))
			{
				player->die();
				projectiles->at(i)->setActive(false);
			}
	}

	if (enemies->size() > 0)
	{
		//check enemy collision with tiles
		for (int i = 0; i < enemies->size(); i++)
		{
			for (int j = 0; j < allTiles.size(); j++)
			{
				if (!allTiles.at(j)->canIntersect)
				{
					r1->x = enemies->at(i)->getRect()->x + (enemies->at(i)->x_speed) * 10;
					r1->y = enemies->at(i)->getRect()->y + (enemies->at(i)->y_speed) * 10;
					r1->w = Constants::TILE_WIDTH;
					r1->h = Constants::TILE_HEIGHT;
					if (SDL_HasIntersection(r1, allTiles.at(j)->rect))
						enemies->at(i)->changeDirection();

				}

			}
		}

		//check enemy and player collision
		for (int i = 0; i < enemies->size(); i++)
		{
			r1->x = enemies->at(i)->getRect()->x + (enemies->at(i)->x_speed) * 10;
			r1->y = enemies->at(i)->getRect()->y + (enemies->at(i)->y_speed) * 10;
			r1->w = 64;
			r1->h = 64;
			if (SDL_HasIntersection(r1, player->getRect()))
				enemies->at(i)->changeDirection();
		}

		//check player and enemy collision
		for (int i = 0; i < enemies->size(); i++)
		{
			r1->x = player->getRect()->x + (player->x_speed) * 10;
			r1->y = player->getRect()->y + (player->y_speed) * 10;
			r1->w = Constants::TILE_WIDTH;
			r1->h = Constants::TILE_HEIGHT;
			if (SDL_HasIntersection(enemies->at(i)->getRect(), r1))
				player->setBlocked();
		}

		//check for enemy and projectile collisions
		for (int i = 0; i < enemies->size(); i++)
		{
			for (int j = 0; j < projectiles->size(); j++)
			{
				if (projectiles->at(j)->getOwner() != Constants::Enemy)
				{
					if (SDL_HasIntersection(projectiles->at(j)->getRect(), enemies->at(i)->getRect()))
					{
						enemies->at(i)->die();
						if (!enemies->at(i)->isActive()){
							player->setKills(player->getKills() + 1);
						}

						
						projectiles->at(j)->setActive(false);
					}
				}
			}
		}

		//check for collision between enemies
		for (int i = 0; i < enemies->size() - 1; i++)
		{
			for (int j = 0; j < enemies->size(); j++)
			{
				if (i == j)
					j++;
				r1->x = enemies->at(i)->getRect()->x + (enemies->at(i)->x_speed) * 10;
				r1->y = enemies->at(i)->getRect()->y + (enemies->at(i)->y_speed) * 10;
				r1->w = Constants::TILE_WIDTH;
				r1->h = Constants::TILE_HEIGHT;

				r2->x = enemies->at(j)->getRect()->x + (enemies->at(j)->x_speed) * 10;
				r2->y = enemies->at(j)->getRect()->y + (enemies->at(j)->y_speed) * 10;
				r2->w = Constants::TILE_WIDTH;
				r2->h = Constants::TILE_HEIGHT;

				if (SDL_HasIntersection(r1, r2))
				{
					enemies->at(i)->changeDirection();
					enemies->at(j)->changeDirection();
				}
			}
		}


		//check projectile and projectile collisions
		for (int i = 0; i < projectiles->size(); i++){

			for (int k = i + 1; k < projectiles->size(); k++){

				if (SDL_HasIntersection(projectiles->at(i)->getRect(), projectiles->at(k)->getRect())){
					projectiles->at(i)->setActive(false);
					projectiles->at(k)->setActive(false);
				}


			}
		}
		
			
		


	}
	delete r1;
	delete r2;
}


void Game::removeInactiveObjects()
{
	//remove inactive projectiles
	int counter = 0;
	for (int i = 0; i < projectiles->size(); i++)
	{
		if (!projectiles->at(i)->getActive())
		{
			Projectile* temp = projectiles->at(counter);
			projectiles->erase(projectiles->begin() + counter);
			delete temp;
		}
		counter++;
	}
	
	//remove inactive enemies
	counter = 0;
	for (int i = 0; i < enemies->size(); i++)
	{
		if (!enemies->at(counter)->isActive())
		{
			EnemyTank* temp = enemies->at(counter);
			enemies->erase(enemies->begin() + counter);
			delete temp;
		}
		counter++;
	}

}

void Game::bulletDestroy(Projectile* target){
	for (int k = 0; k < allTiles.size(); k++){


		if (SDL_HasIntersection(allTiles.at(k)->rect, target->getRect())){

			if (allTiles.at(k)->type == 1){//brick

				allTiles.erase(allTiles.begin() + k);
				k--;

				target->setActive(false);
			}
			else if (allTiles.at(k)->type == 3){//brick
				target->setActive(false);
			}
			else if (allTiles.at(k)->type == 2){//grass

			}
			else if (allTiles.at(k)->type == 7 || allTiles.at(k)->type == 8 || allTiles.at(k)->type == 9 || allTiles.at(k)->type == 6)//bird
			{
				lost = true;
			}
		}


	}
}

void Game::spawnEnemies()
{


}
