#include <SDL.h>
#include "Player.h"
#include "MapBlocks.h"
#include "missile.h"
#include "iostream"
#include <vector>

SDL_Texture* loadImage(std::string fname, SDL_Renderer *gRenderer) {
	SDL_Texture* newText = nullptr;

	SDL_Surface* startSurf = IMG_Load(fname.c_str());
    if(gRenderer == nullptr){
        return nullptr;
    }
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

WallBlock::WallBlock(){};
WallBlock::WallBlock(int num){
    CEILING_ABS_X = num * block_side;
    FLOOR_ABS_X = num * block_side;
    CEILING_ABS_Y = 0;
    FLOOR_ABS_Y = 720 - WallBlock::block_side;
    CEILING_REL_X = CEILING_ABS_X;
    FLOOR_REL_X = FLOOR_ABS_X;
    CEILING_REL_Y = CEILING_ABS_Y;
    FLOOR_REL_Y = FLOOR_ABS_Y;
}
HealthBlock::HealthBlock(){
    HEALTH_HEIGHT=20;
    HEALTH_WIDTH=20;
}
HealthBlock::HealthBlock(int LEVEL_WIDTH,int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength){
    HEALTH_HEIGHT=20;
    HEALTH_WIDTH=20;
    HEALTH_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    HEALTH_ABS_Y= LEVEL_HEIGHT-600+rand()%500;

    while ((HEALTH_ABS_X - 1280) % cave_freq <= cave_width || (HEALTH_ABS_X>(openAir*72) && HEALTH_ABS_X+HEALTH_WIDTH<(openAir+openAirLength)*72)) {
        HEALTH_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    }

    HEALTH_REL_X=HEALTH_ABS_X;
    HEALTH_REL_Y=HEALTH_ABS_Y;
}

InfFireBlock::InfFireBlock(){
    INF_FIRE_HEIGHT=35;
    INF_FIRE_WIDTH=35;
}
InfFireBlock::InfFireBlock(int LEVEL_WIDTH,int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength){
    INF_FIRE_HEIGHT=35;
    INF_FIRE_WIDTH=35;
    INF_FIRE_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    INF_FIRE_ABS_Y= LEVEL_HEIGHT-600+rand()%500;

    while ((INF_FIRE_ABS_X - 1280) % cave_freq <= cave_width || (INF_FIRE_ABS_X>(openAir*72) && INF_FIRE_ABS_X+INF_FIRE_WIDTH<(openAir+openAirLength)*72)) {
        INF_FIRE_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    }

    INF_FIRE_REL_X=INF_FIRE_ABS_X;
    INF_FIRE_REL_Y=INF_FIRE_ABS_Y;
}

AllyPlaneBlock::AllyPlaneBlock(){
    ALLY_PLANE_HEIGHT = 35;
    ALLY_PLANE_WIDTH = 35;
}


AllyPlaneBlock::AllyPlaneBlock(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength)
{
    ALLY_PLANE_HEIGHT = 35;
    ALLY_PLANE_WIDTH = 35;

    ALLY_PLANE_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    ALLY_PLANE_ABS_Y = LEVEL_HEIGHT - 600 + rand() % 500;

    while ((ALLY_PLANE_ABS_X - 1280) % cave_freq <= cave_width || (ALLY_PLANE_ABS_X>(openAir*72) && ALLY_PLANE_ABS_X+ALLY_PLANE_WIDTH<(openAir+openAirLength)*72)) {
        ALLY_PLANE_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    }

    ALLY_PLANE_REL_X=ALLY_PLANE_ABS_X;
    ALLY_PLANE_REL_Y=ALLY_PLANE_ABS_Y;
}

AutoFireBlock::AutoFireBlock(){
    AUTOFIRE_HEIGHT=35;
    AUTOFIRE_WIDTH=35;
}
AutoFireBlock::AutoFireBlock(int LEVEL_WIDTH,int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength){
    AUTOFIRE_HEIGHT=35;
    AUTOFIRE_WIDTH=35;
    AUTOFIRE_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    AUTOFIRE_ABS_Y= LEVEL_HEIGHT-600+rand()%500;

    while ((AUTOFIRE_ABS_X - 1280) % cave_freq <= cave_width || (AUTOFIRE_ABS_X>(openAir*72) && AUTOFIRE_ABS_X+AUTOFIRE_WIDTH<(openAir+openAirLength)*72)) {
        AUTOFIRE_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    }

    AUTOFIRE_REL_X=AUTOFIRE_ABS_X;
    AUTOFIRE_REL_Y=AUTOFIRE_ABS_Y;
}

InvincBlock::InvincBlock(){
    INVINCE_HEIGHT=35;
    INVINCE_WIDTH=35;
}
InvincBlock::InvincBlock(int LEVEL_WIDTH,int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength){
    INVINCE_HEIGHT=35;
    INVINCE_WIDTH=35;
    INVINCE_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    INVINCE_ABS_Y= LEVEL_HEIGHT-600+rand()%500;

    while ((INVINCE_ABS_X - 1280) % cave_freq <= cave_width || (INVINCE_ABS_X>(openAir*72) && INVINCE_ABS_X+INVINCE_WIDTH<(openAir+openAirLength)*72)) {
        INVINCE_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    }

    INVINCE_REL_X=INVINCE_ABS_X;
    INVINCE_REL_Y=INVINCE_ABS_Y;
}

SmallBlock::SmallBlock(){
    SMALL_HEIGHT=35;
    SMALL_WIDTH=35;
}
SmallBlock::SmallBlock(int LEVEL_WIDTH,int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength){
    SMALL_HEIGHT=35;
    SMALL_WIDTH=35;
    SMALL_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    SMALL_ABS_Y= LEVEL_HEIGHT-600+rand()%500;

    while ((SMALL_ABS_X - 1280) % cave_freq <= cave_width || (SMALL_ABS_X>(openAir*72) && SMALL_ABS_X+SMALL_WIDTH<(openAir+openAirLength)*72)) {
        SMALL_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    }

    SMALL_REL_X=SMALL_ABS_X;
    SMALL_REL_Y=SMALL_ABS_Y;
}

Stalagmite::Stalagmite()
{
    SDL_Renderer *gRenderer= nullptr;
    Stalagmite(1,1,gRenderer, 5500, 2000, 0, 0);
}
Stalagmite::Stalagmite(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength)
{
    STALAG_WIDTH = rand() % 16 + 60;
    STALAG_HEIGHT = rand() % 141 + 50;
    hitboxWidth = STALAG_WIDTH / 2;

    STALAG_ABS_X = (rand() * 10) % LEVEL_WIDTH;
    STALAG_ABS_Y = LEVEL_HEIGHT - WallBlock::block_side - STALAG_HEIGHT;//growing from bottom of cave
	// Select a new x coordinate if the current one is in a cave or open air section
	while ((STALAG_ABS_X - 1280) % cave_freq <= cave_width || (STALAG_ABS_X>(openAir*72) && STALAG_ABS_X+STALAG_WIDTH<(openAir+openAirLength)*72)) {
		STALAG_ABS_X = (rand() * 10) % LEVEL_WIDTH;
	}
    //STALAG_ABS_Y= rand() % LEVEL_HEIGHT;

    STALAG_REL_X = STALAG_ABS_X;
    STALAG_REL_Y = STALAG_ABS_Y;
    alreadyExploded = 0;

    stalagShapeNum = rand() % 4 + 1;
}

Stalagtite::Stalagtite()
{
    SDL_Renderer *gRenderer= nullptr;
    Stalagtite(1,1,gRenderer, 5500, 2000, 0, 0);
}
Stalagtite::Stalagtite(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength)
{
    STALAG_WIDTH = rand() % 16 + 60;
    STALAG_HEIGHT = rand() % 141 + 50;
    hitboxWidth = STALAG_WIDTH / 2;

    STALAG_ABS_X = (rand() * 10) % LEVEL_WIDTH;

    STALAG_ABS_Y = LEVEL_HEIGHT - 720 + WallBlock::block_side;//growing from top of cave
	// Select a new x coordinate if the current one is in a cave or open air section
	while ((STALAG_ABS_X - 1280) % cave_freq <= cave_width || (STALAG_ABS_X>(openAir*72) && STALAG_ABS_X+STALAG_WIDTH<(openAir+openAirLength)*72)) {
		STALAG_ABS_X = (rand() * 10) % LEVEL_WIDTH;
	}
    //STALAG_ABS_Y= rand() % LEVEL_HEIGHT;

    STALAG_REL_X = STALAG_ABS_X;
    STALAG_REL_Y = STALAG_ABS_Y;

    stalagShapeNum = rand() % 4 + 1;

    beenShot = 0;
    acceleration = 0;
}

Turret::Turret()
{
    SDL_Renderer *gRenderer= nullptr;
    SDL_Texture *tex1 = nullptr;
    SDL_Texture *tex2 = nullptr;
    Turret(1, 1, gRenderer, 5500, 2000, 0, 0, tex1, tex2);
}

Turret::Turret(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength, SDL_Texture* mSprite1, SDL_Texture* mSprite2) :
    gRenderer{ gRenderer }
{
    BLOCK_ABS_X = (rand() * 10) % LEVEL_WIDTH;
	BLOCK_ABS_Y = LEVEL_HEIGHT - WallBlock::block_side - Turret::BLOCK_HEIGHT;

	if (rand() % 2 == 1) {
		BLOCK_ABS_Y = LEVEL_HEIGHT - 720 + WallBlock::block_side;
	}
	while ((BLOCK_ABS_X - 1280) % cave_freq <= cave_width || (BLOCK_ABS_X>(openAir*72) && BLOCK_ABS_X+BLOCK_WIDTH<(openAir+openAirLength)*72 && BLOCK_ABS_Y==LEVEL_HEIGHT -720 + WallBlock::block_side)) {
		BLOCK_ABS_X = (rand() * 10) % LEVEL_WIDTH;
	}

    // These should be the same first
    BLOCK_REL_X = BLOCK_ABS_X;
    BLOCK_REL_Y = BLOCK_ABS_Y;

    // BLOCK_WIDTH = 25 + (rand() % 100);
    // BLOCK_HEIGHT = 25 + (rand() % 100);
    //Standard Enemy plane size
    BLOCK_WIDTH = 50;
    BLOCK_HEIGHT = 50;
    missileSprite1 = mSprite1;
    missileSprite2 = mSprite2;

    // Select the ceiling or floor turret sprite
	bottom = 0;
    if(BLOCK_ABS_Y == LEVEL_HEIGHT - WallBlock::block_side - Turret::BLOCK_HEIGHT){
        bottom = 1;
    }

    FB_sprite = { BLOCK_ABS_X,  BLOCK_ABS_Y, BLOCK_WIDTH, BLOCK_HEIGHT};
    FB_hitbox = FB_sprite;

	last_move = SDL_GetTicks();
}

int Turret::getRelX() { return BLOCK_REL_X; }
int Turret::getRelY() { return BLOCK_REL_Y; }
int Turret::getAbsX() { return BLOCK_ABS_X; }
int Turret::getAbsY() { return BLOCK_ABS_Y; }

Missile * Turret::handleFiring(int posX, int posY) {
    int damage = 500;
    int blast_radius = 150;

	time_since_move = SDL_GetTicks() - last_move;
	Missile * m = nullptr;
	if (time_since_move >= SHOOT_FREQ) {
		last_move = SDL_GetTicks();
		int xDist = posX - BLOCK_REL_X;
		int yDist = posY - BLOCK_REL_Y;
		double math = (double)xDist / sqrt(xDist * xDist + yDist * yDist) * 400;
		double math2 = ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400;
		if (BLOCK_REL_Y >= posY){
            int missType = rand()%5;//1 in 5 chance of missile being red
            if(missType < 4){
		        m = new Missile(damage, blast_radius, BLOCK_REL_X + BLOCK_WIDTH / 2, BLOCK_REL_Y - 20, ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, missileSprite1, gRenderer);
	        }
	        else{
                m = new Missile(damage, blast_radius, BLOCK_REL_X + BLOCK_WIDTH / 2, BLOCK_REL_Y - 20, ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, missileSprite2, gRenderer);
	        }
		}
		else {
            int missType = rand()%5;//1 in 5 chance of missile being red
	        SDL_Texture* missSprite;
            if(missType < 4){
		        m = new Missile(damage, blast_radius, BLOCK_REL_X + BLOCK_WIDTH / 2, BLOCK_REL_Y + 5 + BLOCK_HEIGHT, ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, missileSprite1, gRenderer);
	        }
	        else{
		        m = new Missile(damage, blast_radius, BLOCK_REL_X + BLOCK_WIDTH / 2, BLOCK_REL_Y + 5 + BLOCK_HEIGHT, ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, missileSprite2, gRenderer);
	        }
		}
	}
	return m;
}

Explosion::Explosion()
{
    SDL_Renderer *gRenderer= nullptr;
    Explosion(1, 1, 0, gRenderer);
}

Explosion::Explosion(int x_loc, int y_loc, int t, SDL_Renderer *gRenderer)
{
	// Initialize all necessary variables
	initial_explosion_size = 30;
	current_size = 30;
	final_explosion_size = 100;
	explosion_speed = 100;
	center_x = x_loc;
	center_y = y_loc;
	abs_x = center_x - current_size / 2;
	abs_y = center_y - current_size / 2;
	explosion_time = SDL_GetTicks();
    type = t;
	stationary = false;			// Explosion should move with the camera
}

Explosion::Explosion(int x, int y, int size) {
	initial_explosion_size = size / 5;
	current_size = size / 5;
	final_explosion_size = size;
	explosion_speed = size;
	center_x = x;
	center_y = y;
	abs_x = center_x - current_size / 2;
	abs_y = center_y - current_size / 2;
	explosion_time = SDL_GetTicks();
    type = 0;
	stationary = true;			// Boss explosion shouldn't move over time
}

MapBlocks::MapBlocks()
{
    gRenderer= nullptr;
    MapBlocks(1, 1, gRenderer = nullptr, 5500, 2000, 0,0, 1);
}

MapBlocks::MapBlocks(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gr, int cave_freq, int cave_width, int openAir, int openAirLength, int diff)
{
	gRenderer = gr;
	explosionSprite = loadImage("sprites/Explosion.png", gRenderer);
    dustCloudSprite = loadImage("sprites/dustCloud.png", gRenderer);
	topTurretSprite = loadImage("sprites/topturret.png", gRenderer);
	bottomTurretSprite = loadImage("sprites/bottomturret.png", gRenderer);
	stalactiteSprite1 = loadImage("sprites/stalagt1.png", gRenderer);
	stalactiteSprite2 = loadImage("sprites/stalagt2.png", gRenderer);
	stalactiteSprite3 = loadImage("sprites/stalagt3.png", gRenderer);
	stalactiteSprite4 = loadImage("sprites/stalagt4.png", gRenderer);
	stalagmiteSprite1 = loadImage("sprites/stalagm1.png", gRenderer);
	stalagmiteSprite2 = loadImage("sprites/stalagm2.png", gRenderer);
	stalagmiteSprite3 = loadImage("sprites/stalagm3.png", gRenderer);
	stalagmiteSprite4 = loadImage("sprites/stalagm4.png", gRenderer);
    healthSprite=loadImage("sprites/health.png", gRenderer);
    mSprite1=loadImage("sprites/missile.png", gRenderer);
    mSprite2=loadImage("sprites/missile2.png", gRenderer);
    infFireSprite=loadImage("sprites/infFire.png", gRenderer);
    invinceSprite=loadImage("sprites/invince.png", gRenderer);
    autofireSprite=loadImage("sprites/autofire.png", gRenderer);
    smallSprite=loadImage("sprites/small.png", gRenderer);
    allySprite=loadImage("sprites/plus_ally_ai.png", gRenderer);
	
	explosion_sound = Mix_LoadWAV("sounds/explosion.wav");


    if(diff == 3){
        BLOCKS_N = LEVEL_WIDTH/2000;
        HEALTH_N = LEVEL_WIDTH/5000;
        INF_FIRE_N = LEVEL_WIDTH/20000;
        INVINCE_N = LEVEL_WIDTH/20000;
        AUTOFIRE_N=LEVEL_WIDTH/30000;
        SMALL_N = LEVEL_WIDTH/10000;
        ALLY_N = LEVEL_WIDTH/3000;
    }
    else if (diff == 2){
        BLOCKS_N = LEVEL_WIDTH/2500;
        HEALTH_N = LEVEL_WIDTH/3300;
        INF_FIRE_N = LEVEL_WIDTH/10000;
        INVINCE_N = LEVEL_WIDTH/15000;
        AUTOFIRE_N = LEVEL_WIDTH/20000;
        SMALL_N = LEVEL_WIDTH/8000;
        ALLY_N = LEVEL_WIDTH/3000;
    }
    else{
        BLOCKS_N = LEVEL_WIDTH/5000;
        HEALTH_N = LEVEL_WIDTH/2500;
        INF_FIRE_N = LEVEL_WIDTH/7000;
        INVINCE_N = LEVEL_WIDTH/10000;
        AUTOFIRE_N = LEVEL_WIDTH/10000;
        SMALL_N = LEVEL_WIDTH/6700;
        ALLY_N = LEVEL_WIDTH/3000;    }

	CEILING_N = LEVEL_WIDTH / WallBlock::block_side;

    int i;
    for(i = 0; i<CEILING_N; i++){
        // Create blocks on the top of the screen if it isn't an open air section
		if(!(i>openAir && i<openAir+openAirLength && openAir+openAirLength<CEILING_N)){
			ceiling_arr.push_back(WallBlock(i));
        }
		// Create blocks on the bottom of the screen
        floor_arr.push_back(WallBlock(i));
    }

    for (i = 0; i < BLOCKS_N; i++)
    {
        blocks_arr.push_back(Turret(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength, mSprite1, mSprite2)); // Initiating each Turret
    }

    for (i=0; i < HEALTH_N; i++)
    {
        health_arr.push_back(HealthBlock(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength));//Initiate the healthblocks
    }

    for (i=0; i < INF_FIRE_N; i++)
    {
        infFire_arr.push_back(InfFireBlock(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength));//Initiate the shooting powerup
    }

    for (i=0; i < INVINCE_N; i++)
    {
        invince_arr.push_back(InvincBlock(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength));//Initiate the invincibility
    }

    for (i=0; i < AUTOFIRE_N; i++)
    {
        autofire_arr.push_back(AutoFireBlock(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength));//Initiate the shooting powerup
    }

    for (i=0; i < SMALL_N; i++)
    {
        small_arr.push_back(SmallBlock(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength));//Initiate the small powerup
    }

    for (i=0; i < STALAG_N; i++)
    {
        stalagm_arr.push_back(Stalagmite(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength));//Initiate the stalagmites
    }
    for (i=0; i < STALAG_N; i++)
    {
        stalagt_arr.push_back(Stalagtite(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength));//Initiate the stalagtites
    }
    for(i = 0; i < ALLY_N; i++)
    {
        ally_arr.push_back(AllyPlaneBlock(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength));
    }
}

MapBlocks::~MapBlocks()
{
	SDL_DestroyTexture(explosionSprite);
	SDL_DestroyTexture(dustCloudSprite);
	SDL_DestroyTexture(topTurretSprite);
	SDL_DestroyTexture(bottomTurretSprite);
	SDL_DestroyTexture(stalactiteSprite1);
	SDL_DestroyTexture(stalactiteSprite2);
	SDL_DestroyTexture(stalactiteSprite3);
	SDL_DestroyTexture(stalactiteSprite4);
	SDL_DestroyTexture(stalagmiteSprite1);
	SDL_DestroyTexture(stalagmiteSprite2);
	SDL_DestroyTexture(stalagmiteSprite3);
	SDL_DestroyTexture(stalagmiteSprite4);
	SDL_DestroyTexture(healthSprite);
	SDL_DestroyTexture(mSprite1);
	SDL_DestroyTexture(mSprite2);
    SDL_DestroyTexture(infFireSprite);
    SDL_DestroyTexture(invinceSprite);
    SDL_DestroyTexture(autofireSprite);
    SDL_DestroyTexture(smallSprite);
    SDL_DestroyTexture(allySprite);
	Mix_FreeChunk(explosion_sound);
}

bool MapBlocks::checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight)
{
    if (x + pWidth < xTwo || x > xTwo + pTwoWidth)
        return false;
    if (y + pHeight < yTwo || y > yTwo + pTwoHeight)
        return false;
    return true;
}

void MapBlocks::moveBlocks(int camX, int camY)
{
    int i;
    for (i = 0; i < blocks_arr.size(); i++)
    {
        blocks_arr[i].BLOCK_REL_X = blocks_arr[i].BLOCK_ABS_X - camX;
        blocks_arr[i].BLOCK_REL_Y = blocks_arr[i].BLOCK_ABS_Y - camY;
	}
    //ceiling and floor
    for(i = 0; i < ceiling_arr.size(); i++)
    {
        ceiling_arr[i].CEILING_REL_X = ceiling_arr[i].CEILING_ABS_X - camX;
	}
    for(i = 0; i < floor_arr.size(); i++)
	{
        floor_arr[i].FLOOR_REL_X = floor_arr[i].FLOOR_ABS_X - camX;
    }

    for (i = 0; i < health_arr.size(); i++)
    {
        health_arr[i].HEALTH_REL_X = health_arr[i].HEALTH_ABS_X - camX;
        health_arr[i].HEALTH_REL_Y = health_arr[i].HEALTH_ABS_Y-camY;
    }

    for (i = 0; i < infFire_arr.size(); i++)
    {
        infFire_arr[i].INF_FIRE_REL_X = infFire_arr[i].INF_FIRE_ABS_X - camX;
        infFire_arr[i].INF_FIRE_REL_Y = infFire_arr[i].INF_FIRE_ABS_Y-camY;
    }

    for (i = 0; i < invince_arr.size(); i++)
    {
        invince_arr[i].INVINCE_REL_X = invince_arr[i].INVINCE_ABS_X - camX;
        invince_arr[i].INVINCE_REL_Y = invince_arr[i].INVINCE_ABS_Y-camY;
    }
    for (i = 0; i < autofire_arr.size(); i++)
    {
        autofire_arr[i].AUTOFIRE_REL_X = autofire_arr[i].AUTOFIRE_ABS_X - camX;
        autofire_arr[i].AUTOFIRE_REL_Y = autofire_arr[i].AUTOFIRE_ABS_Y-camY;
    }

    for (i = 0; i < small_arr.size(); i++)
    {
        small_arr[i].SMALL_REL_X = small_arr[i].SMALL_ABS_X - camX;
        small_arr[i].SMALL_REL_Y = small_arr[i].SMALL_ABS_Y-camY;
    }

    for (i = 0; i < stalagm_arr.size(); i++)
    {
        stalagm_arr[i].STALAG_REL_X = stalagm_arr[i].STALAG_ABS_X - camX;
        stalagm_arr[i].STALAG_REL_Y = stalagm_arr[i].STALAG_ABS_Y-camY;
    }
    for(i = 0; i < ally_arr.size(); i++)
    {
        ally_arr[i].ALLY_PLANE_REL_X = ally_arr[i].ALLY_PLANE_ABS_X - camX;
        ally_arr[i].ALLY_PLANE_REL_Y = ally_arr[i].ALLY_PLANE_ABS_Y - camY;
    }
    for (i = 0; i < stalagt_arr.size(); i++)
    {
        stalagt_arr[i].STALAG_REL_X = stalagt_arr[i].STALAG_ABS_X - camX;
		stalagt_arr[i].STALAG_REL_Y = stalagt_arr[i].STALAG_ABS_Y - camY;
        if(stalagt_arr[i].beenShot == 1){
            stalagt_arr[i].time_since_move = SDL_GetTicks() - stalagt_arr[i].last_move;
            if(stalagt_arr[i].STALAG_REL_Y <  stalagt_arr[i].terminalVelocityYValue){
                stalagt_arr[i].acceleration += 0.008 * stalagt_arr[i].time_since_move;
            }
            stalagt_arr[i].STALAG_ABS_Y += stalagt_arr[i].acceleration; // maybe make it fall until it reaches halfway down instead when the tip collides
            stalagt_arr[i].last_move = SDL_GetTicks();
        }
        // stalagt_arr[i].STALAG_REL_Y = stalagt_arr[i].STALAG_ABS_Y-camY - WallBlock::block_side - stalagt_arr[i].STALAG_HEIGHT;
    }
	for (i = explosion_arr.size() - 1; i >= 0; i--)
	{
		explosion_arr[i].current_size = (double) explosion_arr[i].initial_explosion_size + ((SDL_GetTicks() - explosion_arr[i].explosion_time) * explosion_arr[i].explosion_speed) / 1000;
		explosion_arr[i].abs_x = explosion_arr[i].center_x - explosion_arr[i].current_size / 2;
		explosion_arr[i].abs_y = explosion_arr[i].center_y - explosion_arr[i].current_size / 2;
		explosion_arr[i].rel_x = explosion_arr[i].abs_x - camX;
		explosion_arr[i].rel_y = explosion_arr[i].abs_y - camY;
		explosion_arr[i].hitbox = {(int)explosion_arr[i].rel_x, (int)explosion_arr[i].rel_y, (int)explosion_arr[i].current_size, (int)explosion_arr[i].current_size};
		// If the explosion has reached its maximum size, get rid of it
		if (explosion_arr[i].current_size >= explosion_arr[i].final_explosion_size) {
			explosion_arr.erase(explosion_arr.begin() + i);
		}
	}
}

std::vector<Missile*> MapBlocks::handleFiring(std::vector<Missile*> missiles, int posX, int posY) {
	for (int i = 0; i < blocks_arr.size(); i++) {
		if (blocks_arr[i].BLOCK_REL_X > 0 && blocks_arr[i].BLOCK_REL_Y > 0 && blocks_arr[i].BLOCK_REL_X <= 1280 && blocks_arr[i].BLOCK_REL_Y <= 720) {
			Missile * newMissile = blocks_arr[i].handleFiring(posX, posY);
			if (newMissile != nullptr) {
				missiles.push_back(newMissile);
			}
		}
	}
	return missiles;
}

bool MapBlocks::checkCollision(Kamikaze *kam){
	int i;
    for (i = 0; i < blocks_arr.size(); i++)
    {
        // If there's a collision, return true and delete the turret
		if (checkCollide(kam->getX(), kam->getY(), kam->getWidth(), kam->getHeight(), blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT))
        {
					explosion_arr.push_back(Explosion(blocks_arr[i].BLOCK_ABS_X + blocks_arr[i].BLOCK_WIDTH / 2, blocks_arr[i].BLOCK_ABS_Y + blocks_arr[i].BLOCK_HEIGHT / 2, 0, gRenderer));
					blocks_arr.erase(blocks_arr.begin() + i);
					return true;
        }
    }
    for (i = 0; i < stalagm_arr.size(); i++)
    {
        // If there's a collision, damage the enemy and delete the stalagmite
        if (checkCollide(kam->getX(), kam->getY(), kam->getWidth(), kam->getHeight(), stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT))
        {
						explosion_arr.push_back(Explosion(stalagm_arr[i].STALAG_ABS_X + stalagm_arr[i].STALAG_WIDTH / 2, stalagm_arr[i].STALAG_ABS_Y + stalagm_arr[i].STALAG_HEIGHT / 2, 1, gRenderer));
						stalagm_arr.erase(stalagm_arr.begin() + i);
						return true;
        }
		}

		for (i = 0; i < stalagt_arr.size(); i++)
		{
        // If there's a collision, damage the enemy and delete the stalactite
        if (checkCollide(kam->getX(), kam->getY(), kam->getWidth(), kam->getHeight(), stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT))
        {
						explosion_arr.push_back(Explosion(stalagt_arr[i].STALAG_ABS_X + stalagt_arr[i].STALAG_WIDTH / 2, stalagt_arr[i].STALAG_ABS_Y + stalagt_arr[i].STALAG_HEIGHT / 2, 1, gRenderer));
						stalagt_arr.erase(stalagt_arr.begin() + i);
						return true;
        }
    }
		return false;
}

void MapBlocks::checkCollision(Player *p)
{
    if(p->health <= 0) return;
	int i;
    for (i = blocks_arr.size() - 1; i >= 0; i--)
    {
        // If there's a collision, damage the player and blow up the turret
		if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT))
        {
            p->hit(5);
			explosion_arr.push_back(Explosion(blocks_arr[i].BLOCK_ABS_X + blocks_arr[i].BLOCK_WIDTH / 2, blocks_arr[i].BLOCK_ABS_Y + blocks_arr[i].BLOCK_HEIGHT / 2, 0, gRenderer));
			blocks_arr.erase(blocks_arr.begin() + i);
        }
    }

    for (i = health_arr.size() - 1; i >= 0; i--)
    {
        // If there's a collision, heal the player and delete health powerup
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), health_arr[i].HEALTH_REL_X, health_arr[i].HEALTH_REL_Y, health_arr[i].HEALTH_WIDTH, health_arr[i].HEALTH_HEIGHT))
        {
            p->heal(20);
            health_arr.erase(health_arr.begin() + i);
        }
    }

    for (i = infFire_arr.size() - 1; i >= 0; i--)
    {
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), infFire_arr[i].INF_FIRE_REL_X, infFire_arr[i].INF_FIRE_REL_Y, infFire_arr[i].INF_FIRE_WIDTH, infFire_arr[i].INF_FIRE_HEIGHT))
        {
            //turn off player overheats
            p->setInfiniteVal(true);
            p->resetHeatVals();
            infFire_arr.erase(infFire_arr.begin()+i);
        }
    }

    for (i = invince_arr.size() - 1; i >= 0; i--)
    {
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), invince_arr[i].INVINCE_REL_X, invince_arr[i].INVINCE_REL_Y, invince_arr[i].INVINCE_WIDTH, invince_arr[i].INVINCE_HEIGHT))
        {
            p->setInvinceVal(true);
            invince_arr.erase(invince_arr.begin()+i);
        }
    }
    for (i = ally_arr.size() - 1; i >= 0; i--)
    {
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), ally_arr[i].ALLY_PLANE_REL_X, ally_arr[i].ALLY_PLANE_REL_Y, ally_arr[i].ALLY_PLANE_WIDTH, ally_arr[i].ALLY_PLANE_HEIGHT))
        {
            // p->setInvinceVal(true);
            ally_arr.erase(ally_arr.begin() + i);
        }
    }
    for (i = autofire_arr.size() - 1; i >= 0; i--)
    {
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), autofire_arr[i].AUTOFIRE_REL_X, autofire_arr[i].AUTOFIRE_REL_Y, autofire_arr[i].AUTOFIRE_WIDTH, autofire_arr[i].AUTOFIRE_HEIGHT))
        {
            p->setAutoFire(true);
            autofire_arr.erase(autofire_arr.begin()+i);
        }
    }

    for (i = small_arr.size() - 1; i >= 0; i--)
    {
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), small_arr[i].SMALL_REL_X, small_arr[i].SMALL_REL_Y, small_arr[i].SMALL_WIDTH, small_arr[i].SMALL_HEIGHT))
        {
            p->setSmall(true);
            small_arr.erase(small_arr.begin()+i);
        }
    }

    for (i = stalagm_arr.size() - 1; i >= 0; i--)
    {
        // If there's a collision, damage the player and blow up the stalagmite
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), stalagm_arr[i].STALAG_REL_X + stalagm_arr[i].STALAG_WIDTH / 4, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].hitboxWidth, stalagm_arr[i].STALAG_HEIGHT))
        {
            p->hit(5);
			explosion_arr.push_back(Explosion(stalagm_arr[i].STALAG_ABS_X + stalagm_arr[i].STALAG_WIDTH / 2, stalagm_arr[i].STALAG_ABS_Y + stalagm_arr[i].STALAG_HEIGHT / 2, 1, gRenderer));
			stalagm_arr.erase(stalagm_arr.begin() + i);
        }
	}

	for (i = stalagt_arr.size() - 1; i >= 0; i--)
	{
		// If there's a collision, damage the player and blow up the stalactite
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), stalagt_arr[i].STALAG_REL_X + stalagt_arr[i].STALAG_WIDTH / 4, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].hitboxWidth, stalagt_arr[i].STALAG_HEIGHT))
        {
            p->hit(5);
			explosion_arr.push_back(Explosion(stalagt_arr[i].STALAG_ABS_X + stalagt_arr[i].STALAG_WIDTH / 2, stalagt_arr[i].STALAG_ABS_Y + stalagt_arr[i].STALAG_HEIGHT / 2, 1, gRenderer));
			stalagt_arr.erase(stalagt_arr.begin() + i);
        }
    }
    //ceiling and floor
    for(i = 0; i < ceiling_arr.size(); i++){
        if((checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), ceiling_arr[i].CEILING_REL_X, ceiling_arr[i].CEILING_REL_Y, WallBlock::block_side, WallBlock::block_side)))
        {
            p->undoXMove();
            p->undoYMove();

            if(checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(),ceiling_arr[i].CEILING_REL_X, ceiling_arr[i].CEILING_REL_Y, WallBlock::block_side, WallBlock::block_side))
            {
                p->setPosX(std::max(ceiling_arr[i].CEILING_REL_X - p->getWidth(), 0.0));
                p->redoYMove();
            }

        }
	}
	for (i = 0; i < floor_arr.size(); i++) {

        if((checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), floor_arr[i].FLOOR_REL_X, floor_arr[i].FLOOR_REL_Y, WallBlock::block_side, WallBlock::block_side)))
        {
            p->undoXMove();
            p->undoYMove();

            if(checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(),floor_arr[i].FLOOR_REL_X, floor_arr[i].FLOOR_REL_Y, WallBlock::block_side, WallBlock::block_side))
            {
                p->setPosX(std::max(floor_arr[i].FLOOR_REL_X - p->getWidth(), 0.0));
                p->redoYMove();
            }

        }
    }
}

void MapBlocks::checkCollision(Enemy *e)
{
	int i;
    for (i = 0; i < blocks_arr.size(); i++)
    {
        // If there's a collision, damage the enemy and delete the turret
		if (checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT))
        {
            e->hit(5);
			explosion_arr.push_back(Explosion(blocks_arr[i].BLOCK_ABS_X + blocks_arr[i].BLOCK_WIDTH / 2, blocks_arr[i].BLOCK_ABS_Y + blocks_arr[i].BLOCK_HEIGHT / 2, 0, gRenderer));
			blocks_arr.erase(blocks_arr.begin() + i);
        }
    }
    for (i = 0; i < stalagm_arr.size(); i++)
    {
        // If there's a collision, damage the enemy and delete the stalagmite
        if (checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT))
        {
            e->hit(5);
			explosion_arr.push_back(Explosion(stalagm_arr[i].STALAG_ABS_X + stalagm_arr[i].STALAG_WIDTH / 2, stalagm_arr[i].STALAG_ABS_Y + stalagm_arr[i].STALAG_HEIGHT / 2, 1, gRenderer));
			stalagm_arr.erase(stalagm_arr.begin() + i);
        }
	}
	for (i = 0; i < stalagt_arr.size(); i++)
	{
        // If there's a collision, damage the enemy and delete the stalactite
        if (checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT))
        {
            e->hit(5);
			explosion_arr.push_back(Explosion(stalagt_arr[i].STALAG_ABS_X + stalagt_arr[i].STALAG_WIDTH / 2, stalagt_arr[i].STALAG_ABS_Y + stalagt_arr[i].STALAG_HEIGHT / 2, 1, gRenderer));
			stalagt_arr.erase(stalagt_arr.begin() + i);
        }
    }
}

// Checks missile collisions with stalagmite and stalgtites
bool MapBlocks::checkCollision(Missile* m)
{
    for (int i = 0; i < stalagm_arr.size(); i++)
    {
        if (checkCollide(m->getX(), m->getY(), m->getWidth(), m->getWidth(), stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT))
        {
            int x = stalagm_arr[i].STALAG_ABS_X + stalagm_arr[i].STALAG_WIDTH / 2;
            int y = stalagm_arr[i].STALAG_ABS_Y + stalagm_arr[i].STALAG_HEIGHT / 2;
            explosion_arr.push_back(Explosion(x, y, 1, gRenderer));
            stalagm_arr.erase(stalagm_arr.begin() + i);
            return true;
        }
    }
    for (int i = 0; i < stalagt_arr.size(); i++)
    {
        if (checkCollide(m->getX(), m->getY(), m->getWidth(), m->getWidth(), stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT))
        {
            stalagt_arr[i].beenShot = 1;
            stalagt_arr[i].last_move = SDL_GetTicks();
            return true;
        }
    }

    return false;
}

// Returns 0 if the bullet hit nothing, 1 if it hit the ceiling, 2 if it hit the floor, 3 if it hit something else
int MapBlocks::checkCollision(Bullet *b)
{
    for (int i = blocks_arr.size() - 1; i >= 0; i--)
    {
        // If there's a collision with one of the planes, destroy the plane and the bullet
		if (checkCollide(b->getX(), b->getY(), b->getWidth(), b->getHeight(), blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT))
        {
			explosion_arr.push_back(Explosion(blocks_arr[i].BLOCK_ABS_X + blocks_arr[i].BLOCK_WIDTH / 2, blocks_arr[i].BLOCK_ABS_Y + blocks_arr[i].BLOCK_HEIGHT / 2, 0, gRenderer));
            blocks_arr.erase(blocks_arr.begin() + i);
            return 3;
        }
    }
    // If there's a collision with a stalagmite or a stalagtite, detroy the bullet. The stalag will be fine; stalags are strong.
    for (int i = 0; i < stalagm_arr.size(); i++)
	{
        if (checkCollide(b->getX(), b->getY(), b->getWidth(), b->getHeight(), stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT))
        {
            int x = stalagm_arr[i].STALAG_ABS_X + stalagm_arr[i].STALAG_WIDTH / 2;
            int y = stalagm_arr[i].STALAG_ABS_Y + stalagm_arr[i].STALAG_HEIGHT / 2;
            explosion_arr.push_back(Explosion(x, y, 1, gRenderer));
			stalagm_arr.erase(stalagm_arr.begin() + i);
            return 3;
        }
	}
	for (int i = 0; i < stalagt_arr.size(); i++)
	{
        if (checkCollide(b->getX(), b->getY(), b->getWidth(), b->getHeight(), stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT))
        {
            stalagt_arr[i].beenShot = 1;
            stalagt_arr[i].last_move = SDL_GetTicks();
            return 3;
        }
    }
	//ceiling and floor
    for(int i = 0; i < ceiling_arr.size(); i++) {
        if((checkCollide(b->getX(), b->getY(), b->getWidth(), b->getHeight(), ceiling_arr[i].CEILING_REL_X, ceiling_arr[i].CEILING_REL_Y, WallBlock::block_side, WallBlock::block_side)))
        {
            return 1;
        }
	}
	for (int i = 0; i < floor_arr.size(); i++) {
        if((checkCollide(b->getX(), b->getY(), b->getWidth(), b->getHeight(), floor_arr[i].FLOOR_REL_X, floor_arr[i].FLOOR_REL_Y, WallBlock::block_side, WallBlock::block_side)))
        {
            return 2;
        }
    }
	// Otherwise, the bullet didn't collide with anything and will survive
	return 0;
}


void MapBlocks::render(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer, bool caveIsEnabled)
{
    int i;

    if(caveIsEnabled && CaveSystem::CAVE_START_ABS_X != -1)
    {
        for (i = ceiling_arr.size() - 1; i >= 0; i--)
        {
            if (ceiling_arr[i].CEILING_ABS_X > CaveSystem::CAVE_START_ABS_X && ceiling_arr[i].CEILING_ABS_X < CaveSystem::CAVE_END_ABS_X)
            {
				ceiling_arr.erase(ceiling_arr.begin() + i);
            }
		}
		for (i = floor_arr.size() - 1; i >= 0; i--)
		{
            if (floor_arr[i].FLOOR_ABS_X > CaveSystem::CAVE_START_ABS_X && floor_arr[i].FLOOR_ABS_X < CaveSystem::CAVE_END_ABS_X)
            {
				floor_arr.erase(floor_arr.begin() + i);
            }
        }

    }


    for (i = 0; i < blocks_arr.size(); i++)
    {
        // Only render the Turret if will be screen
        if (blocks_arr[i].BLOCK_REL_X < SCREEN_WIDTH && blocks_arr[i].BLOCK_REL_Y < SCREEN_HEIGHT && blocks_arr[i].BLOCK_REL_Y >= WallBlock::block_side)
        {
            SDL_Rect fillRect = {(int)blocks_arr[i].BLOCK_REL_X, (int)blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT};
            if (blocks_arr[i].bottom == 1) {
				SDL_RenderCopyEx(gRenderer, bottomTurretSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
			}
			else {
				SDL_RenderCopyEx(gRenderer, topTurretSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
			}
        }
    }

    //Render Ceiling and floor
    for(i = 0; i < ceiling_arr.size(); i++)
	{
        if(ceiling_arr[i].CEILING_REL_X < SCREEN_WIDTH && ceiling_arr[i].CEILING_REL_Y < SCREEN_HEIGHT)
        {
            SDL_Rect fillRect = {(int)ceiling_arr[i].CEILING_REL_X, (int)ceiling_arr[i].CEILING_REL_Y, WallBlock::block_side, WallBlock::block_side};
            SDL_SetRenderDrawColor(gRenderer, 0x7F, 0x33, 0x00, 0xFF);
            SDL_RenderFillRect(gRenderer, &fillRect);
        }
	}

	for (i = 0; i < floor_arr.size(); i++)
	{
        if(floor_arr[i].FLOOR_REL_X < SCREEN_WIDTH && floor_arr[i].FLOOR_REL_Y < SCREEN_HEIGHT)
        {
            SDL_Rect fillRect = {(int)floor_arr[i].FLOOR_REL_X, (int)floor_arr[i].FLOOR_REL_Y, WallBlock::block_side, WallBlock::block_side};
            SDL_SetRenderDrawColor(gRenderer, 0x7F, 0x33, 0x00, 0xFF);
            SDL_RenderFillRect(gRenderer, &fillRect);
        }
    }

    for (i = 0; i < health_arr.size(); i++)
    {
        // Only render the health powerup if it will be screen
        if (health_arr[i].HEALTH_REL_X < SCREEN_WIDTH && health_arr[i].HEALTH_REL_Y < SCREEN_HEIGHT)
        {
            SDL_Rect fillRect = {(int)health_arr[i].HEALTH_REL_X, (int)health_arr[i].HEALTH_REL_Y, health_arr[i].HEALTH_WIDTH, health_arr[i].HEALTH_HEIGHT};
            SDL_RenderCopyEx(gRenderer, healthSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }

    for (i = 0; i < infFire_arr.size(); i++)
    {
        // Only render the shooting powerup if it will be screen
        if (infFire_arr[i].INF_FIRE_REL_X < SCREEN_WIDTH && infFire_arr[i].INF_FIRE_REL_Y < SCREEN_HEIGHT)
        {
            SDL_Rect fillRect = {(int)infFire_arr[i].INF_FIRE_REL_X, (int)infFire_arr[i].INF_FIRE_REL_Y, infFire_arr[i].INF_FIRE_WIDTH, infFire_arr[i].INF_FIRE_HEIGHT};
            SDL_RenderCopyEx(gRenderer, infFireSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }

    for (i = 0; i < invince_arr.size(); i++)
    {
        // Only render the invince powerup if it will be screen
        if (invince_arr[i].INVINCE_REL_X < SCREEN_WIDTH && invince_arr[i].INVINCE_REL_Y < SCREEN_HEIGHT)
        {
            SDL_Rect fillRect = {(int)invince_arr[i].INVINCE_REL_X, (int)invince_arr[i].INVINCE_REL_Y, invince_arr[i].INVINCE_WIDTH, invince_arr[i].INVINCE_HEIGHT};
            SDL_RenderCopyEx(gRenderer, invinceSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }

    for (i = 0; i < autofire_arr.size(); i++)
    {
        // Only render the invince powerup if it will be screen
        if (autofire_arr[i].AUTOFIRE_REL_X < SCREEN_WIDTH && autofire_arr[i].AUTOFIRE_REL_Y < SCREEN_HEIGHT)
        {
            SDL_Rect fillRect = {(int)autofire_arr[i].AUTOFIRE_REL_X, (int)autofire_arr[i].AUTOFIRE_REL_Y, autofire_arr[i].AUTOFIRE_WIDTH, autofire_arr[i].AUTOFIRE_HEIGHT};
            SDL_RenderCopyEx(gRenderer, autofireSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }

    for (i = 0; i < small_arr.size(); i++)
    {
        // Only render the invince powerup if it will be screen
        if (small_arr[i].SMALL_REL_X < SCREEN_WIDTH && small_arr[i].SMALL_REL_Y < SCREEN_HEIGHT)
        {
            SDL_Rect fillRect = {(int)small_arr[i].SMALL_REL_X, (int)small_arr[i].SMALL_REL_Y, small_arr[i].SMALL_WIDTH, small_arr[i].SMALL_HEIGHT};
            SDL_RenderCopyEx(gRenderer, smallSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }


    // for (i = 0; i < ally_arr.size(); i++)
    // {
    //     // Only render the invince powerup if it will be screen
    //     if (ally_arr[i].ALLY_PLANE_REL_X < SCREEN_WIDTH && ally_arr[i].ALLY_PLANE_REL_Y < SCREEN_HEIGHT)
    //     {
    //         SDL_Rect fillRect = {(int)ally_arr[i].ALLY_PLANE_REL_X, (int)ally_arr[i].ALLY_PLANE_REL_Y, ally_arr[i].ALLY_PLANE_WIDTH, ally_arr[i].ALLY_PLANE_HEIGHT};
    //         SDL_RenderCopyEx(gRenderer, allySprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
    //     }
    // }



    for (i = 0; i < stalagm_arr.size(); i++)
    {
        // Only render the Stalag if will be screen
        if (stalagm_arr[i].STALAG_REL_X >= -stalagt_arr[i].STALAG_HEIGHT && stalagm_arr[i].STALAG_REL_Y >= -stalagt_arr[i].STALAG_WIDTH && stalagm_arr[i].STALAG_REL_X < SCREEN_WIDTH && stalagm_arr[i].STALAG_REL_Y < SCREEN_HEIGHT)
        {
            SDL_Rect fillRect = {(int)stalagm_arr[i].STALAG_REL_X, (int)stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT};
            if (stalagm_arr[i].stalagShapeNum == 1) {
				SDL_RenderCopyEx(gRenderer, stalagmiteSprite1, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
			}
			else if (stalagm_arr[i].stalagShapeNum == 2) {
				SDL_RenderCopyEx(gRenderer, stalagmiteSprite2, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
			}
			else if (stalagm_arr[i].stalagShapeNum == 3) {
				SDL_RenderCopyEx(gRenderer, stalagmiteSprite3, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
			}
			else {
				SDL_RenderCopyEx(gRenderer, stalagmiteSprite4, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
			}
        }
    }

    for (i = 0; i < stalagt_arr.size(); i++)
    {
        // Only render the Stalag if will be screen
        if (stalagt_arr[i].STALAG_REL_X >= -stalagt_arr[i].STALAG_WIDTH && stalagt_arr[i].STALAG_REL_Y >= -stalagt_arr[i].STALAG_HEIGHT && stalagt_arr[i].STALAG_REL_X < SCREEN_WIDTH && stalagt_arr[i].STALAG_REL_Y < SCREEN_HEIGHT && stalagt_arr[i].STALAG_REL_Y + stalagt_arr[i].STALAG_HEIGHT < SCREEN_HEIGHT + 35 - WallBlock::block_side){ // + 35 to have the stalags stick around a little after hittig the floor

			SDL_Rect fillRect = {(int)stalagt_arr[i].STALAG_REL_X, (int)stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT};
            if (stalagt_arr[i].stalagShapeNum == 1) {
				SDL_RenderCopyEx(gRenderer, stalactiteSprite1, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
			}
			else if (stalagt_arr[i].stalagShapeNum == 2) {
				SDL_RenderCopyEx(gRenderer, stalactiteSprite2, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
			}
			else if (stalagt_arr[i].stalagShapeNum == 3) {
				SDL_RenderCopyEx(gRenderer, stalactiteSprite3, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
			}
			else {
				SDL_RenderCopyEx(gRenderer, stalactiteSprite4, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
			}
        }

        if(stalagt_arr[i].STALAG_REL_Y + stalagt_arr[i].STALAG_HEIGHT >= SCREEN_HEIGHT + 35 - WallBlock::block_side && stalagt_arr[i].STALAG_REL_Y + stalagt_arr[i].STALAG_HEIGHT <= SCREEN_HEIGHT + 37 - WallBlock::block_side){
            int x = stalagt_arr[i].STALAG_ABS_X + stalagt_arr[i].STALAG_WIDTH / 2;
            int y = stalagt_arr[i].STALAG_ABS_Y + stalagt_arr[i].STALAG_HEIGHT / 2;
            explosion_arr.push_back(Explosion(x, y, 1, gRenderer));
			stalagt_arr.erase(stalagt_arr.begin() + i);
        }
    }

	for (i = 0; i < explosion_arr.size(); i++) {
        if(explosion_arr[i].type == 0){
		    SDL_RenderCopyEx(gRenderer, explosionSprite, nullptr, &explosion_arr[i].hitbox, 0.0, nullptr, SDL_FLIP_NONE);
        }
        else{
            SDL_RenderCopyEx(gRenderer, dustCloudSprite, nullptr, &explosion_arr[i].hitbox, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }
}

// Add an explosion at the given location
void MapBlocks::addExplosion(int x, int y, int w, int h, int type) {
	if (type == 0) Mix_PlayChannel(-1, explosion_sound, 0);
	explosion_arr.push_back(Explosion(x + w / 2, y + h / 2, type, gRenderer));
}

std::vector<Stalagmite> MapBlocks::getStalagmites() {
	return stalagm_arr;
}

std::vector<Stalagtite> MapBlocks::getStalagtites() {
	return stalagt_arr;
}

std::vector<Turret> MapBlocks::getTurrets() {
	return blocks_arr;
}

// Special version of MapBlocks optimized for the boss section
BossBlocks::BossBlocks(int w, int h, SDL_Renderer *gr, int diff)
{
	screen_width = w;
	screen_height = h;
	difficulty = diff;
	gRenderer = gr;
	explosionSprite = loadImage("sprites/Explosion.png", gRenderer);
	dustCloudSprite = loadImage("sprites/dustCloud.png", gRenderer);
    healthSprite=loadImage("sprites/health.png", gRenderer);
    infFireSprite=loadImage("sprites/infFire.png", gRenderer);
    invinceSprite=loadImage("sprites/invince.png", gRenderer);
    autofireSprite=loadImage("sprites/autofire.png", gRenderer);
    smallSprite=loadImage("sprites/small.png", gRenderer);
    allySprite=loadImage("sprites/plus_ally_ai.png", gRenderer);
	
	explosion_sound = Mix_LoadWAV("sounds/explosion.wav");
	
	currentX = w;
}

BossBlocks::~BossBlocks()
{
	SDL_DestroyTexture(explosionSprite);
	SDL_DestroyTexture(dustCloudSprite);
	SDL_DestroyTexture(healthSprite);
    SDL_DestroyTexture(infFireSprite);
    SDL_DestroyTexture(invinceSprite);
    SDL_DestroyTexture(autofireSprite);
    SDL_DestroyTexture(smallSprite);
    SDL_DestroyTexture(allySprite);
	Mix_FreeChunk(explosion_sound);
}

bool BossBlocks::checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight)
{
    if (x + pWidth < xTwo || x > xTwo + pTwoWidth)
        return false;
    if (y + pHeight < yTwo || y > yTwo + pTwoHeight)
        return false;
    return true;
}

void BossBlocks::moveBlocks(double camShift)
{
	// Make new powerups if a screen has passed
	currentX += camShift;
	if (currentX > screen_width) {
		currentX = 0;
		createPowerups();
	}
	
	int i;
	// Move everything left based on how much the camera has shifted
    for (i = 0; i < health_arr.size(); i++)
    {
        health_arr[i].HEALTH_REL_X -= camShift;
    }

    for (i = 0; i < infFire_arr.size(); i++)
    {
        infFire_arr[i].INF_FIRE_REL_X -= camShift;
    }

    for (i = 0; i < invince_arr.size(); i++)
    {
        invince_arr[i].INVINCE_REL_X -= camShift;
    }
    for (i = 0; i < autofire_arr.size(); i++)
    {
        autofire_arr[i].AUTOFIRE_REL_X -= camShift;
    }

    for (i = 0; i < small_arr.size(); i++)
    {
        small_arr[i].SMALL_REL_X -= camShift;
    }
	
    for(i = 0; i < ally_arr.size(); i++)
    {
        ally_arr[i].ALLY_PLANE_REL_X -= camShift;
    }
	
	for (i = explosion_arr.size() - 1; i >= 0; i--)
	{
		explosion_arr[i].current_size = (double) explosion_arr[i].initial_explosion_size + ((SDL_GetTicks() - explosion_arr[i].explosion_time) * explosion_arr[i].explosion_speed) / 1000;
		if (!explosion_arr[i].stationary) {
			explosion_arr[i].center_x -= camShift;
		}
		explosion_arr[i].rel_x = explosion_arr[i].center_x - explosion_arr[i].current_size / 2;
		explosion_arr[i].rel_y = explosion_arr[i].center_y - explosion_arr[i].current_size / 2;
		explosion_arr[i].hitbox = {(int)explosion_arr[i].rel_x, (int)explosion_arr[i].rel_y, (int)explosion_arr[i].current_size, (int)explosion_arr[i].current_size};
		// If the explosion has reached its maximum size, get rid of it
		if (explosion_arr[i].current_size >= explosion_arr[i].final_explosion_size) {
			explosion_arr.erase(explosion_arr.begin() + i);
		}
	}
}

// Every screen_width pixels, create new powerups
void BossBlocks::createPowerups()
{
	// Set the number of powerups according to the difficulty
	int powerupCount;
	if (difficulty == 1) powerupCount = 4;
	if (difficulty == 2) powerupCount = 3;
	if (difficulty == 3) powerupCount = 2;
	
	// Randomly choose from the 6 powerups to add
	int powerupNum;
	for (int i = 0; i < powerupCount; i++)
	{
		powerupNum = rand() % 6;
		if (powerupNum == 0) {
			HealthBlock newHealthBlock = HealthBlock();
			newHealthBlock.HEALTH_REL_X = (rand() % (screen_width - newHealthBlock.HEALTH_WIDTH)) + screen_width;
			newHealthBlock.HEALTH_REL_Y = rand() % (screen_height - MARGIN - newHealthBlock.HEALTH_HEIGHT) + MARGIN;
			health_arr.push_back(newHealthBlock);
		}
		else if (powerupNum == 1) {
			InfFireBlock newInfFireBlock = InfFireBlock();
			newInfFireBlock.INF_FIRE_REL_X = (rand() % (screen_width - newInfFireBlock.INF_FIRE_WIDTH)) + screen_width;
			newInfFireBlock.INF_FIRE_REL_Y = rand() % (screen_height - MARGIN - newInfFireBlock.INF_FIRE_HEIGHT) + MARGIN;
			infFire_arr.push_back(newInfFireBlock);
		}
		else if (powerupNum == 2) {
			AllyPlaneBlock newAllyPlaneBlock = AllyPlaneBlock();
			newAllyPlaneBlock.ALLY_PLANE_REL_X = (rand() % (screen_width - newAllyPlaneBlock.ALLY_PLANE_WIDTH)) + screen_width;
			newAllyPlaneBlock.ALLY_PLANE_REL_Y = rand() % (screen_height - MARGIN - newAllyPlaneBlock.ALLY_PLANE_HEIGHT) + MARGIN;
			ally_arr.push_back(newAllyPlaneBlock);
		}
		else if (powerupNum == 3) {
			AutoFireBlock newAutoFireBlock = AutoFireBlock();
			newAutoFireBlock.AUTOFIRE_REL_X = (rand() % (screen_width - newAutoFireBlock.AUTOFIRE_WIDTH)) + screen_width;
			newAutoFireBlock.AUTOFIRE_REL_Y = rand() % (screen_height - MARGIN - newAutoFireBlock.AUTOFIRE_HEIGHT) + MARGIN;
			autofire_arr.push_back(newAutoFireBlock);
		}
		else if (powerupNum == 4) {
			InvincBlock newInvincBlock = InvincBlock();
			newInvincBlock.INVINCE_REL_X = (rand() % (screen_width - newInvincBlock.INVINCE_WIDTH)) + screen_width;
			newInvincBlock.INVINCE_REL_Y = rand() % (screen_height - MARGIN - newInvincBlock.INVINCE_HEIGHT) + MARGIN;
			invince_arr.push_back(newInvincBlock);
		}
		else {
			SmallBlock newSmallBlock = SmallBlock();
			newSmallBlock.SMALL_REL_X = (rand() % (screen_width - newSmallBlock.SMALL_WIDTH)) + screen_width;
			newSmallBlock.SMALL_REL_Y = rand() % (screen_height - MARGIN - newSmallBlock.SMALL_HEIGHT) + MARGIN;
			small_arr.push_back(newSmallBlock);
		}
	}
}

// Add an explosion at the given location
void BossBlocks::addExplosion(int x, int y, int w, int h, int type) {
    if (type == 0) Mix_PlayChannel(-1, explosion_sound, 0);
	explosion_arr.push_back(Explosion(x + w / 2, y + h / 2, type, gRenderer));
}

// Add an explosion at given x and y with given size
void BossBlocks::addExplosion(int x, int y, int size) {
	Mix_PlayChannel(-1, explosion_sound, 0);
	explosion_arr.push_back(Explosion(x, y, size));
}

// Handle collisions between player and powerups
void BossBlocks::checkCollision(Player *p)
{
    if(p->health <= 0) return;
	int i;
	
    for (i = health_arr.size() - 1; i >= 0; i--)
    {
        // If there's a collision, heal the player and delete health powerup
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), health_arr[i].HEALTH_REL_X, health_arr[i].HEALTH_REL_Y, health_arr[i].HEALTH_WIDTH, health_arr[i].HEALTH_HEIGHT))
        {
            p->heal(20);
            health_arr.erase(health_arr.begin() + i);
        }
    }
    for (i = infFire_arr.size() - 1; i >= 0; i--)
    {
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), infFire_arr[i].INF_FIRE_REL_X, infFire_arr[i].INF_FIRE_REL_Y, infFire_arr[i].INF_FIRE_WIDTH, infFire_arr[i].INF_FIRE_HEIGHT))
        {
            //turn off player overheats
            p->setInfiniteVal(true);
            p->resetHeatVals();
            infFire_arr.erase(infFire_arr.begin()+i);
        }
    }
    for (i = invince_arr.size() - 1; i >= 0; i--)
    {
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), invince_arr[i].INVINCE_REL_X, invince_arr[i].INVINCE_REL_Y, invince_arr[i].INVINCE_WIDTH, invince_arr[i].INVINCE_HEIGHT))
        {
            p->setInvinceVal(true);
            invince_arr.erase(invince_arr.begin()+i);
        }
    }
    for (i = ally_arr.size() - 1; i >= 0; i--)
    {
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), ally_arr[i].ALLY_PLANE_REL_X, ally_arr[i].ALLY_PLANE_REL_Y, ally_arr[i].ALLY_PLANE_WIDTH, ally_arr[i].ALLY_PLANE_HEIGHT))
        {
            // p->setInvinceVal(true);
            ally_arr.erase(ally_arr.begin() + i);
        }
    }
    for (i = autofire_arr.size() - 1; i >= 0; i--)
    {
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), autofire_arr[i].AUTOFIRE_REL_X, autofire_arr[i].AUTOFIRE_REL_Y, autofire_arr[i].AUTOFIRE_WIDTH, autofire_arr[i].AUTOFIRE_HEIGHT))
        {
            p->setAutoFire(true);
            autofire_arr.erase(autofire_arr.begin()+i);
        }
    }
    for (i = small_arr.size() - 1; i >= 0; i--)
    {
        if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), small_arr[i].SMALL_REL_X, small_arr[i].SMALL_REL_Y, small_arr[i].SMALL_WIDTH, small_arr[i].SMALL_HEIGHT))
        {
            p->setSmall(true);
            small_arr.erase(small_arr.begin()+i);
        }
    }
}

void BossBlocks::renderPowerups(SDL_Renderer* gRenderer)
{
    int i;
	
	// Render all of the powerups, deleting anything that is no longer needed
    for (i = health_arr.size() - 1; i >= 0; i--)
    {
		if (health_arr[i].HEALTH_REL_X < -health_arr[i].HEALTH_WIDTH) {
			health_arr.erase(health_arr.begin() + i);
		}
		else {
			SDL_Rect fillRect = {(int)health_arr[i].HEALTH_REL_X, (int)health_arr[i].HEALTH_REL_Y, health_arr[i].HEALTH_WIDTH, health_arr[i].HEALTH_HEIGHT};
			SDL_RenderCopyEx(gRenderer, healthSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
		}
	}

    for (i = infFire_arr.size() - 1; i >= 0; i--)
    {
        if (infFire_arr[i].INF_FIRE_REL_X < -infFire_arr[i].INF_FIRE_WIDTH) {
			infFire_arr.erase(infFire_arr.begin() + i);
		}
		else {
            SDL_Rect fillRect = {(int)infFire_arr[i].INF_FIRE_REL_X, (int)infFire_arr[i].INF_FIRE_REL_Y, infFire_arr[i].INF_FIRE_WIDTH, infFire_arr[i].INF_FIRE_HEIGHT};
            SDL_RenderCopyEx(gRenderer, infFireSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }

    for (i = invince_arr.size() - 1; i >= 0; i--)
    {
        if (invince_arr[i].INVINCE_REL_X < -invince_arr[i].INVINCE_WIDTH) {
			invince_arr.erase(invince_arr.begin() + i);
		}
		else {
            SDL_Rect fillRect = {(int)invince_arr[i].INVINCE_REL_X, (int)invince_arr[i].INVINCE_REL_Y, invince_arr[i].INVINCE_WIDTH, invince_arr[i].INVINCE_HEIGHT};
            SDL_RenderCopyEx(gRenderer, invinceSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }

    for (i = autofire_arr.size() - 1; i >= 0; i--)
    {
        if (autofire_arr[i].AUTOFIRE_REL_X < -autofire_arr[i].AUTOFIRE_WIDTH) {
			autofire_arr.erase(autofire_arr.begin() + i);
		}
		else {
            SDL_Rect fillRect = {(int)autofire_arr[i].AUTOFIRE_REL_X, (int)autofire_arr[i].AUTOFIRE_REL_Y, autofire_arr[i].AUTOFIRE_WIDTH, autofire_arr[i].AUTOFIRE_HEIGHT};
            SDL_RenderCopyEx(gRenderer, autofireSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }

    for (i = small_arr.size() - 1; i >= 0; i--)
    {
        if (small_arr[i].SMALL_REL_X < -small_arr[i].SMALL_WIDTH) {
			small_arr.erase(small_arr.begin() + i);
		}
		else {
            SDL_Rect fillRect = {(int)small_arr[i].SMALL_REL_X, (int)small_arr[i].SMALL_REL_Y, small_arr[i].SMALL_WIDTH, small_arr[i].SMALL_HEIGHT};
            SDL_RenderCopyEx(gRenderer, smallSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }


    // for (i = ally_arr.size() - 1; i >= 0; i--)
    // {
    //     if (ally_arr[i].ALLY_PLANE_REL_X < -ally_arr[i].ALLY_PLANE_WIDTH) {
	// 		ally_arr.erase(ally_arr.begin() + i);
	// 	}
	// 	else {
    //         SDL_Rect fillRect = {(int)ally_arr[i].ALLY_PLANE_REL_X, (int)ally_arr[i].ALLY_PLANE_REL_Y, ally_arr[i].ALLY_PLANE_WIDTH, ally_arr[i].ALLY_PLANE_HEIGHT};
    //         SDL_RenderCopyEx(gRenderer, allySprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
    //     }
    // }
}

void BossBlocks::renderExplosions(SDL_Renderer* gRenderer) {
	int i;
	for (i = explosion_arr.size() - 1; i >= 0; i--) {
        if(explosion_arr[i].type == 0){
		    SDL_RenderCopyEx(gRenderer, explosionSprite, nullptr, &explosion_arr[i].hitbox, 0.0, nullptr, SDL_FLIP_NONE);
        }
        else{
            SDL_RenderCopyEx(gRenderer, dustCloudSprite, nullptr, &explosion_arr[i].hitbox, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }
}
