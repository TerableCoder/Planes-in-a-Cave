#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"

SDL_Texture* Player::loadImage(std::string fname, SDL_Renderer *gRenderer) {
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

Player::Player(int xPos, int yPos, int diff, SDL_Renderer *gRenderer)
{
    x_pos = xPos;
    y_pos = yPos;
    x_vel = 0;
    y_vel = 0;
    x_accel = 0;
    y_accel = 0;
    initializeSprites(diff, gRenderer);
    bg_X = 0;
    tiltAngle = 0;
	last_move = SDL_GetTicks();
    moveUp = false;
    moveDown = false;
    moveForward = false;
    moveBackward = false;
	fshot_heat = 0;
	bshot_heat = 0;
	fshot_maxed = false;
	bshot_maxed = false;
	time_hit = SDL_GetTicks() - FLICKER_TIME;
    time_since_f_shot=SDL_GetTicks();
    time_since_b_shot=SDL_GetTicks();
	health = 100;
    difficulty = diff;
    infiniteShooting= false;
    invincePower = false;
    autoFire=false;
    small = false;
    bullet_shot = Mix_LoadWAV("sounds/pew.wav");
	hit_sound = Mix_LoadWAV("sounds/player_hit.wav");
}

Player::~Player()
{
	SDL_DestroyTexture(sprite1);
	SDL_DestroyTexture(sprite2);
	Mix_FreeChunk(bullet_shot);
	Mix_FreeChunk(hit_sound);
}

void Player::initializeSprites(int diff, SDL_Renderer *gRenderer)
{
    if (diff == 1)
    {
        sprite1 = loadImage("sprites/PlayerPlane1.png", gRenderer);
        sprite2 = loadImage("sprites/PlayerPlane3.png", gRenderer);

        player_height = PLAYER_HEIGHT;
        player_width = PLAYER_WIDTH;
    }
    else
    {
        int min = 1, max = 9;
        int random_sprite = rand() % (max - min + 1) + min;

        switch (random_sprite)
        {
            case 1:
                sprite1 = loadImage("sprites/a10.png", gRenderer);
                sprite2 = loadImage("sprites/a10.png", gRenderer);
                player_width = 178;
                player_height = 47;
                break;
            case 2:
                sprite1 = loadImage("sprites/f16.png", gRenderer);
                sprite2 = loadImage("sprites/f16a.png", gRenderer);
                player_width = 124;
                player_height = 37;
                break;
            case 3: 
                sprite1 = loadImage("sprites/f22.png", gRenderer);
                sprite2 = loadImage("sprites/f22.png", gRenderer);
                player_width = 164;
                player_height = 38;
                break;
            case 4:
                sprite1 = loadImage("sprites/f35.png", gRenderer);
                sprite2 = loadImage("sprites/f35.png", gRenderer);
                player_width = 125;
                player_height = 33;
                break;
            case 5:
                sprite1 = loadImage("sprites/f4.png", gRenderer);
                sprite2 = loadImage("sprites/f4.png", gRenderer);
                player_width = 152;
                player_height = 42;
                break;
            case 6:
                sprite1 = loadImage("sprites/mig21.png", gRenderer);
                sprite2 = loadImage("sprites/mig21.png", gRenderer);
                player_width = 155;
                player_height = 45;
                break;
            case 7:
                sprite1 = loadImage("sprites/mig21e.png", gRenderer);
                sprite2 = loadImage("sprites/mig21e.png", gRenderer);
                player_width = 155;
                player_height = 50;
                break;
            case 8:
                sprite1 = loadImage("sprites/mig31.png", gRenderer);
                sprite2 = loadImage("sprites/mig31a.png", gRenderer);
                player_width = 209;
                player_height = 38;
                break;
            case 9:
                sprite1 = loadImage("sprites/mig29.png", gRenderer);
                sprite2 = loadImage("sprites/mig29a.png", gRenderer);
                player_width = 148;
                player_height = 42;
                break;
            case 10:
                sprite1 = loadImage("sprites/su24.png", gRenderer);
                sprite2 = loadImage("sprites/su24a.png", gRenderer);
                player_width = 176;
                player_height = 50;
                break;
        }           
    }

    player_hurt_height = player_height * 0.8;
    player_hurt_width = player_width * 0.8;
    s_player_hurt_height = player_hurt_height / 1.5;
    s_player_hurt_width = player_hurt_width / 1.5;
}

void Player::handleMute()
{
    Mix_VolumeChunk(bullet_shot, abs(Mix_VolumeChunk(bullet_shot, -1) - 128));
}

//Takes key presses and adjusts the player's velocity
void Player::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_w:
            moveUp = true;
            break;

        case SDLK_a:
            moveBackward = true;
            break;

        case SDLK_s:
            moveDown = true;
            break;

        case SDLK_d:
            moveForward = true;
            break;
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_w:
            moveUp = false;
            break;

        case SDLK_a:
            moveBackward = false;
            break;

        case SDLK_s:
            moveDown = false;
            break;

        case SDLK_d:
            moveForward = false;
            break;
        }
    }
}

void Player::acceleration(bool &increasing, bool &decreasing, double &accel, double &accelerate_by, double &decelerate_factor, double &vel){
    if(!accel && decreasing && !increasing) accel = -1;
    if(!accel && !decreasing && increasing) accel = 1;
    if(increasing != decreasing && (decreasing && accel > 0 || increasing && accel < 0)) accelerate_by *= decelerate_factor; // manually change direction faster
    if(decreasing) accel -= accelerate_by;
    if(increasing) accel += accelerate_by;
    if(!decreasing && !increasing){ // automatically decelerate faster
        if(vel < 0) accel += decelerate_factor*accelerate_by;
        else if(vel > 0) accel -= decelerate_factor*accelerate_by;
        float vel_increment = accel*time_since_move;
        vel += vel_increment * 2;
        if(vel != 0 && vel <= fabs((int) (decelerate_factor*vel_increment)) && vel >= -fabs((int) (decelerate_factor*vel_increment))){
            accel = 0;
            vel = 0;
        }
    } else{ // normal movement
        float vel_increment = accel*time_since_move;
        vel += vel_increment * 2;
    }
    if(accel > 3) accel = 3;
    else if(accel < -3) accel = -3;
}

//Moves the player
void Player::move(int SCREEN_WIDTH, int SCREEN_HEIGHT, int LEVEL_HEIGHT, int camY)
{
    double accelerate_by = 0.003*time_since_move;
    double decelerate_factor = 4.0;
    acceleration(moveDown, moveUp, y_accel, accelerate_by, decelerate_factor, y_vel);
    double accelAngle = y_accel/6;
    if(!moveDown && !moveUp && y_vel > 0) tiltAngle = 90*sin(accelAngle) > 0 ? 90*sin(accelAngle) : 0;
    else if(!moveDown && !moveUp && y_vel < 0) tiltAngle = 90 * sin(accelAngle) < 0 ? 90 * sin(accelAngle) : 0;
    else tiltAngle = 90*sin(accelAngle);
    acceleration(moveForward, moveBackward, x_accel, accelerate_by, decelerate_factor, x_vel);

    if (y_vel > MAX_PLAYER_VEL)
        y_vel = MAX_PLAYER_VEL;
    else if (y_vel < -MAX_PLAYER_VEL)
        y_vel = -MAX_PLAYER_VEL;
    if (x_vel > MAX_PLAYER_VEL)
        x_vel = MAX_PLAYER_VEL;
    else if (x_vel < -MAX_PLAYER_VEL)
        x_vel = -MAX_PLAYER_VEL;

	time_since_move = SDL_GetTicks() - last_move;
	if(infiniteShooting && SDL_GetTicks()-time_since_inf>INFINITE_TIME){
        infiniteShooting=false;
    }
    if(invincePower && SDL_GetTicks()-time_since_invincible>INVINCE_TIME){
        invincePower=false;
    }
    if(autoFire && SDL_GetTicks()-time_since_auto>AUTOFIRE_TIME){
        autoFire=false;
    }
    if(small && SDL_GetTicks()-time_since_small>SMALL_TIME){
        small=false;
    }
	// Update heat of the front and back gun
	if (fshot_maxed && SDL_GetTicks() - fshot_max_time > COOLDOWN_TIME) {
		if(fshot_heat <= 0){
            fshot_heat = 0;
            fshot_maxed = false;
        }
        else{
            fshot_heat -= (SHOOT_COST / 10);
        }
	}
	if (!fshot_maxed) {
		fshot_heat -= time_since_move * RECOVERY_RATE;
		if (fshot_heat < 0) fshot_heat = 0;
	}
	if (bshot_maxed && SDL_GetTicks() - bshot_max_time > COOLDOWN_TIME) {
		if(bshot_heat <= 0){
            bshot_heat = 0;
            bshot_maxed = false;
        }
        else{
            bshot_heat -= (SHOOT_COST / 10);
        }
	}
	if (!bshot_maxed) {
		bshot_heat -= time_since_move * RECOVERY_RATE;
		if (bshot_heat < 0) bshot_heat = 0;
	}

    x_pos += (double) (x_vel * time_since_move) / 1000;
    y_pos += (double) (y_vel * time_since_move) / 1000;
    bg_X += (double) (time_since_move) / 10;

    // Move the player horizontally
    if(small == false){
        if (x_pos < 0)
        {
            x_pos = 0;
        }
        else if (x_pos > SCREEN_WIDTH - getWidth())
        {
           x_pos = SCREEN_WIDTH - getWidth();
        }
        // Stop the player if they hit the top of the level
        else if (y_pos < 0)
        {
          y_pos = 0;
        }
        // Stop the player if they hit the bottom
        else if (y_pos > SCREEN_HEIGHT - player_height)
        {
            y_pos = SCREEN_HEIGHT - player_height;
        }
    }
    else{
        if (x_pos < 0)
        {
            x_pos = 0;
        }
        else if (x_pos > SCREEN_WIDTH - getWidth())
        {
           x_pos = SCREEN_WIDTH - getWidth();
        }
        // Stop the player if they hit the top of the level
        else if (y_pos < 0)
        {
          y_pos = 0;
        }
        // Stop the player if they hit the bottom
        else if (y_pos > SCREEN_HEIGHT - player_height)
        {
            y_pos = SCREEN_HEIGHT - player_height;
        }
    }


    if (camY < 0)
    {
        camY = 0;
    }
    else if (camY > LEVEL_HEIGHT - SCREEN_HEIGHT)
    {
        camY = LEVEL_HEIGHT - SCREEN_HEIGHT;
    }
	last_move = SDL_GetTicks();
}

//Shows the player on the screen relative to the camera
void Player::render(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	// Don't render the player if they're flickering after being hit
	if ((SDL_GetTicks() - time_hit) <= FLICKER_TIME && ((SDL_GetTicks() - time_hit) / FLICKER_FREQ) % 2 == 0) {
		return;
	}
    if(small == false){
        SDL_Rect playerLocation = {(int) x_pos, (int) y_pos, getWidth(), getHeight()};
	    // Alternates through the two sprites every ANIMATION_FREQ ticks
        if ((SDL_GetTicks() / ANIMATION_FREQ) % 2 == 1) {
	    	SDL_RenderCopyEx(gRenderer, sprite1, nullptr, &playerLocation, tiltAngle, nullptr, SDL_FLIP_NONE);
	    }
	    else {
	    	SDL_RenderCopyEx(gRenderer, sprite2, nullptr, &playerLocation, tiltAngle, nullptr, SDL_FLIP_NONE);
	    }
    }
    else{
        SDL_Rect playerLocation = {(int) x_pos, (int) y_pos, getWidth(), getHeight()};
	    // Alternates through the two sprites every ANIMATION_FREQ ticks
        if ((SDL_GetTicks() / ANIMATION_FREQ) % 2 == 1) {
	    	SDL_RenderCopyEx(gRenderer, sprite1, nullptr, &playerLocation, tiltAngle, nullptr, SDL_FLIP_NONE);
	    }
	    else {
	    	SDL_RenderCopyEx(gRenderer, sprite2, nullptr, &playerLocation, tiltAngle, nullptr, SDL_FLIP_NONE);
	    }
    }
    
}

// Damages the player if they've been hit
void Player::hit(int damage) {
	// If the player has just been hit, they should be invunerable, so don't damage them
	if(!invincePower && health > 0){
        Mix_PlayChannel(-1, hit_sound, 0);
        if(this->difficulty == 2){
            damage /= 1.5;
        }
        else if(this->difficulty == 1){
            damage /= 2;
        }
        if ((SDL_GetTicks() - time_hit) <= FLICKER_TIME) {
		    return;
	    }
	    time_hit = SDL_GetTicks();
	    health -= damage;
	    if (health < 0) {
	    	health = 0;
    	}
    }
}

void Player::heal(int amount) {
    health += amount;
    if (health > 100) {
        health = 100;
    }
}

void Player::setInfiniteVal(bool val){
    infiniteShooting=val;
    time_since_inf=SDL_GetTicks();
}

void Player::setInvinceVal(bool val){
    invincePower=val;
    time_since_invincible=SDL_GetTicks();
}

void Player::setAutoFire(bool val){
    autoFire=val;
    time_since_auto=SDL_GetTicks();
}

void Player::setSmall(bool val){
    small=val;
    time_since_small=SDL_GetTicks();
}

void Player::resetHeatVals(){
    bshot_heat = 0;
    fshot_heat=0;
    bshot_maxed = false;
    fshot_maxed = false;
}

// Checks if the player collided with a kamikaze, returning true if so
bool Player::checkCollisionKami(int kamiX, int kamiY, int kamiW, int kamiH) {
    if(small == false){
        return checkCollide(kamiX, kamiY, kamiW, kamiH, x_pos + 12, y_pos - 12, player_hurt_width, player_hurt_height);
    }
    else{
        return checkCollide(kamiX, kamiY, kamiW, kamiH, x_pos + 8, y_pos - 8, s_player_hurt_width, s_player_hurt_height);
    }
}

// Checks if the player collided with a bullet, returning true if so
bool Player::checkCollisionBullet(int bullX, int bullY, int bullW, int bullH) {
    if(small == false){
        return checkCollide(bullX, bullY, bullW, bullH, x_pos + 12, y_pos + 12, player_hurt_width, player_hurt_height);
    }
    else{
        return checkCollide(bullX, bullY, bullW, bullH, x_pos + 9, y_pos + 9, s_player_hurt_width, s_player_hurt_height);
    }	
}

bool Player::checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight)
{
    if (x + pWidth < xTwo || x > xTwo + pTwoWidth)
        return false;
    if (y + pHeight < yTwo || y > yTwo + pTwoHeight)
        return false;
    return true;
}

Bullet* Player::handleForwardFiring()
{
	if (!fshot_maxed && (SDL_GetTicks()- time_since_f_shot) >= 100) {
		Bullet* b = new Bullet(x_pos+PLAYER_WIDTH+5 -fabs(PLAYER_WIDTH/8*sin(tiltAngle)), y_pos+PLAYER_HEIGHT/2+PLAYER_HEIGHT*sin(tiltAngle), fabs(450*cos(tiltAngle)), tiltAngle >= 0 ? fabs(450*sin(tiltAngle)) : -fabs(450*sin(tiltAngle)));
    }
    if(!infiniteShooting || !autoFire){
    //std::cout << "entered firing handler" << std::endl;
    //std::cout << "time since f shot = " << SDL_GetTicks()- time_since_f_shot << std::endl;
    double bulletAngle = tiltAngle*PI/180;
        if (!fshot_maxed && (SDL_GetTicks()- time_since_f_shot) >= 100) {
                //std::cout << "Firing new bullet"<< std::endl;
            Mix_PlayChannel(-1, bullet_shot, 0);

            Bullet *b;
            if(small == false){
                b = new Bullet(x_pos+getWidth()+5 -fabs(getWidth()/8*sin(bulletAngle)), y_pos+player_height/2+player_height*sin(bulletAngle), fabs(450*cos(bulletAngle)), bulletAngle >= 0 ? fabs(450*sin(bulletAngle)) : -fabs(450*sin(bulletAngle)));
            }
            else{
                b = new Bullet(x_pos+getWidth()+5 -fabs(getWidth()/8*sin(bulletAngle)), y_pos+player_height/2+player_height*sin(bulletAngle), fabs(450*cos(bulletAngle)), bulletAngle >= 0 ? fabs(450*sin(bulletAngle)) : -fabs(450*sin(bulletAngle)));
            }
            if(!infiniteShooting){
        		fshot_heat += SHOOT_COST;
        		if (fshot_heat > MAX_SHOOT_HEAT) {
        			fshot_maxed = true;
        			fshot_heat = MAX_SHOOT_HEAT;
        			fshot_max_time = SDL_GetTicks();
        		}
            }
            time_since_f_shot = SDL_GetTicks();
    		return b;
        }
    }
    return nullptr;
}

Bullet* Player::handleBackwardFiring()
{
    double bulletAngle = tiltAngle*PI/180;
	if (!bshot_maxed && (SDL_GetTicks() - time_since_b_shot) >=100) {
        Mix_PlayChannel(-1, bullet_shot, 0);

        Bullet* b;
		if(small == false){
            b = new Bullet(x_pos-10 +fabs(getWidth()/8*sin(bulletAngle)), y_pos+player_height/2-player_height*sin(bulletAngle), -fabs(450*cos(bulletAngle)), bulletAngle >= 0 ? -fabs(450*sin(bulletAngle)) : fabs(450*sin(bulletAngle)));
        }
        else{
            b = new Bullet(x_pos-10 +fabs(getWidth()/8*sin(bulletAngle)), y_pos+player_height/2-player_height*sin(bulletAngle), -fabs(450*cos(bulletAngle)), bulletAngle >= 0 ? -fabs(450*sin(bulletAngle)) : fabs(450*sin(bulletAngle)));
        }
		if(!infiniteShooting){
            bshot_heat += SHOOT_COST;
            if (bshot_heat > MAX_SHOOT_HEAT) {
                bshot_maxed = true;
                bshot_heat = MAX_SHOOT_HEAT;
                bshot_max_time = SDL_GetTicks();
            }
        }
        time_since_b_shot = SDL_GetTicks();
		return b;
	}
	return nullptr;
}


//Position and velocity accessors
int Player::getPosX() { return x_pos; };
int Player::getPosY() { return y_pos; };
void Player::setVelX(int vel_x) { x_vel = vel_x; };
void Player::setVelY(int vel_y) { y_vel = vel_y; };
int Player::getVelX() { return x_vel; };
int Player::getVelY() { return y_vel; };
void Player::setPosX(int x) { x_pos = x; }
void Player::setPosY(int y) { y_pos = y; }

int Player::getWidth() { 
    if(small == false){
        return player_width; 
    }
    else{
        return player_width / 1.5;
    }
}

int Player::getHeight() { 
    if(small == false){
        return player_height; 
    }
    else{
        return player_height / 1.5; 
    }
}
 
int Player::getHitboxX() {
	if (small) return x_pos + 9;
	else return x_pos + 12;
}

int Player::getHitboxY() {
	if (small) return y_pos + 9;
	else return y_pos + 12;
};

int Player::getHurtWidth() { 
    if(small == false){
        return player_hurt_width; 
    }
    else{
        return s_player_hurt_width;
    }
}

int Player::getHurtHeight() { 
    if(small == false){
        return player_hurt_height; 
    }
    else{
        return s_player_hurt_height; 
    }
}

int Player::getHealth() { return health; };
int Player::getFrontHeat() { return fshot_heat; }
int Player::getBackHeat() { return bshot_heat; }
void Player::setHealthMax() { health = 100; }
bool Player::getAutoFire(){ return autoFire;}
bool Player::getSmall(){ return small;}

// Methods that can be used to undo the user's moves when dealing with collisions
void Player::undoXMove() {x_pos -= (double) (x_vel * time_since_move) / 1000;}
void Player::undoYMove() {y_pos -= (double) (y_vel * time_since_move) / 1000;}
void Player::redoXMove() {x_pos += (double) (x_vel * time_since_move) / 1000;}
void Player::redoYMove() {y_pos += (double) (y_vel * time_since_move) / 1000;}
