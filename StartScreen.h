#ifndef StartScreen_H
#define StartScreen_H

#include <SDL.h>
#include "Player.h"

class StartScreen
{
public:
    StartScreen(SDL_Texture *start, SDL_Texture *btn, SDL_Texture *info);
    static const int START_BUTTON_WIDTH = 250;
    static const int START_BUTTON_HEIGHT = 80;
    static const int START_BUTTON_X = 1280 - 400;
    static const int START_BUTTON_Y = 720 - 150;
    static const int INFO_BUTTON_WIDTH = 250;
    static const int INFO_BUTTON_HEIGHT = 80;
    static const int INFO_BUTTON_X = 400-INFO_BUTTON_WIDTH;
    static const int INFO_BUTTON_Y = 720 - 150;

    bool notStarted = true;
    bool infoMenu=false;

    SDL_Texture* gBackground;
    SDL_Texture* btn_start;
    SDL_Texture* btn_info;


    void handleEvent(SDL_Event &e);
    void render(SDL_Renderer *gRenderer);
};

#endif