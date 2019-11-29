#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include "Boss.h"
#include "bullet.h"
#include "missile.h"

SDL_Texture* Boss::loadImage(std::string fname, SDL_Renderer *gRenderer) {
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

Boss::Boss(int x, int y, int xvel, int yvel, int diff, SDL_Renderer *gRenderer): xPos{(double) x}, yPos{(double) y},maxXVelo{xvel},maxYVelo{yvel}{
  boss_sprite = {(int) xPos, (int) yPos, WIDTH, HEIGHT};
  boss_hitbox_bottom = {(int) xPos, (int) (yPos+(HEIGHT/2)), WIDTH, HEIGHT/2};
  boss_hitbox_top = {(int) (xPos+(WIDTH/4)), (int) yPos, WIDTH/2, HEIGHT};
  last_move = SDL_GetTicks();
  time_since_pattern = SDL_GetTicks();
  last_shot_missile = SDL_GetTicks() - FIRING_FREQ;
  last_shot_down = last_shot_missile;
  last_shot_up = last_shot_missile;
  // Index number of the pattern currently being used. 0 represents no pattern
  pattern = 0;
  // Phase within whichever pattern is being used
  phase = 1;
  // Number of missiles fired within the current phase
  numFired = 0;
  maxXVelo = 200;
  maxYVelo = 200;
  last_pattern = 0;
  if(diff == 3){
	max_health = 2000;
  }
  else if(diff == 2){
	max_health = 1500;
  }
  else{
	max_health = 1000;
  }
  health = max_health;
  difficulty = diff;
  //sprite1 = loadImage(name, gRenderer);
}

// IF YOU CREATE ANY POINTERS, DELETE THEM IN THIS METHOD
Boss::~Boss() {

}


void Boss::renderBoss(int SCREEN_WIDTH, SDL_Renderer* gRenderer){
    if(xPos<SCREEN_WIDTH){
      //SDL_RenderCopyEx(gRenderer, sprite1, nullptr, &boss_sprite, 0, nullptr, SDL_FLIP_NONE);
      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(gRenderer, &boss_hitbox_top);
      SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
      SDL_RenderFillRect(gRenderer, &boss_hitbox_bottom);
      boss_hitbox_bottom = {(int) xPos, (int) (yPos+(HEIGHT/2)), WIDTH, HEIGHT/2};
      boss_hitbox_top = {(int) (xPos+(WIDTH/4)), (int) yPos, WIDTH/2, HEIGHT};
    }
}

void Boss::move(int SCREEN_WIDTH){
	xVelo = 0;
	time_since_pattern = SDL_GetTicks() - last_pattern;
	if (time_since_pattern >= PATTERN_DELAY && pattern == 0){
		pattern = (rand() % NUM_PATTERNS) + 1;
	}
	if (pattern == 1) {
		patternOne(SCREEN_WIDTH);
  }
	else if (pattern == 2) {
		patternTwo(SCREEN_WIDTH);
	}
  else if (pattern == 3){
    patternThree(SCREEN_WIDTH);
  }
	else{
		if (yVelo == 0) {
			yVelo = maxYVelo;
	    }
	    else if (yVelo > 0 && yPos > MAX_DOWN) {
			yVelo = -maxYVelo;
	    }
	    else if (yVelo < 0 && yPos < MAX_UP) {
			yVelo = maxYVelo;
	    }
	}
	time_since_move = SDL_GetTicks() - last_move;
	xPos += (double) (xVelo * time_since_move)/1000;
	yPos += (double) (yVelo * time_since_move)/1000;
	boss_sprite = {(int)xPos,(int)yPos,WIDTH,HEIGHT};
	boss_hitbox_bottom = {(int) xPos, (int) (yPos+(HEIGHT/2)), WIDTH, HEIGHT/2};
	boss_hitbox_top = {(int) (xPos+(WIDTH/4)), (int) yPos, WIDTH/2, HEIGHT};
	last_move = SDL_GetTicks();
}

bool Boss::checkCollision(int x, int y, int w, int h) {
	// Check collision with the top part
	if (checkCollide(x, y, w, h, xPos, yPos + HEIGHT/2, WIDTH, HEIGHT/2)) {
		return true;
	}
	// Check collision with the bottom part
	else if (checkCollide(x, y, w, h, xPos + WIDTH/4, yPos, WIDTH/2, HEIGHT)) {
		return true;
	}
	else {
		return false;
	}
}

bool Boss::checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight)
{
    if (x + pWidth < xTwo || x > xTwo + pTwoWidth)
        return false;
    if (y + pHeight < yTwo || y > yTwo + pTwoHeight)
        return false;
    return true;
}

std::vector<Missile*> Boss::handleFiringMissile(std::vector<Missile*> missiles ,int x, int y, SDL_Renderer* gRenderer){
  time_since_shot_missile = SDL_GetTicks() - last_shot_missile;
  if(pattern == 1){
	  missiles = handleFiringMissilePatternOne(missiles, x, y, gRenderer);
  }
  if (pattern == 2) {
	  missiles = handleFiringMissilePatternTwo(missiles, x, y, gRenderer);
  }
  if (pattern == 3){
    missiles = handleFiringMissilePatternThree(missiles, x, y, gRenderer);
  }
  return missiles;
}

// Firing for pattern 1
std::vector<Missile*> Boss::handleFiringMissilePatternOne(std::vector<Missile*> missiles, int x, int y, SDL_Renderer* gRenderer) {
	int damage = 500;
	int blast_radius = 150;
	Missile* m = nullptr;
	int xDist = x - xPos;
    int yDist = y - (yPos+(HEIGHT/2));
    double math = (double)xDist / sqrt(xDist * xDist + yDist * yDist) * 400;
    double math2 = ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400;
    // Firing in top right corner
	if(needsFiring && phase == 1){
      m = new Missile(damage, blast_radius, xPos, yPos+HEIGHT, ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, loadImage("sprites/missile.png", gRenderer), gRenderer);
      needsFiring = false;
	  numFired = 1;
    }
	// Firing in top left corner
	else if (needsFiring && phase == 2){
      m = new Missile(damage, blast_radius, xPos+WIDTH, yPos+HEIGHT, ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, loadImage("sprites/missile.png", gRenderer), gRenderer);
      needsFiring = false;
	  numFired = 2;
    }
	// Firing in bottom left corner
	else if (needsFiring && phase == 3){
      m = new Missile(damage, blast_radius, xPos+WIDTH, yPos+(HEIGHT/2), ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, loadImage("sprites/missile.png", gRenderer), gRenderer);
      needsFiring = false;
	  numFired = 3;
    }
	// Firing in bottom right corner
	else if (needsFiring && phase == 4){
      m = new Missile(damage, blast_radius, xPos, yPos+(HEIGHT/2), ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, loadImage("sprites/missile.png", gRenderer), gRenderer);
      needsFiring = false;
	  numFired = 4;
    }
	// Add the new missile if there is one
    if (m != nullptr)
      missiles.push_back(m);
	return missiles;
}

// Firing for pattern 2
std::vector<Missile*> Boss::handleFiringMissilePatternTwo(std::vector<Missile*> missiles, int x, int y, SDL_Renderer* gRenderer) {
	int damage = 500;
	int blast_radius = 150;
	int xDist = x - xPos;
    int yDist = y - (yPos+(HEIGHT/2));
    double math = (double)xDist / sqrt(xDist * xDist + yDist * yDist) * 400;
    double math2 = ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400;
	// Fire a missile to the left if in phases 2 or 3
	if ((phase == 2 || phase == 3) && time_since_shot_missile >= PATTERN_TWO_FIRING_FREQ){
		Missile * m = new Missile(damage, blast_radius, xPos, yPos+(HEIGHT/2), ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, loadImage("sprites/missile.png", gRenderer), gRenderer);
		missiles.push_back(m);
		last_shot_missile = SDL_GetTicks();
    }
	return missiles;
}
	
std::vector<Missile*> Boss::handleFiringMissilePatternThree(std::vector<Missile*> missiles, int x, int y, SDL_Renderer* gRenderer)
{
  int damage = 500;
  int blast_radius = 150;
  int xDist = x - xPos;
  int yDist = y - (yPos + (HEIGHT / 2));
  double math = (double)xDist / sqrt(xDist * xDist + yDist * yDist) * 400;
  double math2 = ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400;
  // Fire a missile to the left if in phases 2 or 3
  if ((phase == 2 || phase == 3) && time_since_shot_missile >= PATTERN_TWO_FIRING_FREQ)
  {
    Missile *m = new Missile(damage, blast_radius, xPos, yPos + (HEIGHT / 2), ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, loadImage("sprites/missile.png", gRenderer), gRenderer);
    missiles.push_back(m);
    last_shot_missile = SDL_GetTicks();
  }
  return missiles;
}


Bullet* Boss::handleFiringUp(){
  return nullptr;
}

Bullet* Boss::handleFiringDown(){
  return nullptr;
}

void Boss::hit(int d){
  if (health - d < 0)
    health = 0;
  else
    health -= d;
}

int Boss::getX(){
  return (int) xPos;
}

int Boss::getY(){
  return (int) yPos;
}

int Boss::getWidth() {
  return WIDTH;
}

int Boss::getHeight() {
  return HEIGHT;
}

int Boss::getHealth(){
  return health;
}

double Boss::getHealthPercentage() {
	return 100.0 * health / max_health;
}

void Boss::moveLeft() {
	time_since_move = SDL_GetTicks() - last_move;
	xPos -= (double) (maxXVelo * time_since_move) / 1000;
	last_move = SDL_GetTicks();
}

// Movement for pattern 1
void Boss::patternOne(int SCREEN_WIDTH){
  xVelo = 0;
  yVelo = 0;
  // Phase 1: move to the top right and shoot a missile
  if(phase == 1){
    if (yPos > MAX_UP)
      yVelo = -maxYVelo;
    else{
      yVelo = 0;
	  if (numFired < 1) needsFiring = true;
    }

    if (time_since_pattern - PATTERN_DELAY >= pattern_one_delay){
      phase = 2;
    }

  }
  // Phase 2: move to the top left and shoot a missile
  else if(phase == 2){

    if (xPos > 50){
      xVelo = -(maxXVelo*2);
      yVelo = 0;
    }else{
      xVelo = 0;
      yVelo = 0;
	  if (numFired < 2) needsFiring = true;
    }

    if ((time_since_pattern - PATTERN_DELAY) >= pattern_one_delay*2){
	  phase = 3;
    }

  }
  // Phase 3: move to the bottom left and shoot a missile
  else if(phase == 3){
    if (yPos < MAX_DOWN){
      xVelo = 0;
      yVelo = maxYVelo;
    }else{
      xVelo = 0;
      yVelo = 0;
	  if (numFired < 3) needsFiring = true;
    }

      if ((time_since_pattern-PATTERN_DELAY) >= pattern_one_delay*3){
		  phase = 4;
      }

  }
  // Phase 4: move to the bottom right and shoot a missile
  else if(phase == 4){
    if (xPos < SCREEN_WIDTH - WIDTH - 50){
      xVelo = (maxXVelo*2);
      yVelo = 0;
    }else{
      xVelo = 0;
      yVelo = 0;
      if (numFired < 4) needsFiring = true;
    }

    if (time_since_pattern-PATTERN_DELAY >= pattern_one_delay*4)
      phase = 5;
  }

  // At the end of the pattern, reset everything so that another pattern can be used
  if(phase == 5){
	phase = 1;
    last_pattern = SDL_GetTicks();
	pattern = 0;
	numFired = 0;
  }
}

// Movement for pattern 2
void Boss::patternTwo(int SCREEN_WIDTH)
{
	xVelo = 0;
	yVelo = 0;
	// Phase 1: move to starting position at bottom of screen
	if (phase == 1) {
		int x_dist_to_start = SCREEN_WIDTH - 250 - WIDTH - xPos;
		int y_dist_to_start = MAX_DOWN - yPos;
		xVelo = maxXVelo * ((double)x_dist_to_start / (-x_dist_to_start + y_dist_to_start));
		yVelo = maxYVelo * ((double)y_dist_to_start / (-x_dist_to_start + y_dist_to_start));
		if (x_dist_to_start > -5 && y_dist_to_start < 5) {
			phase = 2;
		}
	}
	// Phase 2: move to the top of the screen while firing
	else if (phase == 2) {
		yVelo = -maxYVelo;
		if (yPos < MAX_UP) {
			phase = 3;
		}
	}
	// Phase 3: move to the bottom of the screen while firing
	else if (phase == 3) {
		yVelo = maxYVelo;
		if (yPos > MAX_DOWN) {
			phase = 4;
		}
	}
	// Phase 4: go back to the starting position
	else if (phase == 4) {
		int x_dist_to_start = SCREEN_WIDTH - 50 - WIDTH - xPos;
		int y_dist_to_start = (MAX_DOWN + MAX_UP) / 2 - yPos;
		xVelo = maxXVelo * ((double)x_dist_to_start / (x_dist_to_start - y_dist_to_start));
		yVelo = maxYVelo * ((double)y_dist_to_start / (x_dist_to_start - y_dist_to_start));
		if (x_dist_to_start < 5 && y_dist_to_start > -5) {
			phase = 5;
		}
	}
	// Phase 5: reset everything so that another pattern can be used
	if (phase == 5) {
		phase = 1;
		last_pattern = SDL_GetTicks();
		pattern = 0;
		numFired = 0;
	}
}

void Boss::patternThree(int SCREEN_WIDTH)
{
  xVelo = 0;
  yVelo = 0;

  if (phase == 1)
  {
    // Moving to start position
    int x_dist_to_start = SCREEN_WIDTH / 2 - WIDTH / 2 - xPos;
    int y_dist_to_start = MAX_DOWN / 2 - HEIGHT / 2 - yPos;
    xVelo = maxXVelo * ((double)x_dist_to_start / (-x_dist_to_start + y_dist_to_start));
    yVelo = maxYVelo * ((double)y_dist_to_start / (-x_dist_to_start + y_dist_to_start));
    if (x_dist_to_start > -5 && y_dist_to_start < 5)
    {
      phase = 2;
    }
  }
  // Phase 2: move to the left of the screen while firing
  else if (phase == 2)
  {
    yVelo = 0;
    xVelo = -maxXVelo;
    if (xPos < 1)
    {
      phase = 3;
    }
  }
  // Phase 3: move to the right of the screen while firing
  else if (phase == 3)
  {
    yVelo = 0;
    xVelo = maxXVelo;
    if (xPos > SCREEN_WIDTH - WIDTH - 1)
    {
      phase = 4;
    }
  }
  // Phase 4: go back to the starting position
  else if (phase == 4)
  {
    int x_dist_to_start = SCREEN_WIDTH / 2 - WIDTH / 2 - xPos;
    int y_dist_to_start = MAX_DOWN / 2 - HEIGHT / 2 - yPos;
    xVelo = maxXVelo * ((double)x_dist_to_start / (-x_dist_to_start + y_dist_to_start));
    yVelo = maxYVelo * ((double)y_dist_to_start / (-x_dist_to_start + y_dist_to_start));
    if (x_dist_to_start < 5 && y_dist_to_start > -5)
    {
      phase = 5;
    }
  }
  // Phase 5: reset everything so that another pattern can be used
  if (phase == 5)
  {
    phase = 1;
    last_pattern = SDL_GetTicks();
    pattern = 0;
    numFired = 0;
  }
}
