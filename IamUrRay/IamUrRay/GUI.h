#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "MAP_CONSTANTS.h"

using namespace std;
class GUI
{
private:
	SDL_Texture* tankIcon;
	SDL_Rect* tankRectangle;

	SDL_Texture* flagIcon;
	SDL_Rect* flagRectangle;

	int livesRemaining;
	int enemiesRemaining;
	string lives_pref;
	string enemies_pref;
	string lives;
	string enemies;
public:
	GUI(SDL_Texture* icon, SDL_Texture* flag);
	~GUI();
	void Update(int livesRemaining, int enemiesRemaining);
	void Draw(SDL_Renderer* renderer);
};

