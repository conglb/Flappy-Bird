#pragma once
#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

const int SCREEN_WIDTH = 288;
const int SCREEN_HEIGHT = 512;
const int speed_map = 1;

namespace CommonFunc
{

	//load anh len renderer
	SDL_Texture* LoadImage(const char* file, SDL_Renderer* ren);
	//kiem tra va cham
	bool CheckCollision(const SDL_Rect& bird, const SDL_Rect& Water_pipe,Mix_Chunk* vacham);
	//in diem
	void Print_score(int score, SDL_Renderer* ren);
	void Print_score_HI(int score, int hight_score, SDL_Renderer* ren);
}

#endif // !COMMON_FUNC_H_
