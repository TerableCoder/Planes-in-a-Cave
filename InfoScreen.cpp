#include "InfoScreen.h"
#include <SDL.h>
#include <SDL_image.h>


InfoScreen::InfoScreen(SDL_Texture *info, SDL_Texture *btn){
	gBackground=info;
	btn_back=btn;
}

void InfoScreen::handleEvent(SDL_Event&e)
{
	if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inBack = false;


		if(x > BACK_BUTTON_X && x < BACK_BUTTON_X + BACK_BUTTON_WIDTH && y > BACK_BUTTON_Y && y < BACK_BUTTON_Y + BACK_BUTTON_HEIGHT)
			{ inBack = true;}

		if(inBack && e.type == SDL_MOUSEBUTTONUP){
			show=false;
		}

	}
}

void InfoScreen::render(SDL_Renderer *gRenderer)
{
	SDL_Rect bgRect = {0,0, 1280, 720};
	SDL_RenderCopy(gRenderer, gBackground, nullptr, &bgRect);

	SDL_Rect fillRectButton = {BACK_BUTTON_X, BACK_BUTTON_Y, BACK_BUTTON_WIDTH, BACK_BUTTON_HEIGHT};
	SDL_RenderCopyEx(gRenderer, btn_back, nullptr, &fillRectButton, 0.0, nullptr, SDL_FLIP_NONE);

}