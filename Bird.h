#pragma once
#include"CommonFunc.h"

const int g = 1;
const int max_speed = 10;
class Bird
{
public:
	Bird(SDL_Renderer* ren);
	~Bird();

	void Ready();
	void Die(Mix_Chunk* roi, Mix_Chunk* die);
	void Move(SDL_Event e, Mix_Chunk* vaycanh);
	SDL_Rect Get_det() const { return det_; }
	void Draw(SDL_Renderer* ren);
private:
	SDL_Texture* text_;
	SDL_Rect src_, det_;
	int speed_;
	int y_;
	int delay;
	bool check;
};
