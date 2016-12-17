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
	srand( (unsigned)time( NULL ) );
	win = SDL_CreateWindow("A Simple Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	tra.setRender(ren);
	life.setRender(ren);
	score.setRender(ren);
	monster_number = 2;
	for(int i = 0; i < monster_number; i++){
		Monster M;
		M.setRender(ren);
		monsters.push_back(M);
	}
	monsters[0].setSpeed(2.0);
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
	for(int i = 0; i < monster_number; i++){
		monsters[i].move();
		monsters[i].show();
		SDL_RenderCopy(ren, monsters[i].getTexture(), NULL, &FULL_RECT);
	}
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
	const Uint32 FPS=1000/30;//30 is fps
	Uint32 _FPS_Timer = 0;
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
						tra.recognize();
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
						
						int t = tra.recognize();
						cout<<t<<endl;
						for(int i = 0; i < monster_number; i++){
							monsters[i].deleteLabel(t);
							if(monsters[i].isDead()) monsters[i].setSpeed(-4.0);
						}
						
						tra.clear();
						
						//cout<<"life is "<<life.getLife()<<endl;
						//cout<<"score is "<<score.getScore()<<endl;
					}
					break;
			}
		}
		show();
		if(SDL_GetTicks()-_FPS_Timer<FPS){
			SDL_Delay(FPS-SDL_GetTicks()+_FPS_Timer);
		}
		_FPS_Timer=SDL_GetTicks();
	}
}
