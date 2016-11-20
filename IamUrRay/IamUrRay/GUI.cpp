#include "GUI.h"


GUI::GUI(SDL_Texture* icon, SDL_Texture* flag)
{
	tankIcon = icon;
	livesRemaining = 0;
	enemiesRemaining = 0;
	tankRectangle = new SDL_Rect();
	tankRectangle->h = Constants::TANK_ICON_HEIGHT;
	tankRectangle->w = Constants::TANK_ICON_WIDTH;

	flagIcon = flag;
	flagRectangle = new SDL_Rect();
	flagRectangle->h = Constants::FLAG_ICON_HEIGHT;
	flagRectangle->w = Constants::FLAG_ICON_WIDTH;
}


GUI::~GUI()
{
	SDL_DestroyTexture(tankIcon);
	delete tankRectangle;
}

void GUI::Update(int livesRemaining, int enemiesRemaining)
{
	this->enemiesRemaining = enemiesRemaining;
	this->livesRemaining = livesRemaining;
}

void GUI::Draw(SDL_Renderer* renderer)
{

	int counter = 0;
	int column = 0;
	int row = 0;
	
	
	while (counter < enemiesRemaining)
	{
		if (column == 3)
		{
			column = 0;
			row++;
		}

		
		tankRectangle->y = (row * Constants::TANK_ICON_HEIGHT) + Constants::TANK_ICON_FIRSTY;
		tankRectangle->x = (column * Constants::TANK_ICON_WIDTH) + 1.02f * Constants::TANK_ICON_FIRSTX;

		SDL_RenderCopy(renderer, tankIcon, NULL, tankRectangle);

		column++;
		counter++;
	}

	int fcounter = 0;
	int fcolumn = 0;
	int frow = 0;
	while (fcounter < livesRemaining)
	{
		if (fcolumn == 3)
		{
			fcolumn = 0;
			frow++;
		}


		flagRectangle->y = (frow * Constants::FLAG_ICON_HEIGHT) + 1.5f * Constants::FLAG_ICON_FIRSTY;
		flagRectangle->x = (fcolumn * Constants::FLAG_ICON_WIDTH) + 1.02f * Constants::FLAG_ICON_FIRSTX;
		SDL_RenderCopy(renderer, flagIcon, NULL, flagRectangle);

		fcolumn++;
		fcounter++;
	}
}