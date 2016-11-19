#include "Game.h"
#include "MAP_CONSTANTS.h"
#include <iostream>

#include <fstream>
#include <string>


using namespace std;

Game::Game()
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
	if (!GAME_Init())
	{
		cout << "Game could not initialise properly!" << endl;
		exit(0);
	}
	if (!GAME_Load())
	{
		cout << "Game could not load content!" << endl;
	}



	initPlayer();


}

Game::~Game()
{
	SDL_FreeSurface(texture1);
	texture1 = NULL;
	SDL_DestroyTexture(bg_texture);
	texture1 = NULL;
	SDL_FreeSurface(buffer_surface);
	buffer_surface = NULL;
	SDL_DestroyWindow(main_window);
	main_window = NULL;

	delete bg_rect;
	SDL_Quit();

	for (int i = 0; i < projectiles->size(); i++)
	{
		delete projectiles->at(i);
	}
	delete projectiles;
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
	SDL_Texture* projectile_texture = SDL_CreateTextureFromSurface(main_renderer, projectileSurf);
	if (player_texture == NULL)
	{
		cout << "Failed to convert projectile surface into texture! Error: " << IMG_GetError() << endl;
		return false;
	}

	player = new Tank(player_texture, projectile_texture, projectiles);

	SDL_FreeSurface(temp_surface);
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
		main_window = SDL_CreateWindow("IamUrRay - maingame!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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


	GAME_initializeMap();

	return success;
}

bool Game::GAME_Load()
{
	bool success = true;

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



	for (int i = 0; i < projectiles->size();i++)
	{
		projectiles->at(i)->Update();
	}

	player->Update(SDL_GetKeyboardState(NULL));


	removeInactiveObjects();
	cout << "Projectiles: " << projectiles->size() << endl;
}

void Game::GAME_Draw()
{
	SDL_RenderClear(main_renderer);
	SDL_RenderCopy(main_renderer, bg_texture, NULL, bg_rect);

	GAME_drawLandscape();

	player->Draw(main_renderer);

	for (int i = 0; i < projectiles->size(); i++)
	{

		if (projectiles->at(i)->getActive())
			projectiles->at(i)->Draw(main_renderer);
		else
			cout << "Not active!" << endl;

	}
	SDL_RenderPresent(main_renderer);
	
	
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


	
	ifstream file("map1.txt");
	std::string str;
	int row = 0;
	while (std::getline(file, str))
	{

		for (unsigned int c = 0; c < str.length(); c++){
			textMap[row][c] = (str[c] - '0');

			SDL_Rect* nextRect = new SDL_Rect();
			nextRect -> x = c * 32;
			nextRect ->y = row * 32;
			nextRect->w =  32;
			nextRect->h = 32;

			if (textMap[row][c]==2){//grass
				allTiles.push_back(new Tile2(nextRect, true));
			}
			else {//other
				allTiles.push_back(new Tile2(nextRect, false));
			}
			
		}
		row++;
		
	}



}


void Game::GAME_drawLandscape(){

	int arrSize = 26;
	int nextType;

	for (int i = 0; i < arrSize; i++){
		for (int j = 0; j < arrSize; j++){
			nextType = textMap[i][j];
			if (nextType==0){//empty tile
				

			}
			else if (nextType == 1){//brick
				SDL_RenderCopy(main_renderer, brickTexture, NULL,  allTiles[i * 26 + j]->rect);
			}
			else if (nextType == 2){//grass
				SDL_RenderCopy(main_renderer, brickTexture, NULL, allTiles[i * 26 + j]->rect);
			}
			else if (nextType == 3){//wall
				SDL_RenderCopy(main_renderer, wallTexture, NULL, allTiles[i * 26 + j]->rect);
			}
			else if (nextType == 6){//top left
				SDL_RenderCopy(main_renderer, base_1_Texture, NULL, allTiles[i * 26 + j]->rect);
			}
			else if (nextType == 7){//top right
				SDL_RenderCopy(main_renderer, base_2_Texture, NULL, allTiles[i * 26 + j]->rect);
			}
			else if (nextType == 8){//bottom left
				SDL_RenderCopy(main_renderer, base_3_Texture, NULL, allTiles[i * 26 + j]->rect);
			}
			else if (nextType == 9){//skip
				SDL_RenderCopy(main_renderer, base_4_Texture, NULL, allTiles[i * 26 + j]->rect);
			}


		}


	}




}


void Game::removeInactiveObjects()
{
	int counter = 0;
	for (int i = 0; i < projectiles->size(); i++)
	{
		if (!projectiles->at(i)->getActive())
		{
			Projectile* temp = projectiles->at(counter);
			projectiles->erase(projectiles->begin() + counter);
			delete temp;
			counter++;
		}
	}
	

}