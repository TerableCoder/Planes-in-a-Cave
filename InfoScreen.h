#ifndef InfoScreen_H
#define InfoScreen_H

#include <SDL.h>
#include "Player.h"

class InfoScreen
{
public:
    InfoScreen(SDL_Texture *info, SDL_Texture *btn);
    static const int BACK_BUTTON_WIDTH = 250;
    static const int BACK_BUTTON_HEIGHT = 80;
    static const int BACK_BUTTON_X = 50;
    static const int BACK_BUTTON_Y = 25;

    bool show=true;

    SDL_Texture* gBackground;
    SDL_Texture* btn_back;

    void handleEvent(SDL_Event &e);
    void render(SDL_Renderer *gRenderer);
};

#endif