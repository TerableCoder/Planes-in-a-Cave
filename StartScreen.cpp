#include "StartScreen.h"
#include <SDL.h>
#include <SDL_image.h>


StartScreen::StartScreen(SDL_Texture *start, SDL_Texture *btn, SDL_Texture *info){
	gBackground=start;
	btn_start=btn;
	btn_info=info;
}

void StartScreen::handleEvent(SDL_Event&e)
{
	if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inStart = false;
		bool inInfo = false;

		if(x > START_BUTTON_X && x < START_BUTTON_X + START_BUTTON_WIDTH && y > START_BUTTON_Y && y < START_BUTTON_Y + START_BUTTON_HEIGHT)
			{ inStart = true;}

		if(x > INFO_BUTTON_X && x < INFO_BUTTON_X + INFO_BUTTON_WIDTH && y > INFO_BUTTON_Y && y < INFO_BUTTON_Y + INFO_BUTTON_HEIGHT)
			{ inInfo = true;}

		if(inStart && e.type == SDL_MOUSEBUTTONUP){
			notStarted=false;
		}
		if(inInfo && e.type == SDL_MOUSEBUTTONUP){
			infoMenu=true;
		}
	}
}

void StartScreen::render(SDL_Renderer *gRenderer)
{
	SDL_Rect bgRect = {0,0, 1280, 720};
	SDL_RenderCopy(gRenderer, gBackground, nullptr, &bgRect);

	SDL_Rect fillRectButton = {START_BUTTON_X, START_BUTTON_Y, START_BUTTON_WIDTH, START_BUTTON_HEIGHT};
	SDL_RenderCopyEx(gRenderer, btn_start, nullptr, &fillRectButton, 0.0, nullptr, SDL_FLIP_NONE);

	SDL_Rect fillRectInfo = {INFO_BUTTON_X, INFO_BUTTON_Y, INFO_BUTTON_WIDTH, INFO_BUTTON_HEIGHT};
	SDL_RenderCopyEx(gRenderer, btn_info, nullptr, &fillRectInfo, 0.0, nullptr, SDL_FLIP_NONE);
}

