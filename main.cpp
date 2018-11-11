#include"Water_pipe.h"
#include"Bird.h"
#include<stdlib.h>
#include<ctime>
#include<fstream>

using namespace std;

bool QUIT(SDL_Event even);
int main(int argv, char* argo[])
{
	int HI_Score;
	fstream f;
	f.open("Score.txt", ios::in);
	f >> HI_Score;
	f.close();

	int Score = 0;
	// Khoi tao Window
	////////////////////////////////////////////////////////////////////////////////////////
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event even;
	bool gameover = false;
	bool ready = false;
	////////////////////////////////////////////////////////////////////////////////////////
	SDL_Texture* text = CommonFunc::LoadImage("img.png", renderer);
	//=BGR
	SDL_Rect rect,rect1,rect11;
	rect.x = 0; rect.y = 0; rect.w = SCREEN_WIDTH; rect.h = SCREEN_HEIGHT; // det in anh
	rect1.h = 483 - 447; rect1.w = 868 - 561; rect1.x = 561; rect1.y = 447; //
	rect11.h = 483 - 460; rect11.w = 868 - 640; rect11.x = 0; rect11.y = 0; //
	//bird
	Bird bird(renderer);
	//=mat dat
	SDL_Rect src, det1, det2;
	src.x = 293; src.y = 0; src.h = det1.h = det2.h = 112; src.w = det1.w = det2.w = 308;
	det1.y = det2.y = SCREEN_HEIGHT - 112;
	det1.x = 0; det2.x = 306;
	//=tap-tap
	SDL_Rect srctap, dettap;
	srctap.x = 314; srctap.y = 292; srctap.w = dettap.w = 111; srctap.h = dettap.h = 139;
	dettap.x = (SCREEN_WIDTH - 70) / 2 + 20; dettap.y = (SCREEN_HEIGHT - 155) / 2 + 10;
	//=game over
	SDL_Rect srcg, detg;
	srcg.x = 565; srcg.y = 192; srcg.w = detg.w = 279; srcg.h = detg.h = 233;
	detg.x = (SCREEN_WIDTH - 279) / 2; detg.y = (SCREEN_HEIGHT - 233) / 2;
	//ong nuoc
	Water_pipe Water_pipe1(renderer), Water_pipe2(renderer);
	int x, y;
	srand(time(NULL));
	x = SCREEN_WIDTH + 100;
	y = 100 - 244 + rand() % (SCREEN_HEIGHT - 112 - 77 - 200);
	Water_pipe1.Set_det(x, y);
	x = Water_pipe1.Get_det1().x + SCREEN_WIDTH / 2 + 56 / 2;
	y = 100 - 244 + rand() % (SCREEN_HEIGHT - 112 - 77 - 200);
	Water_pipe2.Set_det(x, y);
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }
    Mix_Chunk* win = NULL;
    win = Mix_LoadWAV( "sound/win.wav" );
    Mix_Chunk* vaycanh = NULL;
    vaycanh = Mix_LoadWAV( "sound/wing.wav" );
    Mix_Chunk* vacham = NULL;
    vacham = Mix_LoadWAV( "sound/vacham.wav" );
    Mix_Chunk* roi = NULL, *die = NULL;
    roi = Mix_LoadWAV( "sound/roi.wav" );
    die = Mix_LoadWAV( "soudn/die.wav" );
    ////////////////////////////////////////////////////////////////////////////////////////
	//test

	////////////////////////////////////////////////////////////////////////////////////////
	while (true)
	{
		SDL_PollEvent(&even);

		//=bat dau
		while (!ready)
		{
			SDL_PollEvent(&even);
			det1.x = 0;
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, text, &rect, NULL);
			bird.Draw(renderer);
			SDL_RenderCopy(renderer, text, &src, &det1);
			SDL_RenderCopy(renderer, text, &srctap, &dettap);

			bird.Ready();
			SDL_RenderPresent(renderer);
			if (even.type == SDL_KEYDOWN && even.key.keysym.sym == SDLK_SPACE)
				ready = true;
			if (QUIT(even))
				goto quit;
			SDL_Delay(15);
		}
		//=xu ly


		bird.Move(even, vaycanh);
		Water_pipe1.Move();//cot
		Water_pipe2.Move();
		// ong nuoc 56x244
		if (Water_pipe1.Get_det1().x<-Water_pipe1.Get_det1().w)
		{
			x = Water_pipe2.Get_det1().x + SCREEN_WIDTH / 2 + 56 / 2;
			y = 100 - 244 + rand() % (SCREEN_HEIGHT - 389);
			Water_pipe1.Set_det(x, y);
		}
		if (Water_pipe2.Get_det1().x<-Water_pipe2.Get_det1().w)
		{
			x = Water_pipe1.Get_det1().x + SCREEN_WIDTH / 2 + 56 / 2;
			y = 100 - 244 + rand() % (SCREEN_HEIGHT - 389tao );
			Water_pipe2.Set_det(x, y);
		}
		det1.x--; det2.x = det1.x + 306;//mat dat
		if (det2.x == 0)
		{
			det1.x = 0; det2.x = 306;
		}
		//tang diem
		if (bird.Get_det().x == Water_pipe1.Get_det1().x + 46 || bird.Get_det().x == Water_pipe2.Get_det1().x + 46)
		{
		    if( Mix_PlayChannel( -1, win, 0 ) == -1 )
            {
                return 0;
            }
			Score++;
		}

		//=va cham
		if (CommonFunc::CheckCollision(bird.Get_det(), Water_pipe1.Get_det1(),vacham) ||
			CommonFunc::CheckCollision(bird.Get_det(), Water_pipe2.Get_det1(),vacham))
		{
			gameover = true;
		}

		//hien thi
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, text, &rect, NULL);//bgr
		bird.Draw(renderer);
		Water_pipe1.Draw(renderer);//cot
		Water_pipe2.Draw(renderer);

		SDL_RenderCopy(renderer, text, &src, &det1);//nen dat
		SDL_RenderCopy(renderer, text, &src, &det2);
		CommonFunc::Print_score(Score, renderer);
		SDL_RenderPresent(renderer);
		//ket thuc
		while (gameover)
		{
			if (Score > HI_Score) // ionic
			{
				HI_Score = Score;
				fstream f;
				f.open("Score.txt", ios::out);
				f.clear();
				f << HI_Score;
				f.close();
			}
			SDL_PollEvent(&even);
			det1.x = 0;
			bird.Die(roi, die);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, text, &rect, NULL);
			bird.Draw(renderer);
			Water_pipe1.Draw(renderer);//cot
			Water_pipe2.Draw(renderer);
			SDL_RenderCopy(renderer, text, &src, &det1);
			SDL_RenderCopy(renderer, text, &srcg, &detg);
			SDL_RenderCopy(renderer, text, &rect1, &rect11);
			///////////////////////////
			CommonFunc::Print_score_HI(Score, HI_Score, renderer);
			SDL_RenderPresent(renderer);
			if (even.type == SDL_MOUSEBUTTONDOWN &&
				even.motion.x > 12 && even.motion.x < SCREEN_WIDTH - 12
				&& even.motion.y > 307 && even.motion.y < 367)
			{
				gameover = false;
				ready = false;
				bird = Bird(renderer);
				x = SCREEN_WIDTH + 100;
				y = 100 - 244 + rand() % (SCREEN_HEIGHT - 112 - 77 - 200);
				Water_pipe1.Set_det(x, y);
				x = Water_pipe1.Get_det1().x + SCREEN_WIDTH / 2 + 56 / 2;
				y = 100 - 244 + rand() % (SCREEN_HEIGHT - 112 - 77 - 200);
				Water_pipe2.Set_det(x, y);
				Score = 0;
			}
			SDL_Delay(20);
			if (QUIT(even))
				goto quit;
		}
		if (QUIT(even))
			goto quit;
		SDL_Delay(20);
	}
quit:SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
bool QUIT(SDL_Event even)
{
	if (even.type == SDL_QUIT)
		return true;
	if (even.type == SDL_KEYDOWN && even.key.keysym.sym == SDLK_ESCAPE)
		return true;
	return false;
}
