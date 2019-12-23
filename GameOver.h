#ifndef GameOver_H
#define GameOver_H

#include <SDL.h>
#include "Player.h"
#include "MapBlocks.h"

class GameOver
{
public:
    bool isGameOver = false;
    // constexpr int SCREEN_WIDTH = 1280;
    // constexpr int SCREEN_HEIGHT = 720;
    static const int RESTART_BUTTON_WIDTH = 200;
    static const int RESTART_BUTTON_HEIGHT = 50;
    static const int RESTART_BUTTON_X = (int)(1280/2) - 100;
    static const int RESTART_BUTTON_Y = (int)(720/1.5) - 25;
    GameOver(SDL_Texture *cred, SDL_Texture *rest);

    SDL_Texture* btn_restart;
    SDL_Texture* btn_credits;
	int diff;

    static const int CRED_BUTTON_WIDTH = 200;
    static const int CRED_BUTTON_HEIGHT = 50;
    static const int CRED_BUTTON_X = (int)(1280/2) - 100;
    static const int CRED_BUTTON_Y = (int)(720/1.5) + 50;

    void stopGame(Player*);
    int handleEvent(SDL_Event &e, SDL_Renderer *gRenderer);
    void render(SDL_Renderer *gRenderer);
    void displayCredits(SDL_Renderer* gRenderer);
private:
    void restart(SDL_Renderer *gRenderer);
    int LEVEL_WIDTH = 100000;
    int LEVEL_HEIGHT = 2000;
};

#endif