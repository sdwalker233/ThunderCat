//
//  game.cpp
//  SDL_game
//
//  Created by shad0w_walker on 2016/12/14.
//  Copyright © 2016年 GKP. All rights reserved.
//

#include "game.hpp"
#include "mix_sound.hpp"

Game::Game()
{
	win = SDL_CreateWindow("A Simple Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	tra.setRender(ren);
	life.setRender(ren);
	score.setRender(ren);
}

Game::~Game()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
}

void Game::show()
{
	SDL_RenderCopy(ren, tex_background, NULL, &FULL_RECT);
	life.show();
	SDL_RenderCopy(ren, life.getTexture(), NULL, &FULL_RECT);
	tra.show();
	SDL_RenderCopy(ren, tra.getTexture(), NULL, &FULL_RECT);
	score.show();
	SDL_RenderCopy(ren, score.getTexture(), NULL, &FULL_RECT);
	SDL_RenderPresent(ren);
}

void Game::run()
{
	EffectSound miao = EffectSound("resources/music/miao.wav");
	miao.play();
	SDL_Surface *sur_background = IMG_Load("resources/pic/background2.jpg");
	tex_background = SDL_CreateTextureFromSurface(ren, sur_background);
	
	show();
	
	int f = 0;
	const Uint32 FPS=1000/30;//30为限制的帧速
	Uint32 _FPS_Timer;
	bool quit = false;
	bool mouse = false;
	SDL_Point pos;
	int x, y;
	while (!quit){
		while (SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					x = event.button.x;
					y = event.button.y;
					mouse = true;
					//printf("down: %d, %d\n", x, y);
					pos.x = x;
					pos.y = y;
					tra.addPostion(pos);
					//tra.show();
					break;
				case SDL_MOUSEMOTION:
					if(mouse){
						x = event.motion.x;
						y = event.motion.y;
						//printf("move: %d, %d\n", x, y);
						pos.x = x;
						pos.y = y;
						tra.addPostion(pos);
						//tra.show();
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if(mouse){
						x = event.button.x;
						y = event.button.y;
						mouse = false;
						//printf("up: %d, %d\n", x, y);
						if(f) life.increase();
						else life.decrease();
						f ^= 1;
						
						if(tra.recognize()) score.add(10);
						show();
						tra.clear();
						
						cout<<"life is "<<life.getLife()<<endl;
						cout<<"score is "<<score.getScore()<<endl;
					}
					break;
			}
		}
	}
	if(SDL_GetTicks()-_FPS_Timer<FPS){
		SDL_Delay(FPS-SDL_GetTicks()+_FPS_Timer);
	}
	_FPS_Timer=SDL_GetTicks();
}
