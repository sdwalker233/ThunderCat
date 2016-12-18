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
	
	EffectSound miao = EffectSound("resources/music/miao.wav");
	miao.play();
	SDL_Surface *sur_background = IMG_Load("resources/pic/background2.jpg");
	tex_background = SDL_CreateTextureFromSurface(ren, sur_background);
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

void Game::welcome()
{
	SDL_Texture *startbutton;
	SDL_Surface *sur_startbutton = IMG_Load("resources/pic/startbutton.jpg");
	startbutton = SDL_CreateTextureFromSurface(ren, sur_startbutton);
	SDL_Rect rect_startbutton = { 390,290,147,168 };
	SDL_RenderCopy(ren, startbutton, NULL, &rect_startbutton);
	SDL_RenderPresent(ren);
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.x>=390&& event.button.x<=537&& event.button.y>=290&& event.button.y<=458)
						quit = true;
					break;
			}
		}
	}
}

void Game::createMonster(int m_number)
{
	monster_number = m_number;
	monsters.clear();
	for(int i = 0; i < monster_number; i++){
		Monster M;
		M.setRender(ren);
		monsters.push_back(M);
	}
}

void Game::run()
{
	welcome();
	show();
//chapter 1
//level 1
	createMonster(1);
	monsters[0].setStart(800, 100);
	monsters[0].setEnd(20, 100);
	monsters[0].setSpeed(3.0);
	stage();
//level 2
	createMonster(2);
	monsters[0].setStart(800, 100);
	monsters[0].setEnd(20, 100);
	monsters[0].setSpeed(4.0);
	monsters[1].setStart(800, 300);
	monsters[1].setEnd(20, 300);
	monsters[1].setSpeed(6.0);
	stage();
//leve 3
	createMonster(3);
	monsters[0].setStart(800, 100);
	monsters[0].setEnd(20, 100);
	monsters[0].setSpeed(4.0);
	monsters[1].setStart(800, 250);
	monsters[1].setEnd(20, 250);
	monsters[1].setSpeed(5.0);
	monsters[2].setStart(800, 400);
	monsters[2].setEnd(20, 400);
	monsters[2].setSpeed(6.0);
	stage();
	
//chapter 2
//level 1
	createMonster(1);
	monsters[0].setStart(800, 0);
	monsters[0].setEnd(350, 250);
	monsters[0].setSpeed(4.0);
	stage();
//level 2
	createMonster(2);
	monsters[0].setStart(0, 0);
	monsters[0].setEnd(350, 250);
	monsters[0].setSpeed(4.0);
	monsters[1].setStart(800, 600);
	monsters[1].setEnd(450, 320);
	monsters[1].setSpeed(4.0);
	stage();
//level3
	createMonster(4);
	monsters[0].setStart(0, 0);
	monsters[0].setEnd(350, 250);
	monsters[0].setSpeed(4.0);
	monsters[1].setStart(800, 600);
	monsters[1].setEnd(450, 320);
	monsters[1].setSpeed(4.0);
	monsters[2].setStart(800, 0);
	monsters[2].setEnd(350, 250);
	monsters[2].setSpeed(4.0);
	monsters[3].setStart(0, 600);
	monsters[3].setEnd(350, 420);
	monsters[3].setSpeed(4.0);
	stage();
}

void Game::stage()
{
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
					tra.clear();
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
						//tra.recognize();
						//tra.show();
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if(mouse){
						x = event.button.x;
						y = event.button.y;
						mouse = false;
						//printf("up: %d, %d\n", x, y);
						
						int t = tra.recognize();
						//cout<<t<<endl;
						for(int i = 0; i < monster_number; i++)
							if(monsters[i].isDead() == false){
								monsters[i].deleteLabel(t);
								if(monsters[i].isDead()) score.add(100);
							}
						
						//cout<<"life is "<<life.getLife()<<endl;
						//cout<<"score is "<<score.getScore()<<endl;
					}
					break;
			}
		}
		int outnum = 0;
		for(int i = 0; i < monster_number; i++){
			if(monsters[i].isOut()) outnum++;
			else{
				if(monsters[i].isDead()) monsters[i].retreat();
				if(monsters[i].isReachEnd()) life.decrease();
				if(monsters[i].isReachStart()){}
			}
		}
		if(outnum == monster_number) quit = true;
		
		show();
		if(SDL_GetTicks()-_FPS_Timer<FPS){
			SDL_Delay(FPS-SDL_GetTicks()+_FPS_Timer);
		}
		_FPS_Timer=SDL_GetTicks();
	}
}

