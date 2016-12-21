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
	if(ren == nullptr) ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
	tra.setRender(ren);
	life.setRender(ren);
	score.setRender(ren);
	lightning.setRender(ren);
	hero.setRender(ren);
	bgTexture = nullptr;
	
	quit = false;
	EffectSound miao = EffectSound("resources/music/miao.wav");
	miao.play();
}

Game::~Game()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
}

void Game::show()
{
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, bgTexture, NULL, &FULL_RECT);
	life.show();
	SDL_RenderCopy(ren, life.getTexture(), NULL, &FULL_RECT);
	for(int i = 0; i < monster_number; i++){
		monsters[i].move();
		monsters[i].show();
		SDL_RenderCopy(ren, monsters[i].getTexture(), NULL, &FULL_RECT);
	}
	hero.show();
	SDL_RenderCopy(ren, hero.getTexture(), NULL, &FULL_RECT);
	tra.show();
	SDL_RenderCopy(ren, tra.getTexture(), NULL, &FULL_RECT);
	lightning.show();
	SDL_RenderCopy(ren, lightning.getTexture(), NULL, &FULL_RECT);
	score.show();
	SDL_RenderCopy(ren, score.getTexture(), NULL, &FULL_RECT);
	SDL_RenderPresent(ren);
}

void Game::scoll(const string &bgName)
{
	SDL_Texture *last_bg = bgTexture;
	SDL_Surface *bgSurface = IMG_Load(bgName.c_str());
	bgTexture = SDL_CreateTextureFromSurface(ren, bgSurface);
	SDL_Rect rect = {0, 0, windowWidth, windowHeight};
	for(int i = windowWidth; i >= 0; i -= 7){
		//SDL_RenderClear(ren);
		SDL_RenderCopy(ren, last_bg, NULL, &FULL_RECT);
		rect.x = i;
		SDL_RenderCopy(ren, bgTexture, NULL, &rect);
		SDL_RenderPresent(ren);
		SDL_Delay(5);
	}
	SDL_DestroyTexture(last_bg);
}

/*返回1：关卡模式
 返回2：无尽模式
 返回3：退出*/
int Game::welcome()
{
	SDL_Texture *roundmode,*endlessmode,*exit;
	SDL_Surface *sur_roundmode = IMG_Load("resources/pic/roundmode.png"),
	*sur_endlessmode = IMG_Load("resources/pic/endlessmode.png"),
	*sur_exit = IMG_Load("resources/pic/exit.png");
	roundmode = SDL_CreateTextureFromSurface(ren, sur_roundmode);
	endlessmode = SDL_CreateTextureFromSurface(ren, sur_endlessmode);
	exit = SDL_CreateTextureFromSurface(ren, sur_exit);
	
	SDL_Rect rect_roundmode = { 307,150,187,85 };
	SDL_Rect rect_endlessmode = { 307,250,187,85 };
	SDL_Rect rect_exit= { 307,350,187,85 };
	SDL_RenderCopy(ren, bgTexture, NULL, &FULL_RECT);
	SDL_RenderCopy(ren, roundmode, NULL, &rect_roundmode);
	SDL_RenderCopy(ren, endlessmode, NULL, &rect_endlessmode);
	SDL_RenderCopy(ren, exit, NULL, &rect_exit);
	SDL_RenderPresent(ren);
	bool q = false;
	while (!q) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					q = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.x >= 307 && event.button.x <= 494 && event.button.y >= 150 && event.button.y <= 235)
						return 1;
					if (event.button.x >= 307 && event.button.x <= 494 && event.button.y >= 250 && event.button.y <= 335)
						return 2;
					if (event.button.x >= 307 && event.button.x <= 494 && event.button.y >= 350 && event.button.y <= 435)
						return 3;
					
					break;
			}
		}
	}
	return 3;
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
	scoll("resources/pic/background1.jpg");
	if(welcome()==1) normal();
	else if(welcome()==2) endless();

}

void Game::normal()
{
	lightning.increase();
	//chapter 1
	scoll("resources/pic/background2.jpg");
	hero.setPosition(0, 240);
	hero.setStatus(7);
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
	lightning.increase();
	
	//chapter 2
	scoll("resources/pic/background3.jpg");
	hero.setPosition(350, 240);
	hero.setStatus(7);
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
	lightning.increase();
}

void Game::endless()
{
	// endless model
	scoll("resources/pic/background3.jpg");
	hero.setPosition(350, 240);
	hero.setStatus(7);
	int monstercount = 0, stageNum = 0;
	while (quit == false)
	{
		stageNum ++;
		monstercount += 2;
		if(monstercount > 10) monstercount = 10;
		createMonster(monstercount);
		double startx, starty;
		for (int i = 0; i < monstercount; i++)
		{
			startx = rand() % 800;
			starty = rand() % 600;
			if (startx <200 & starty < 100) {
				monsters[i].setStart(startx, starty);
				monsters[i].setEnd(350, 250);
				monsters[i].setSpeed(4.0);
			}
			else if (startx > 500 & starty < 100) {
				monsters[i].setStart(startx, starty);
				monsters[i].setEnd(350, 250);
				monsters[i].setSpeed(4.0);
			}
			else if (startx < 200 & starty > 380) {
				monsters[i].setStart(startx, starty);
				monsters[i].setEnd(350, 420);
				monsters[i].setSpeed(4.0);
			}
			else if (startx > 500 & starty > 380) {
				monsters[i].setStart(startx, starty);
				monsters[i].setEnd(450, 320);
				monsters[i].setSpeed(4.0);
			}
			else
			{	if(i>0)
				i--;
			}
		}
		stage();
		if(stageNum%3==0)
			lightning.increase();
	}
}

void Game::stage()
{
	const Uint32 FPS=1000/20;//30 is fps
	Uint32 _FPS_Timer = 0;
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
						hero.setStatus(t);
						if(t == 6){
							if(lightning.getNum() == 0) break;
							lightning.decrease();
						}
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
				if(monsters[i].isReachEnd()){
					life.decrease();
					hero.setStatus(9);
				}
				if(monsters[i].isReachStart()){}
			}
		}
		if(outnum == monster_number) break;
		if(life.getLife() == 0){
			hero.setStatus(8);
			lose_scence();
			break;
		}
		show();
		if(SDL_GetTicks()-_FPS_Timer<FPS){
			SDL_Delay(FPS-SDL_GetTicks()+_FPS_Timer);
		}
		_FPS_Timer=SDL_GetTicks();
	}
}

void Game::lose_scence()
{
	while(1){
		show();
		SDL_Delay(20);
	}
}

void Game::win_scence()
{
	while(1){
		show();
		SDL_Delay(20);
	}
}
