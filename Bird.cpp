#include "Bird.h"
using namespace std;



Bird::Bird(SDL_Renderer* ren)
{
	text_ = CommonFunc::LoadImage("img.png", ren);
	delay = 0;
	src_.h = det_.h = 24;
	src_.w = det_.w = 34;
	src_.x = 295; src_.y = 118; // toa do trong img
	det_.x = 75; y_ = det_.y = SCREEN_HEIGHT / 2 - 25;
	speed_ = 0;
}

Bird::~Bird()
{
}
void Bird::Ready()
{
	delay++;
	if (delay==10)
	{
		if (src_.y < 118 + 24 * 2)
		{
			src_.y += 24;
		}
		else src_.y = 118;
		delay = 0;
	}
}
void Bird::Die(Mix_Chunk* roi, Mix_Chunk* die)
{
	src_.h = det_.h = 33;
	src_.w = det_.w = 24;
	src_.x = 407; src_.y = 183;
	if (det_.y<SCREEN_HEIGHT - det_.h - 112)
	{
		det_.y += max_speed;
		if( Mix_PlayChannel( -1, roi, 0 ) == -1 )
        {
            return;
        }
	}
	/*
	if (check == 0)
	if (det_.y>=SCREEN_HEIGHT - det_.h-112)
    {
        if( Mix_PlayChannel( -1, die, 0 ) == -1 )
        {
        }
        check = 1;
    }
    */
}

void Bird::Move(SDL_Event e, Mix_Chunk* vaycanh)
{
	delay++;
	if (delay>1)
	{
		det_.y += speed_;
		if (speed_<max_speed)
			speed_ += g;
		delay = 0;
	}
	SDL_PollEvent(&e);
	if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP))
	{
	    if( Mix_PlayChannel( -1, vaycanh, 0 ) == -1 )
        {
            cout << Mix_GetError() <<endl;
        }
		if (det_.y > 10)
		{
			y_ = det_.y;
			det_.y -= 10;
			speed_ = 0;
		}
	}
	if (det_.y<=y_+25)
	{
		src_.h = det_.h = 26;
		src_.w = det_.w = 32;
		src_.x = 335; src_.y = 166;
	}
	else if (det_.y<y_+75)
	{
		src_.h = det_.h = 27;
		src_.w = det_.w = 34;
		src_.x = 370; src_.y = 172;
	}
	else
	{
		src_.h = det_.h = 33;
		src_.w = det_.w = 24;
		src_.x = 407; src_.y = 183;
	}
}

void Bird::Draw(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, text_, &src_, &det_);
}

