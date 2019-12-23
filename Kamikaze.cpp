
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Kamikaze.h"

SDL_Texture* Kamikaze::loadImage(std::string fname, SDL_Renderer *gRenderer) {
  SDL_Texture* newText = nullptr;

  SDL_Surface* startSurf = IMG_Load(fname.c_str());
  if (startSurf == nullptr) {
    std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
  }

  newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	if (newText == nullptr) {
		std::cout << "Unable to create texture from " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(startSurf);

	return newText;
}

Kamikaze::Kamikaze(int x, int y, int w, int h, int delay, SDL_Renderer* gRenderer, int diff) :xPos{(double) x}, yPos{(double) y}, width{w}, height{h}, diff{diff} {
    arrival_time = SDL_GetTicks() + delay;
    last_move = SDL_GetTicks();
    initializeSprites(gRenderer);
    tiltAngle = 0;
}

void Kamikaze::initializeSprites(SDL_Renderer* gRenderer)
{
  if (diff == 1)
      {
        width = 125;
        height = 53;

        sprite1 = loadImage("sprites/EnemyPlaneK1.png", gRenderer);
        sprite2 = loadImage("sprites/EnemyPlaneK2.png", gRenderer);
      }
      else
      {
        int min = 1, max = 9;
        int random_sprite = rand() % (max - min + 1) + min;

        switch (random_sprite)
        {
          case 1:
            width = 178;
            height = 47; 
            sprite1 = loadImage("sprites/a10.png", gRenderer);
            sprite2 = loadImage("sprites/a10.png", gRenderer);
            break;
          case 2:
            width = 124;
            height = 37;
            sprite1 = loadImage("sprites/f16.png", gRenderer);
            sprite2 = loadImage("sprites/f16a.png", gRenderer);
            break;
          case 3: 
            width = 164;
            height = 38;
            sprite1 = loadImage("sprites/f22.png", gRenderer);
            sprite2 = loadImage("sprites/f22.png", gRenderer);
            break;
          case 4:
            width = 125;
            height = 33;
            sprite1 = loadImage("sprites/f35.png", gRenderer);
            sprite2 = loadImage("sprites/f35.png", gRenderer);
            break;
          case 5:
            width = 152;
            height = 42;
            sprite1 = loadImage("sprites/f4.png", gRenderer);
            sprite2 = loadImage("sprites/f4.png", gRenderer);
            break;
          case 6:
            width = 155;
            height = 45;
            sprite1 = loadImage("sprites/mig21.png", gRenderer);
            sprite2 = loadImage("sprites/mig21.png", gRenderer);
            break;
          case 7:
            width = 155;
            height = 50;
            sprite1 = loadImage("sprites/mig21e.png", gRenderer);
            sprite2 = loadImage("sprites/mig21e.png", gRenderer);
            break;
          case 8:
            width = 209;
            height = 38;
            sprite1 = loadImage("sprites/mig31.png", gRenderer);
            sprite2 = loadImage("sprites/mig31a.png", gRenderer);
            break;
          case 9:
            width = 148;
            height = 42;
            sprite1 = loadImage("sprites/mig29.png", gRenderer);
            sprite2 = loadImage("sprites/mig29a.png", gRenderer);
            break;
          case 10:
            width = 176;
            height = 50;
            sprite1 = loadImage("sprites/su24.png", gRenderer);
            sprite2 = loadImage("sprites/su24a.png", gRenderer);
            break;
        }     
      }

      kam_sprite = {(int) xPos, (int) yPos, width, height};
      kam_hitbox = kam_sprite;
}

void Kamikaze::renderKam(int SCREEN_WIDTH, SDL_Renderer* gRenderer) {
	
	kam_sprite = {(int)xPos,(int)yPos,width,height};
    if(xPos < SCREEN_WIDTH){
      if ((SDL_GetTicks() / ANIMATION_FREQ) % 2 == 1)
        SDL_RenderCopyEx(gRenderer, sprite1, nullptr, &kam_sprite, tiltAngle, nullptr, SDL_FLIP_HORIZONTAL);
      else
        SDL_RenderCopyEx(gRenderer, sprite2, nullptr, &kam_sprite, tiltAngle, nullptr, SDL_FLIP_HORIZONTAL);
      kam_hitbox=kam_sprite;
    }
}

void Kamikaze::move(Player* p, int SCREEN_WIDTH){
  xVelo = 0;
  yVelo = 0;
  tiltAngle = 0;
  if (SDL_GetTicks() > arrival_time && xPos > SCREEN_WIDTH - width - 10) {
    xVelo = -MAX_MOVE_VELO;
    shootable = false;
  }
  else{
    shootable = true;
    if (yPos > p->getPosY()+(height/2)){
      tiltAngle = 15;
      yVelo = -MAX_MOVE_VELO;
    }

    if (yPos < p->getPosY()-(height/2)){
      tiltAngle = -15;
      yVelo = MAX_MOVE_VELO;
    }

    if (xPos < p->getPosX()){
      tiltAngle = 0;
      yVelo = 0;
    }
  }
  if (SDL_GetTicks() > ASSAULT_FREQ + arrival_time){
      xVelo = -MAX_ASSAULT_VELO;
  }

  time_since_move = SDL_GetTicks() - last_move;
  xPos += (double) (xVelo * time_since_move)/1000;
  yPos += (double) (yVelo * time_since_move)/1000;
  kam_sprite = {(int)xPos,(int)yPos,width,height};
  kam_hitbox = kam_sprite;
  last_move = SDL_GetTicks();
}

// Checks if the kamikaze collided with a bullet, returning true if so
bool Kamikaze::checkCollisionBullet(int bullX, int bullY, int bullW, int bullH) {
	return checkCollide(bullX, bullY, bullW, bullH, xPos, yPos, width, height);
}

bool Kamikaze::checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight)
{
    if (x + pWidth < xTwo || x > xTwo + pTwoWidth)
        return false;
    if (y + pHeight < yTwo || y > yTwo + pTwoHeight)
        return false;
    return true;
}

int Kamikaze::getX(){
  return (int) xPos;
}

int Kamikaze::getY(){
  return (int) yPos;
}

void Kamikaze::setX(int x){
  xPos = x;
}

void Kamikaze::setY(int y){
  yPos = y;
}

int Kamikaze::getWidth() {
  return width;
}

int Kamikaze::getHeight() {
  return height;
}

SDL_Rect* Kamikaze::getHitbox(){
  return &kam_hitbox;
}

void Kamikaze::setArrivalTime(int delay){
  arrival_time = SDL_GetTicks()+delay;
}

bool Kamikaze::blast(){
  return shootable;
}

void Kamikaze::moveRight() {
	time_since_move = SDL_GetTicks() - last_move;
	xPos += (double) (MAX_MOVE_VELO * time_since_move) / 1000;
	last_move = SDL_GetTicks();
}
