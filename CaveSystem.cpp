#include "CaveSystem.h"

int CaveSystem::CAVE_END_ABS_X;
int CaveSystem::CAVE_START_ABS_X;

CaveBlock::CaveBlock(){}
PathSequence::PathSequence(){}


CaveSystem::CaveSystem()
{
    CAVE_END_ABS_X = -1;
    CAVE_START_ABS_X = -1;
    isEnabled = false;
}

std::string CaveBlock::toString()
{
    return std::to_string(enabled);
}

void printMatrix(CaveBlock *mat[CaveSystem::CAVE_SYSTEM_HEIGHT][CaveSystem::CAVE_SYSTEM_WIDTH], std::size_t N, std::size_t M)
{
    std::cout<<"\n Printing Matrix : \n";
    for(int i = 0 ; i < N ; ++i) {
        for(int j = 0 ; j < M; ++j)
            std::cout << mat[i][j]->toString() << " ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

CaveSystem::CaveSystem(int camX, int camY, int SCREEN_WIDTH, int difficulty)
{
    int i, j;
    int offsetX = camX;

    CAVE_START_ABS_X = offsetX + SCREEN_WIDTH;
    CAVE_END_ABS_X = offsetX + CaveBlock::CAVE_SYSTEM_PIXEL_WIDTH + SCREEN_WIDTH;

    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            CaveBlock *curr_block = new CaveBlock();
            curr_block->CAVE_BLOCK_ABS_X = offsetX + SCREEN_WIDTH + (j * CaveBlock::CAVE_BLOCK_WIDTH);
            curr_block->CAVE_BLOCK_ABS_Y = i * CaveBlock::CAVE_BLOCK_HEIGHT;

            curr_block->CAVE_BLOCK_REL_X = curr_block->CAVE_BLOCK_ABS_X;
            curr_block->CAVE_BLOCK_REL_Y = curr_block->CAVE_BLOCK_ABS_Y;
            curr_block->isPointy = 0;
            cave_system[i][j] = curr_block;
        }

    ceilSprite = nullptr;
    floorSprite = nullptr;
    isEnabled = true;
    diff = difficulty;
    generateRandomCave();
    // printMatrix(cave_system, CAVE_SYSTEM_HEIGHT, CAVE_SYSTEM_WIDTH);
}

CaveSystem::~CaveSystem()
{
    //std::cout << "Deallocating Cave System" << std::endl;
    for(int i=0;i<CAVE_SYSTEM_HEIGHT;i++)
    {
        for(int j=0;j<CAVE_SYSTEM_WIDTH; j++)
        {
            // std::cout << "deallocating item " << i << " , " << j << " from " << cave_system[i][j] << std::endl;
            delete cave_system[i][j];
            // std::cout << "deleted"<< std::endl;
        }
    }
    // delete[] &cave_system;
}

PathSequence* CaveSystem::getPathSequence()
{
    return &path;
}

void CaveSystem::generateRandomCave()
{
    /*

        This is the function that is generating the "randomness of the cave".
        We have a 2D array in cave_system and can iterator through each block
        with the nested FOR loop below. From there, set whether each block will
        rendered by setting block->enabled to 0 or 1.

        It uses a lot of lamda functions because its more organized
    */
    int i, j, x1, x2, y1, y2;

    // FILL THE BOARD WITH BLOCKS
    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            CaveBlock *curr_block = cave_system[i][j];

            // if (curr_block->CAVE_BLOCK_REL_Y > 500 || curr_block->CAVE_BLOCK_REL_Y < 250)
            //     curr_block->enabled = 1;
            // else
            curr_block->enabled = 1;

        }

    auto insert_path = [&](CaveBlock * mat[CaveSystem::CAVE_SYSTEM_HEIGHT][CaveSystem::CAVE_SYSTEM_WIDTH], PathSequence * path, int y_padding)
    {
        // This function inserts the generated Path into a 2D system of cave blocks
        // It is this 2D array that is finally rendered to the screen

        // y_padding will increase the height of the cave

        int i, j, cx, cy;

        for(i = 0; i < path->length; i++)
        {
            cx = path->x[i];
            cy = path->y[i];

            int padding = (3 * cos(i/7) + y_padding) + rand() % 2;
            for (j = (padding * -1); j < padding; j++)
            {
               
                if (cy + j >= 0 && cy + j < CaveSystem::CAVE_SYSTEM_HEIGHT)
                {
                      mat[cy + j][cx]->enabled = 0;
                      //printf("this is cy+j inside if: %d x: %d\n", (cy+j), cx);
                }
                // else
                // {
                //     printf("this is cy+j else if: %d x: %d\n", (cy+j), cx);
                // }
                
                  
            }
        }
    };

    auto rnd_i0 = [&](int n) {
        /* 0 <= rnd_i0(n) < n */
        return ((int)(rand() % n));
    };

    auto int_sign = [&](int n) {
        // -1, 0, or 1 if n is +, 0, or -
        if(n > 0)
            return 1;
        else if (n == 0)
            return 0;
        else
            return -1;
    };

    auto bresenham_line = [&](PathSequence *seq, int x1, int y1, int x2, int y2) {
        // The Bresenham line algorithm. Not symmetrical.
        // Generates a starting line from one end of the cave to other

        int xstep, ystep, xc, yc, acc, cnt;
        cnt = 0;

        xstep = int_sign(x2 - x1);
        ystep = int_sign(y2 - y1);

        xc = x1;
        yc = y1;

        seq->x[cnt] = xc;
        seq->y[cnt] = yc;
        cnt++;

        if ((x1 == x2) && (y1 == y2))
        {
            seq->length = cnt;
            return;
        }

        if (abs(x2 - x1) >= abs(y2 - y1))
        {
            acc = abs(x2 - x1);
            do
            {
                xc += xstep;
                acc += 2 * abs(y2 - y1);

                if (acc >= 2 * abs(x2 - x1))
                {
                    acc -= 2 * abs(x2 - x1);
                    yc += ystep;
                }
                seq->x[cnt] = xc;
                seq->y[cnt] = yc;
                cnt++;
            } while ((xc != x2) && (cnt < CaveSystem::CAVE_SYSTEM_WIDTH));
        }
        else
        {
            acc = abs(y2 - y1);
            do
            {
                yc += ystep;
                acc += 2 * abs(x2 - x1);

                if (acc >= 2 * abs(y2 - y1))
                {
                    acc -= 2 * abs(y2 - y1);
                    xc += xstep;
                }
                seq->x[cnt] = xc;
                seq->y[cnt] = yc;
                cnt++;
            } while ((yc != y2) && (cnt < CaveSystem::CAVE_SYSTEM_WIDTH));
        }
        seq->length = cnt;
    };

    auto uti_perturb = [&](PathSequence *seq, int mindist, int maxdist, int pertamt) {
        int i;
        int nx, ny;
        int lox, loy, hix, hiy;
        int lod2, hid2;
        int ri, rdir;
        int mind2, maxd2;
        int Xoff[8] = {1, 1, 0, -1, -1, -1, 0, 1};
        int Yoff[8] = {0, 1, 1, 1, 0, -1, -1, -1};

        mind2 = mindist * mindist;
        maxd2 = maxdist * maxdist;
        for (i = 0; i < pertamt * seq->length; i++)
        {
            ri = 1 + rnd_i0(seq->length - 2);
            rdir = rnd_i0(8);
            nx = seq->x[ri] + Xoff[rdir];
            ny = seq->y[ri] + Yoff[rdir];
            lox = seq->x[ri - 1];
            loy = seq->y[ri - 1];
            hix = seq->x[ri + 1];
            hiy = seq->y[ri + 1];
            lod2 = ((nx - lox) * (nx - lox)) + ((ny - loy) * (ny - loy));
            hid2 = ((nx - hix) * (nx - hix)) + ((ny - hiy) * (ny - hiy));

            if ((lod2 < mind2) || (lod2 > maxd2) || (hid2 < mind2) || (hid2 > maxd2))
                continue;

            // seq->x[ri] = nx;
            seq->y[ri] = ny;
        }
    };

    // Start and end point
    // y values are have a 5 point padding so that it doesnt interfere with the walls
    x1 = 0;
    y1 = 8 + rnd_i0(CaveSystem::CAVE_SYSTEM_HEIGHT - 12);

    x2 = CaveSystem::CAVE_SYSTEM_WIDTH;
    y2 = 8 + rnd_i0(CaveSystem::CAVE_SYSTEM_HEIGHT - 12);

    bresenham_line(&path, x1, y1, x2, y2);
    uti_perturb(&path, 2, 5, 40);

    int padding;
    if(diff == 3)
        padding = rand() % 3 + 8;
    else if (diff == 2)
        padding = rand() % 4 + 9;
    else if (diff == 1)
        padding = rand() % 3 + 10;


    insert_path(CaveSystem::cave_system, &path, padding);
}

void CaveSystem::moveCaveBlocks(int camX, int camY)
{
    int i, j;
    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            CaveBlock *curr_block = cave_system[i][j];
            curr_block->CAVE_BLOCK_REL_X = curr_block->CAVE_BLOCK_ABS_X - camX;
        }
}

bool checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight)
{
    if (x + pWidth < xTwo || x > xTwo + pTwoWidth)
        return false;
    if (y + pHeight < yTwo || y > yTwo + pTwoHeight)
        return false;
    return true;
}

void CaveSystem::checkCollision(Player *p)
{
    int i, j;
    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            // If there's a collision, cancel the player's move
            if (cave_system[i][j]->enabled == 1 && (checkCollide(p->getPosX() + 12, p->getPosY() + 12, p->getHurtWidth(), p->getHurtHeight(), cave_system[i][j]->CAVE_BLOCK_REL_X, cave_system[i][j]->CAVE_BLOCK_REL_Y, cave_system[i][j]->CAVE_BLOCK_WIDTH, cave_system[i][j]->CAVE_BLOCK_HEIGHT)))
            {
                if(cave_system[i][j]->isPointy == 0){//Player dies instantly if they hit the wall
                    if(diff == 3){
                        p->hit(p->getHealth());
                    }
                    else if(diff == 2){
                        p->hit(p->getHealth() * 1.5);
                    }
                    else{
                        p->hit(p->getHealth() * 2);
                    }
                }
                else{//Player is dealt 25 damage if they hit a pointy cave
                    if(diff == 3){
                        p->hit(25);
                    }
                    else if(diff == 2){
                        p->hit(25 * 1.5);
                    }
                    else{
                        p->hit(25 * 2);
                    }
                    p->undoYMove();
					// If there's still a collision, push the player away from the block they hit so that they don't get sucked into the cave walls
					if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), cave_system[i][j]->CAVE_BLOCK_REL_X, cave_system[i][j]->CAVE_BLOCK_REL_Y, cave_system[i][j]->CAVE_BLOCK_WIDTH, cave_system[i][j]->CAVE_BLOCK_HEIGHT))
					{
						if (cave_system[i-1][j]->enabled == 1) {
							p->setPosY(p->getPosY() + 5);
						}
						else {
							p->setPosY(p->getPosY() - 5);
						}
					}
                }

                // // If there's still a collision, it's due to the scrolling and they need to be moved left accordingly
                // if (checkCollide(p->getPosX(), p->getPosY(), p->getWidth(), p->getHeight(), cave_system[i][j]->CAVE_BLOCK_REL_X, cave_system[i][j]->CAVE_BLOCK_REL_Y, cave_system[i][j]->CAVE_BLOCK_WIDTH, cave_system[i][j]->CAVE_BLOCK_HEIGHT))
                // {
                //     p->setPosX(std::max(cave_system[i][j]->CAVE_BLOCK_REL_X - p->getWidth(), 0));
                //     p->redoYMove();
                // }
            }
        }
}

void CaveSystem::checkCollision(Enemy *e){
    int i, j;
    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            // If there's a collision, cancel the player's move
            if (cave_system[i][j]->enabled == 1 && (checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), cave_system[i][j]->CAVE_BLOCK_REL_X, cave_system[i][j]->CAVE_BLOCK_REL_Y, cave_system[i][j]->CAVE_BLOCK_WIDTH, cave_system[i][j]->CAVE_BLOCK_HEIGHT)))
            {
                e->hit(e->getHealth());//Enemy dies instantly
            }
        }
}

bool CaveSystem::checkCollision(Bullet *b){
    int i, j;
    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
	{
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            // If there's a collision, cancel the player's move
            if (cave_system[i][j]->enabled == 1 && (checkCollide(b->getX(), b->getY(), b->getWidth(), b->getHeight(), cave_system[i][j]->CAVE_BLOCK_REL_X, cave_system[i][j]->CAVE_BLOCK_REL_Y, cave_system[i][j]->CAVE_BLOCK_WIDTH, cave_system[i][j]->CAVE_BLOCK_HEIGHT)))
            {
                return true;
            }
        }
	}
	return false;
}

bool CaveSystem::checkCollision(Missile *m){
    int i, j;
    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
	{
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            // If there's a collision, cancel the player's move
            if (cave_system[i][j]->enabled == 1 && (checkCollide(m->getX(), m->getY(), m->getWidth(), m->getHeight(), cave_system[i][j]->CAVE_BLOCK_REL_X, cave_system[i][j]->CAVE_BLOCK_REL_Y, cave_system[i][j]->CAVE_BLOCK_WIDTH, cave_system[i][j]->CAVE_BLOCK_HEIGHT)))
            {
                return true;
            }
        }
	}
	return false;
}

void CaveSystem::render(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer *gRenderer)
{
    if(ceilSprite == nullptr){
        SDL_Texture* newText = nullptr;
        std::string fname = "sprites/stalagt1.png";
	    SDL_Surface* startSurf = IMG_Load(fname.c_str());
	    newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	    SDL_FreeSurface(startSurf);
        ceilSprite = newText;
        newText = nullptr;
        fname = "sprites/stalagm1.png";
	    startSurf = IMG_Load(fname.c_str());
	    newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	    SDL_FreeSurface(startSurf);
        floorSprite = newText;
    }
    int i, j;
    bool isStillShowing = false;
    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            CaveBlock *curr_block = CaveSystem::cave_system[i][j];

            if (curr_block->CAVE_BLOCK_REL_X < SCREEN_WIDTH && curr_block->CAVE_BLOCK_REL_Y < SCREEN_HEIGHT && curr_block->enabled == 1)
            {
                SDL_Rect fillRect = {curr_block->CAVE_BLOCK_REL_X, curr_block->CAVE_BLOCK_REL_Y, CaveBlock::CAVE_BLOCK_WIDTH, CaveBlock::CAVE_BLOCK_HEIGHT};
                if(i != 0 && CaveSystem::cave_system[i-1][j]->enabled == 0){
                    curr_block->isPointy = 1;
                    SDL_RenderCopyEx(gRenderer, floorSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
                }
                else if(i != CaveSystem::CAVE_SYSTEM_HEIGHT - 1 && CaveSystem::cave_system[i+1][j]->enabled == 0){
                    curr_block->isPointy = 1;
                    SDL_RenderCopyEx(gRenderer, ceilSprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
                }
                else{
                SDL_SetRenderDrawColor(gRenderer, 0x7F, 0x33, 0x00, 0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect);
                }   
            }

            if (curr_block->CAVE_BLOCK_REL_X < SCREEN_WIDTH + 5 && curr_block->CAVE_BLOCK_REL_X >= 0 && curr_block->CAVE_BLOCK_REL_Y < SCREEN_HEIGHT)
                isStillShowing = true;
        }

    if(!isStillShowing)
    {
        isEnabled = false;
        this->~CaveSystem();
        // printf("CAVE SYSTEM DONE SHOWING!\n");
    }
}

int CaveSystem::getStartX()
{
	return CAVE_START_ABS_X;
}

int CaveSystem::getEndX()
{
	return CAVE_END_ABS_X;
}
