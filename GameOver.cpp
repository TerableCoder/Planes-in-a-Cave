#include "GameOver.h"
#include <SDL.h>
#include "Player.h"
#include "MapBlocks.h"
#include <SDL_image.h>
#include "CaveSystem.h"
#include "DifficultySelectionScreen.h"

GameOver::GameOver(SDL_Texture *cred, SDL_Texture *rest){
    btn_restart = rest;
    btn_credits = cred;
};

void GameOver::stopGame(Player *player)
{
    player->setVelX(0);
    player->setVelY(0);
}

int GameOver::handleEvent(SDL_Event &e, SDL_Renderer *gRenderer)
{

    //If mouse event happened
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside_restart_button = true;
        bool inside_cred_button = true;

        if (x < RESTART_BUTTON_X){ inside_restart_button = false; }
        else if (x > RESTART_BUTTON_X + RESTART_BUTTON_WIDTH){ inside_restart_button = false; }
        else if (y < RESTART_BUTTON_Y){ inside_restart_button = false; }
        else if (y > RESTART_BUTTON_Y + RESTART_BUTTON_HEIGHT){ inside_restart_button = false; }

        if (inside_restart_button && e.type == SDL_MOUSEBUTTONUP){
            restart(gRenderer);
            return 0;
        }

        if (x < CRED_BUTTON_X){ inside_cred_button = false; }
        else if (x > CRED_BUTTON_X + CRED_BUTTON_WIDTH){ inside_cred_button = false; }
        else if (y < CRED_BUTTON_Y){ inside_cred_button = false; }
        else if (y > CRED_BUTTON_Y + CRED_BUTTON_HEIGHT){ inside_cred_button = false; }

        if (inside_cred_button && e.type == SDL_MOUSEBUTTONUP){
            displayCredits(gRenderer);
            return 1;
        }
    }
    return 0;
}

void GameOver::render(SDL_Renderer *gRenderer)
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xa1);
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    SDL_Rect fillRectOverlay = {0, 0, 1280, 720};
    SDL_RenderFillRect(gRenderer, &fillRectOverlay);

    // SDL_SetRenderDrawColor(gRenderer, 0x4F, 0xa7, 0x00, 0xFF);
    SDL_Rect fillRectRestartButton = {RESTART_BUTTON_X, RESTART_BUTTON_Y, RESTART_BUTTON_WIDTH, RESTART_BUTTON_HEIGHT};
    // SDL_RenderFillRect(gRenderer, &fillRectButton);

    SDL_Texture *restart_button_texture = nullptr;
    
    restart_button_texture = btn_restart;
    SDL_RenderCopyEx(gRenderer, restart_button_texture, nullptr, &fillRectRestartButton, 0.0, nullptr, SDL_FLIP_NONE);

    SDL_Rect fillRectCredButton = {CRED_BUTTON_X, CRED_BUTTON_Y, CRED_BUTTON_WIDTH, CRED_BUTTON_HEIGHT};

    SDL_Texture *cred_button_texture = nullptr;
   
    cred_button_texture = btn_credits;
    SDL_RenderCopyEx(gRenderer, cred_button_texture, nullptr, &fillRectCredButton, 0.0, nullptr, SDL_FLIP_NONE);
}

void GameOver::restart(SDL_Renderer* gRenderer)
{
    DifficultySelectionScreen *diff_sel_screen;

    SDL_Texture *back_tex = nullptr;
    SDL_Surface *back_surf = IMG_Load("sprites/DiffScreen.png");
    back_tex = SDL_CreateTextureFromSurface(gRenderer, back_surf);
    SDL_FreeSurface(back_surf);

    SDL_Texture *e_tex = nullptr;
    SDL_Surface *e_surf = IMG_Load("sprites/easy_button.png");
    e_tex = SDL_CreateTextureFromSurface(gRenderer, e_surf);
    SDL_FreeSurface(e_surf);

    SDL_Texture *m_tex = nullptr;
    SDL_Surface *m_surf = IMG_Load("sprites/med_button.png");
    m_tex = SDL_CreateTextureFromSurface(gRenderer, m_surf);
    SDL_FreeSurface(m_surf);

    SDL_Texture *h_tex = nullptr;
    SDL_Surface *h_surf = IMG_Load("sprites/hard_button.png");
    h_tex = SDL_CreateTextureFromSurface(gRenderer, h_surf);
    SDL_FreeSurface(h_surf);
    

    diff_sel_screen = new DifficultySelectionScreen(back_tex, e_tex, m_tex, h_tex);
    SDL_Event e;
    diff = 0;
    while(diff == 0){
		while(SDL_PollEvent(&e)) {
			if(e.type==SDL_QUIT){
				diff=4;
			}
			diff = diff_sel_screen->handleEvent(e);
		}
		diff_sel_screen->render(gRenderer);
		SDL_RenderPresent(gRenderer);
	}
    isGameOver = false;
}

void GameOver::displayCredits(SDL_Renderer* gRenderer){

    std::vector<SDL_Texture*> gTex;
	// SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

	// Initialize PNG loading via SDL_image extension library
	int imgFlags = IMG_INIT_PNG;
	int retFlags = IMG_Init(imgFlags);

	// Load media
    SDL_Texture* newText = nullptr;
	SDL_Surface* startSurf = IMG_Load("slides/Hellested_credit_roll.png");
	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	SDL_FreeSurface(startSurf);
    gTex.push_back(newText);

    startSurf = IMG_Load("slides/dilan.png");
	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	SDL_FreeSurface(startSurf);
    gTex.push_back(newText);

    startSurf = IMG_Load("slides/Trant-RandomLevelGeneration.png");
	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	SDL_FreeSurface(startSurf);
    gTex.push_back(newText);

    startSurf = IMG_Load("slides/JakeZomperCredit.png");
	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	SDL_FreeSurface(startSurf);
    gTex.push_back(newText);

    startSurf = IMG_Load("slides/Kenneth Choo Physics.png");
	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	SDL_FreeSurface(startSurf);
    gTex.push_back(newText);

    startSurf = IMG_Load("slides/Faruk Yucel.png");
	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	SDL_FreeSurface(startSurf);
    gTex.push_back(newText);

    startSurf = IMG_Load("slides/mdcredit.PNG");
	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	SDL_FreeSurface(startSurf);
    gTex.push_back(newText);

    startSurf = IMG_Load("slides/connor_schwartz_credit.png");
	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	SDL_FreeSurface(startSurf);
    gTex.push_back(newText);

    startSurf = IMG_Load("slides/Brandon's Credit 1.png");
	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	SDL_FreeSurface(startSurf);
    gTex.push_back(newText);

    startSurf = IMG_Load("slides/jeroen_credit1280x720.png");
	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	SDL_FreeSurface(startSurf);
    gTex.push_back(newText);

	SDL_RenderClear(gRenderer);

	SDL_RenderCopy(gRenderer, gTex[0], NULL, NULL);
	SDL_RenderPresent(gRenderer);
	int time = SDL_GetTicks();
	while (SDL_GetTicks() - time < 3000) {
		SDL_PumpEvents();
	}

	SDL_RenderCopy(gRenderer, gTex[1], NULL, NULL);
	SDL_RenderPresent(gRenderer);
	time = SDL_GetTicks();
	while (SDL_GetTicks() - time < 3000) {
		SDL_PumpEvents();
	}

    SDL_RenderCopy(gRenderer, gTex[2], NULL, NULL);
	SDL_RenderPresent(gRenderer);
	time = SDL_GetTicks();
	while (SDL_GetTicks() - time < 3000) {
		SDL_PumpEvents();
	}

    SDL_RenderCopy(gRenderer, gTex[3], NULL, NULL);
	SDL_RenderPresent(gRenderer);
	time = SDL_GetTicks();
	while (SDL_GetTicks() - time < 3000) {
		SDL_PumpEvents();
	}

    SDL_RenderCopy(gRenderer, gTex[4], NULL, NULL);
	SDL_RenderPresent(gRenderer);
	time = SDL_GetTicks();
	while (SDL_GetTicks() - time < 3000) {
		SDL_PumpEvents();
	}

    SDL_RenderCopy(gRenderer, gTex[5], NULL, NULL);
	SDL_RenderPresent(gRenderer);
	time = SDL_GetTicks();
	while (SDL_GetTicks() - time < 3000) {
		SDL_PumpEvents();
	}

    SDL_RenderCopy(gRenderer, gTex[6], NULL, NULL);
	SDL_RenderPresent(gRenderer);
	time = SDL_GetTicks();
	while (SDL_GetTicks() - time < 3000) {
		SDL_PumpEvents();
	}

    SDL_RenderCopy(gRenderer, gTex[7], NULL, NULL);
	SDL_RenderPresent(gRenderer);
	time = SDL_GetTicks();
	while (SDL_GetTicks() - time < 3000) {
		SDL_PumpEvents();
	}

    SDL_RenderCopy(gRenderer, gTex[8], NULL, NULL);
	SDL_RenderPresent(gRenderer);
	time = SDL_GetTicks();
	while (SDL_GetTicks() - time < 3000) {
		SDL_PumpEvents();
	}

    SDL_RenderCopy(gRenderer, gTex[9], NULL, NULL);
	SDL_RenderPresent(gRenderer);
	time = SDL_GetTicks();
	while (SDL_GetTicks() - time < 3000) {
		SDL_PumpEvents();
	}

	for (auto i : gTex) {
		SDL_DestroyTexture(i);
		i = nullptr;
	}

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
