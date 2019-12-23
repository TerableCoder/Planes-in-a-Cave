
#include "bullet.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include "Enemy.h"


SDL_Texture* Enemy::loadImage(std::string fname, SDL_Renderer *gRenderer) {
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

    Enemy::Enemy(int x, int y, int w, int h, int xvel, int yvel, int diff, SDL_Renderer *gRenderer) :xPos{(double) x}, yPos{(double) y},maxXVelo{xvel},maxYVelo{yvel}, diff{diff} {
		initializeSprites(gRenderer);
		tiltAngle = 0;
	  	last_move = SDL_GetTicks();
		time_hit = SDL_GetTicks() - FLICKER_TIME;
		last_shot = SDL_GetTicks() - FIRING_FREQ;
		is_destroyed = false;
		if(diff == 3){
			health = 20;
		}
		else if(diff == 2){
			health = 15;
		}
		else{
			health = 10;
		}

		prev_direction = 0;
		hit_sound = Mix_LoadWAV("sounds/player_hit.wav");
    }

	Enemy::~Enemy() {
		SDL_DestroyTexture(sprite1);
		SDL_DestroyTexture(sprite2);
		Mix_FreeChunk(hit_sound);
	}

	void Enemy::initializeSprites(SDL_Renderer *gRenderer)
	{
		if (diff == 1)
		{
			width = 125;
			height = 53;

			enemy_sprite = {(int) xPos, (int) yPos, width, height};
			enemy_hitbox = enemy_sprite;
			sprite1 = loadImage("sprites/EnemyPlane1.png", gRenderer);
			sprite2 = loadImage("sprites/EnemyPlane3.png", gRenderer);
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

		enemy_sprite = {(int) xPos, (int) yPos, width, height};
		enemy_hitbox = enemy_sprite;
	}

    void Enemy::renderEnemy(SDL_Renderer* gRenderer){
		enemy_sprite = {(int)xPos,(int)yPos,width,height};
		if ((SDL_GetTicks() - time_hit) <= FLICKER_TIME && ((SDL_GetTicks() - time_hit) / FLICKER_FREQ) % 2 == 0) {
			return;
		}

		if (!is_destroyed){
			if ((SDL_GetTicks() / ANIMATION_FREQ) % 2 == 1) {
				SDL_RenderCopyEx(gRenderer, sprite1, nullptr, &enemy_sprite, tiltAngle, nullptr, SDL_FLIP_NONE);
			}
			else {
				SDL_RenderCopyEx(gRenderer, sprite2, nullptr, &enemy_sprite, tiltAngle, nullptr, SDL_FLIP_NONE);
			}
			enemy_hitbox=enemy_sprite;
		}

		if ((SDL_GetTicks() - time_destroyed) >= SPAWN_FREQ && is_destroyed){
			xPos = -width;
			health = 20;
			is_destroyed = false;
		}
    }

    void Enemy::move(int playerX, int playerY, std::vector<int> bulletX, std::vector<int> bulletY, std::vector<int> bulletVelX, std::vector<int> bulletVelY, std::vector<int> stalagmX, std::vector<int> stalagmH, std::vector<int> stalagtX, std::vector<int> stalagtH, std::vector<int> turretX, std::vector<int> turretH, std::vector<int> turretBottom, int kamiX, int kamiY, int cave_y)
    {
		time_since_move = SDL_GetTicks() - last_move;
		// If the enemy is offscreen, have them move right
		if (xPos <= MIN_X)
		{
			xPos += (double) (maxXVelo * time_since_move) / 1000;
		}
		// If there is no cave, use the risk scores
		else if (cave_y == -1)
		{
			xVelo = 0;
			yVelo = 0;

			// tiltAngle = 0;
			calculateRiskscores(playerX, playerY, bulletX, bulletY, bulletVelX, bulletVelY, kamiX, kamiY, stalagmX, stalagmH, stalagtX, stalagtH, turretX, turretH, turretBottom);
			int direction = chooseDirection();

			// Move right if that's the optimal direction
			if(direction == 3 || direction == 4 || direction == 5 || (direction == 0 && ((xPos - width/2 - MIN_X % SQUARE_WIDTH) < SQUARE_WIDTH / 4))){
				xVelo = maxXVelo;
			}
			// Move left if that's the optimal direction
			if (direction == 1 || direction == 8 || direction == 7 || (direction == 0 && ((xPos - width/2 - MIN_X % SQUARE_WIDTH) > 3 * SQUARE_WIDTH / 4))) {
				xVelo = -maxXVelo;
			}
			// Move up if that's the optimal direction
			if (direction == 1 || direction == 2 || direction == 3 || (direction == 0 && ((yPos - height/2 - MIN_Y % SQUARE_WIDTH) > 3 * SQUARE_WIDTH / 4))) {
				yVelo = -maxYVelo;
				// tiltAngle = 15;
			}
			// Move down if that's the optimal direction
			if (direction == 5 || direction == 6 || direction == 7 || (direction == 0 && ((yPos - height/2 - MIN_Y % SQUARE_WIDTH) < SQUARE_WIDTH / 4))) {
				yVelo = maxYVelo;
				// tiltAngle = -15;
			}

			xPos += (double) (xVelo * time_since_move) / 1000;
			yPos += (double) (yVelo * time_since_move) / 1000;
			prev_direction = direction;
		}
		// Otherwise, just follow the cave
		else
		{
			if (cave_y > yPos + height / 2 + 5) yPos += (double) (maxYVelo * time_since_move) / 1000;
			else if (cave_y < yPos + height / 2 - 5) yPos -= (double) (maxYVelo * time_since_move) / 1000;
		}
		last_move = SDL_GetTicks();
    }

	/*
	Directions are numbered as follows:
	1	2	3
	8	0	4
	7	6	5
	This method just chooses the adjacent square with the lowest risk score.
	Ties are broken randomly to make the enemy's movement more chaotic.
	*/
	int Enemy::chooseDirection() {
		current_x_square = (xPos - width/2 - MIN_X) / SQUARE_WIDTH;
		current_y_square = (yPos - height/2 - MIN_Y) / SQUARE_WIDTH;
		double minRisk = riskScores[current_x_square][current_y_square];
		std::vector<int> leastRisky;
		leastRisky.push_back(0);

		if (current_y_square > 0) {
			if (minRisk >= riskScores[current_x_square][current_y_square-1]) {
				if (minRisk > riskScores[current_x_square][current_y_square-1]) {
					leastRisky.clear();
					minRisk = riskScores[current_x_square][current_y_square-1];
				}
				leastRisky.push_back(2);
			}
			if (current_x_square > 0) {
				if (minRisk >= riskScores[current_x_square-1][current_y_square-1]) {
					if (minRisk > riskScores[current_x_square-1][current_y_square-1]) {
						leastRisky.clear();
						minRisk = riskScores[current_x_square-1][current_y_square-1];
					}
					leastRisky.push_back(1);
				}
			}
			if (current_x_square < NUM_HORIZONTAL_SQUARES - 1) {
				if (minRisk >= riskScores[current_x_square+1][current_y_square-1]) {
					if (minRisk > riskScores[current_x_square+1][current_y_square-1]) {
						leastRisky.clear();
						minRisk = riskScores[current_x_square+1][current_y_square-1];
					}
					leastRisky.push_back(3);
				}
			}
		}
		if (current_y_square < NUM_VERTICAL_SQUARES - 1) {
			if (minRisk >= riskScores[current_x_square][current_y_square+1]) {
				if (minRisk > riskScores[current_x_square][current_y_square+1]) {
					leastRisky.clear();
					minRisk = riskScores[current_x_square][current_y_square+1];
				}
				leastRisky.push_back(6);
			}
			if (current_x_square > 0) {
				if (minRisk >= riskScores[current_x_square-1][current_y_square+1]) {
					if (minRisk > riskScores[current_x_square-1][current_y_square+1]) {
						leastRisky.clear();
						minRisk = riskScores[current_x_square-1][current_y_square+1];
					}
					leastRisky.push_back(7);
				}
			}
			if (current_x_square < NUM_HORIZONTAL_SQUARES - 1) {
				if (minRisk >= riskScores[current_x_square+1][current_y_square+1]) {
					if (minRisk > riskScores[current_x_square+1][current_y_square+1]) {
						leastRisky.clear();
						minRisk = riskScores[current_x_square+1][current_y_square+1];
					}
					leastRisky.push_back(5);
				}
			}
		}
		if (current_x_square > 0) {
			if (minRisk >= riskScores[current_x_square-1][current_y_square]) {
				if (minRisk > riskScores[current_x_square-1][current_y_square]) {
					leastRisky.clear();
					minRisk = riskScores[current_x_square-1][current_y_square];
				}
				leastRisky.push_back(8);
			}
		}
		if (current_x_square > 0) {
			if (minRisk >= riskScores[current_x_square+1][current_y_square]) {
				if (minRisk > riskScores[current_x_square+1][current_y_square]) {
					leastRisky.clear();
					minRisk = riskScores[current_x_square+1][current_y_square];
				}
				leastRisky.push_back(4);
			}
		}
		// If the current movement direction is still in the least risky list, go in that direction
		for (int i = 0; i < leastRisky.size(); i++) {
			if (leastRisky[i] == prev_direction) return prev_direction;
		}
		// Otherwise pick a new direction at random from the list of safe directions
		int choice = rand() % leastRisky.size();
		return leastRisky[choice];
	}

	void Enemy::calculateRiskscores(int playerX, int playerY, std::vector<int> bulletX, std::vector<int> bulletY, std::vector<int> bulletVelX, std::vector<int> bulletVelY, int kamiX, int kamiY, std::vector<int> stalagmX, std::vector<int> stalagmH, std::vector<int> stalagtX, std::vector<int> stalagtH, std::vector<int> turretX, std::vector<int> turretH, std::vector<int> turretBottom) {
		for (int i = 0; i < NUM_HORIZONTAL_SQUARES; i++) {
			for (int j = 0; j < NUM_VERTICAL_SQUARES; j++) {
				riskScores[i][j] = 0;
			}
		}
		int xBlock;
		int yBlock;
		// Factor bullets into the risk score
		for (int i = 0; i < bulletX.size(); i++) {
			xBlock = (bulletX[i] - MIN_X) / SQUARE_WIDTH;
			yBlock = (bulletY[i] - MIN_Y) / SQUARE_WIDTH;
			if (bulletVelX[i] * (xPos - bulletX[i]) > 0 || bulletVelY[i] * (yPos - bulletY[i]) > 0) {
				if (yBlock >= 0 && yBlock < NUM_VERTICAL_SQUARES) {
					for (int j = 0; j < NUM_HORIZONTAL_SQUARES; j++) {
						riskScores[j][yBlock] += 60;
					}
				}
				if (xBlock >= 0 && xBlock < NUM_HORIZONTAL_SQUARES) {
					for (int j = 0; j < NUM_VERTICAL_SQUARES; j++) {
						riskScores[xBlock][j] += 60;
					}
				}
			}
		}

		// Factor stalactites, stalagmites, and turrets into the risk score
		// Basically, any block where there is/soon will be a stalactite or turret is dangerous
		int firstX;
		int lastX;
		int lastY;
		int numHorizSquares = NUM_HORIZONTAL_SQUARES;
		for (int i = 0; i < stalagmX.size(); i++) {
			firstX = std::max(0, (stalagmX[i] - 50) / SQUARE_WIDTH);
			lastX = std::min(numHorizSquares - 1, (stalagmX[i] + 150) / SQUARE_WIDTH);
			lastY = (stalagmH[i] - MIN_Y) / SQUARE_WIDTH;
			for (int j = firstX; j <= lastX; j++) {
				for (int k = 0; k <= lastY; k++) {
					riskScores[j][k] += 50;
				}
			}
		}
		for (int i = 0; i < stalagtX.size(); i++) {
			firstX = std::max(0, (stalagtX[i] - 50) / SQUARE_WIDTH);
			lastX = std::min(numHorizSquares - 1, (stalagtX[i] + 150) / SQUARE_WIDTH);
			lastY = (720 - stalagtH[i] - MIN_Y) / SQUARE_WIDTH;
			for (int j = firstX; j <= lastX; j++) {
				for (int k = NUM_VERTICAL_SQUARES - 1; k >= lastY; k--) {
					riskScores[j][k] += 50;
				}
			}
		}
		for (int i = 0; i < turretX.size(); i++) {
			firstX = std::max(0, (turretX[i] - 50) / SQUARE_WIDTH);
			lastX = std::min(numHorizSquares - 1, (turretX[i] + 150) / SQUARE_WIDTH);
			if (turretBottom[i] == 0) {
				lastY = (turretH[i] - MIN_Y) / SQUARE_WIDTH;
				for (int j = firstX; j <= lastX; j++) {
					for (int k = 0; k <= lastY; k++) {
						riskScores[j][k] += 50;
					}
				}
			}
			else {
				lastY = (720 - turretH[i] - MIN_Y) / SQUARE_WIDTH;
				for (int j = firstX; j <= lastX; j++) {
					for (int k = NUM_VERTICAL_SQUARES - 1; k >= lastY; k--) {
						riskScores[j][k] += 50;
					}
				}
			}
		}

		// Factor kamikazes into the risk score
		// std::cout << "kamis:" << kamiX.size() << std::endl;
		// for (int i = 0; i < kamiX.size(); i++) {
		// 	xBlock = (kamiX[i] - MIN_X) / SQUARE_WIDTH;
		// 	yBlock = (kamiY[i] - MIN_Y) / SQUARE_WIDTH;
		// 	if (yBlock >= 0 && yBlock < NUM_VERTICAL_SQUARES) {
		// 		for (int j = 0; j < NUM_HORIZONTAL_SQUARES; j++) {
		// 			riskScores[j][yBlock] += 10;
		// 		}
		// 	}
		// 	if (xBlock >= 0 && xBlock < NUM_HORIZONTAL_SQUARES) {
		// 		for (int j = 0; j < NUM_VERTICAL_SQUARES; j++) {
		// 			riskScores[xBlock][j] += 10;
		// 		}
		// 	}
		// }

		//New kamikaze risk score calculations
		xBlock = (kamiX - MIN_X)/SQUARE_WIDTH;
		yBlock = (kamiY - MIN_Y)/SQUARE_WIDTH;
		if (yBlock >= 0 && yBlock < NUM_VERTICAL_SQUARES) {
			for (int j = 0; j < NUM_HORIZONTAL_SQUARES; j++) {
				riskScores[j][yBlock] += 10;
			}
		}
		if (xBlock >= 0 && xBlock < NUM_HORIZONTAL_SQUARES) {
			for (int j = 0; j < NUM_VERTICAL_SQUARES; j++) {
				riskScores[xBlock][j] += 10;
			}
		}

		// Factor proximity to the edge of the screen into the risk score
		double center = ((MAX_Y - MIN_Y) / 2.0) / SQUARE_WIDTH - 0.5;
		for (int i = 0; i < NUM_HORIZONTAL_SQUARES; i++) {
			for (int j = 0; j < NUM_VERTICAL_SQUARES; j++) {
				riskScores[i][j] += (j - center) * (j - center) * SQUARE_WIDTH / 10.0;
			}
		}

		// Factor player into the risk score
		xBlock = (playerX - MIN_X) / SQUARE_WIDTH;
		yBlock = (playerY - MIN_Y) / SQUARE_WIDTH;
		if (yBlock >= 0 && yBlock < NUM_VERTICAL_SQUARES) {
			for (int j = 0; j < NUM_HORIZONTAL_SQUARES; j++) {
				riskScores[j][yBlock] -= 30;
			}
		}
		if (xBlock >= 0 && xBlock < NUM_HORIZONTAL_SQUARES) {
			for (int j = 0; j < NUM_VERTICAL_SQUARES; j++) {
				riskScores[xBlock][j] -= 30;
			}
		}
	}

	bool Enemy::checkCollision(int objX, int objY, int objW, int objH) {
		if (is_destroyed) return false;
		return checkCollide(objX, objY, objW, objH, xPos, yPos, width, height);
	}

	bool Enemy::checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight)
	{
	    if (x + pWidth < xTwo || x > xTwo + pTwoWidth)
	        return false;
	    if (y + pHeight < yTwo || y > yTwo + pTwoHeight)
	        return false;
	    return true;
	}

	void Enemy::hit(int d){
        Mix_PlayChannel(-1, hit_sound, 0);
		// If the player has just been hit, they should be invunerable, so don't damage them
		if ((SDL_GetTicks() - time_hit) <= FLICKER_TIME) {
			return;
		}

		time_hit = SDL_GetTicks();
		health -= d;
		if (health <= 0) {
			health = 0;
			time_destroyed = SDL_GetTicks();
			is_destroyed = true;
		}
	}

    int Enemy::getX(){
      return (int) xPos;
    }

    int Enemy::getY(){
      return (int) yPos;
    }

	int Enemy::getWidth() {
		return width;
	}

	int Enemy::getHeight() {
		return height;
	}

    void Enemy::setyVelo(int y){
      yVelo = y;
    }

    void Enemy::setxVelo(int x) {
      xVelo = x;
    }

    void Enemy::setPosX(int x) {
		xPos = x;
	}

	void Enemy::setPosY(int y) {
		yPos = y;
	}

	// Methods that can be used to undo the enemy's moves when dealing with collisions
	void Enemy::undoXMove() {
		xPos -= (double) (xVelo * time_since_move) / 1000;
	}
	void Enemy::undoYMove() {
		yPos -= (double) (yVelo * time_since_move) / 1000;
	}
	void Enemy::redoXMove() {
		xPos += (double) (xVelo * time_since_move) / 1000;
	}
	void Enemy::redoYMove() {
		yPos += (double) (yVelo * time_since_move) / 1000;
	}

    SDL_Rect* Enemy::getHitbox(){
      return &enemy_hitbox;
    }

    Bullet* Enemy::handleFiring()
    {
		if (!is_destroyed){
			time_since_shoot = SDL_GetTicks() - last_shot;
			if (time_since_shoot > FIRING_FREQ) {
				Bullet* b = new Bullet(xPos+width+5,yPos+height/2,450);
				last_shot = SDL_GetTicks();
				return b;
			}
		}
    	return nullptr;
    }

	int Enemy::getHealth(){
		return health;
	}
	
	void Enemy::moveLeft() {
		time_since_move = SDL_GetTicks() - last_move;
		xPos -= (double) (maxXVelo * time_since_move) / 1000;
		last_move = SDL_GetTicks();
	}
