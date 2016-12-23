//
//  game.cpp
//  SDL_game
//
//  Created by shad0w_walker on 2016/12/14.
//  Copyright © 2016�?GKP. All rights reserved.
//
#include "game.hpp"

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
	pausebotton = IMG_LoadTexture(ren, "resources/pic/pausebutton.png");
	restartbotton = IMG_LoadTexture(ren, "resources/pic/restartbutton.png");
	SDL_Surface *pausesur = IMG_Load("resources/pic/pause.png");
	SDL_SetSurfaceBlendMode(pausesur,SDL_BLENDMODE_BLEND);
	SDL_SetSurfaceAlphaMod(pausesur,150);
	pausetex = SDL_CreateTextureFromSurface(ren, pausesur);
	SDL_FreeSurface(pausesur);
	wintex = pausetex;
	losetex = pausetex;
	
	
	ingame = false;
	quit = false;
	EffectSound miao = EffectSound("resources/music/miao.wav");
	die = new EffectSound("resources/music/die.wav");
	miao.play();
}

Game::~Game()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
}

void Game::show(SDL_Texture *extra_tex = NULL, const SDL_Rect *extra_rect = &FULL_RECT)
{
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, bgTexture, NULL, &FULL_RECT);
	life.show();
	SDL_RenderCopy(ren, life.getTexture(), NULL, &FULL_RECT);
	for(int i = 0; i < monster_number; i++){
		if(life.getLife()) monsters[i].move();
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
	if(ingame){
		SDL_Rect rect = {windowWidth-50, windowHeight-50, 50, 50};
		SDL_RenderCopy(ren, pausebotton, NULL, &rect);
		rect.x-=50;
		SDL_RenderCopy(ren, restartbotton, NULL, &rect);
	}
	SDL_RenderCopy(ren, extra_tex, NULL, extra_rect);
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

/*
 1: normal
 2: endless
 3: exit
 */

int Game::welcome()
{
	SDL_Texture *roundmode,*endlessmode,*exit;
	SDL_Surface *sur_roundmode = IMG_Load("resources/pic/roundmode.png"),
	*sur_endlessmode = IMG_Load("resources/pic/endlessmode.png"),
	*sur_exit = IMG_Load("resources/pic/exit.png");
	roundmode = SDL_CreateTextureFromSurface(ren, sur_roundmode);
	endlessmode = SDL_CreateTextureFromSurface(ren, sur_endlessmode);
	exit = SDL_CreateTextureFromSurface(ren, sur_exit);
	
	SDL_Rect rect_roundmode = { 527,200,187,85 };
	SDL_Rect rect_endlessmode = { 527,300,187,85 };
	SDL_Rect rect_exit= { 527,400,187,85 };
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
					if (event.button.x >= 527 && event.button.x <= 714 && event.button.y >= 200 && event.button.y <= 285)
						return 1;
					if (event.button.x >= 527 && event.button.x <= 714 && event.button.y >= 300 && event.button.y <= 385)
						return 2;
					if (event.button.x >= 527 && event.button.x <= 714 && event.button.y >= 400 && event.button.y <= 485)
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
	//monsters.resize(m_number);
	for(int i = 0; i < monster_number; i++){
		Monster M;
		M.setRender(ren);
		monsters.push_back(M);
	}
}

void Game::run()
{
	while(!quit){
		scoll("resources/pic/bg/menu.png");
		int op = welcome();
		ingame = true;
		life.set(MAX_LIFE);
		lightning.set(0);
		score.set(0);
		if(op == 1) normal();
		else if(op == 2) endless();
		else break;
		ingame = false;
	}
}

void Game::normal()
{
	lightning.increase();
	//chapter 1
	if(quit) return;
	scoll("resources/pic/bg/normal1.png");
	hero.setPosition(0, 400);
	hero.setStatus(7);
	//level 1
	createMonster(1);
	monsters[0].setStart(800, 100);
	monsters[0].setEnd(20, 100);
	monsters[0].setSpeed(3.0);
	if(stage()) return;
	//level 2
	createMonster(2);
	monsters[0].setStart(800, 100);
	monsters[0].setEnd(20, 100);
	monsters[0].setSpeed(4.0);
	monsters[1].setStart(800, 300);
	monsters[1].setEnd(20, 300);
	monsters[1].setSpeed(6.0);
	if(stage()) return;
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
	if(stage()) return;
	lightning.increase();
	//win_scene();
	if(quit) return;
	
	//chapter 2
	scoll("resources/pic/bg/normal2.png");
	hero.setPosition(300, 240);
	hero.setStatus(7);
	//level 1
	createMonster(1);
	monsters[0].setStart(800, 0);
	monsters[0].setEnd(300, 250);
	monsters[0].setSpeed(6.0);
	if(stage()) return;
	//level 2
	createMonster(2);
	monsters[0].setStart(0, 0);
	monsters[0].setEnd(300, 250);
	monsters[0].setSpeed(5.0);
	monsters[1].setStart(800, 600);
	monsters[1].setEnd(400, 320);
	monsters[1].setSpeed(5.0);
	if(stage()) return;
	//level3
	createMonster(4);
	monsters[0].setStart(0, 0);
	monsters[0].setEnd(300, 250);
	monsters[0].setSpeed(6.0);
	monsters[1].setStart(800, 600);
	monsters[1].setEnd(400, 320);
	monsters[1].setSpeed(5.0);
	monsters[2].setStart(800, 0);
	monsters[2].setEnd(300, 250);
	monsters[2].setSpeed(5.0);
	monsters[3].setStart(0, 600);
	monsters[3].setEnd(300, 420);
	monsters[3].setSpeed(6.0);
	if(stage()) return;
	lightning.increase();
	//win_scene();
	
	//chapter 3
	scoll("resources/pic/bg/normal3.png");
	hero.setPosition(350,450);
	hero.setStatus(7);
	//level 1
	createMonster(1);
	monsters[0].setStart(800,590);
	monsters[0].setEnd(450, 460);
	monsters[0].setSpeed(4.0);
	if(stage()) return;
	//level 2
	createMonster(3);
	monsters[0].setStart(0, 580);
	monsters[0].setEnd(300, 500);
	monsters[0].setSpeed(3.0);
	monsters[1].setStart(400, 0);
	monsters[1].setEnd(400, 400);
	monsters[1].setSpeed(6.0);
	monsters[2].setStart(800,590);
	monsters[2].setEnd(450, 460);
	monsters[2].setSpeed(4.0);
	if(stage()) return;
	//level3
	createMonster(5);
	monsters[0].setStart(0, 540);
	monsters[0].setEnd(300, 500);
	monsters[0].setSpeed(3.0);
	monsters[1].setStart(400, 0);
	monsters[1].setEnd(400, 400);
	monsters[1].setSpeed(7.5);
	monsters[2].setStart(800,580);
	monsters[2].setEnd(450, 460);
	monsters[2].setSpeed(3.0);
	monsters[3].setStart(0,0);
	monsters[3].setEnd(320,400);
	monsters[3].setSpeed(6.0);
	monsters[4].setStart(700,0);
	monsters[4].setEnd(410, 420);
	monsters[4].setSpeed(6.0);
	if(stage()) return;
	lightning.increase();
	////win_scene();
	
	//chapter 4
	scoll("resources/pic/bg/normal4.png");
	hero.setPosition(0, 400);
	hero.setStatus(7);
	//level 1
	createMonster(1);
	monsters[0].setStart(800, 0);
	monsters[0].setEnd(20, 350);
	monsters[0].setSpeed(10.0);
	if(stage()) return;
	//level 2
	createMonster(2);
	monsters[0].setStart(0, 0);
	monsters[0].setEnd(20, 350);
	monsters[0].setSpeed(8.0);
	monsters[1].setStart(750, 560);
	monsters[1].setEnd(20, 420);
	monsters[1].setSpeed(8.0);
	if(stage()) return;
	//leve 3
	createMonster(3);
	monsters[0].setStart(0, 0);
	monsters[0].setEnd(20, 350);
	monsters[0].setSpeed(8.0);
	monsters[1].setStart(750, 560);
	monsters[1].setEnd(20, 420);
	monsters[1].setSpeed(8.0);
	monsters[2].setStart(800, 0);
	monsters[2].setEnd(20, 350);
	monsters[2].setSpeed(10.0);
	if(stage()) return;
	lightning.increase();
	win_scene();
	if(quit) return;
	
	//chapter 5
	scoll("resources/pic/bg/normal5.png");
	hero.setPosition(0, 400);
	hero.setStatus(7);
	//level 1
	createMonster(5);
	monsters[0].setStart(0, 0);
	monsters[0].setEnd(20, 300);
	monsters[0].setSpeed(4.0);
	monsters[1].setStart(400, 0);
	monsters[1].setEnd(100, 300);
	monsters[1].setSpeed(5.0);
	monsters[2].setStart(800, 0);
	monsters[2].setEnd(100, 350);
	monsters[2].setSpeed(6.0);
	monsters[3].setStart(800,300);
	monsters[3].setEnd(100,360);
	monsters[3].setSpeed(6.0);
	monsters[4].setStart(700,500);
	monsters[4].setEnd(100, 420);
	monsters[4].setSpeed(6.0);
	if(stage()) return;
	//level 2
	hero.setPosition(350, 300);
	createMonster(8);
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
	monsters[4].setStart(0,300);
	monsters[4].setEnd(300, 300);
	monsters[4].setSpeed(4.0);
	monsters[5].setStart(400, 0);
	monsters[5].setEnd(390, 300);
	monsters[5].setSpeed(4.0);
	monsters[6].setStart(400, 600);
	monsters[6].setEnd(390, 400);
	monsters[6].setSpeed(4.0);
	monsters[7].setStart(800, 300);
	monsters[7].setEnd(390, 300);
	monsters[7].setSpeed(4.0);
	if(stage()) return;
	
	lightning.increase();
	win_scene();
	if(quit) return;
}

void Game::endless()
{
	// endless model
	scoll("resources/pic/bg/endless1.png");
	hero.setPosition(350, 240);
	hero.setStatus(7);
	int monstercount = 1, stageNum = 0;
	while (quit == false)
	{
		stageNum ++;
		if((stageNum+1)%3==0)
			monstercount += 1;
		if(monstercount > 10) monstercount = 10;
		createMonster(monstercount);
		double startx, starty;
		for (int i = 0; i < monstercount; i++)
		{
			startx = rand() % 800;
			starty = rand() % 600;
			if (startx <180 && starty < 90) {
				monsters[i].setStart(startx, starty);
				monsters[i].setEnd(350, 250);
				monsters[i].setSpeed(2.0);
			}
			else if (startx > 520 && starty < 90) {
				monsters[i].setStart(startx, starty);
				monsters[i].setEnd(350, 250);
				monsters[i].setSpeed(2.0);
			}
			else if (startx < 180 && starty > 390) {
				monsters[i].setStart(startx, starty);
				monsters[i].setEnd(350, 420);
				monsters[i].setSpeed(2.0);
			}
			else if (startx > 520 && starty > 390) {
				monsters[i].setStart(startx, starty);
				monsters[i].setEnd(450, 320);
				monsters[i].setSpeed(2.0);
			}
			else
			{	if(i>0)
				i--;
			}
		}
		if(stageNum>=3)
			monsters[monstercount/4].setSpeed(4.0);
		if(stageNum>=6)
			monsters[monstercount / 2].setSpeed(5.0);
		if(stageNum>=10)
			monsters[monstercount*3 / 4].setSpeed(6.0);
		if (stageNum >= 14)
			monsters[monstercount * 3 / 8].setSpeed(7.0);
		if (stageNum >= 20)
			monsters[monstercount * 5/ 8].setSpeed(8.0);
		
		if(stage()) return;
		if(stageNum%3==0)
			lightning.increase();
	}
}

void Game::guide()
{
	
}

int Game::stage()
{
	if(quit) return 1;
	const Uint32 FPS=1000/20;//30 is fps
	Uint32 _FPS_Timer = 0;
	bool mouse = false;
	SDL_Point pos;
	int x, y;
	bool q = false;
	while (!q){
		while (SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					q = true;
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
						if(x>=windowWidth-50 && y>=windowHeight-50){
							pause_scene();
							break;
						}
						if(x>=windowWidth-100 && y>=windowHeight-50){
							q = true;
							return 1;
						}
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
			lose_scene();
			return 1;
		}
		show();
		if(SDL_GetTicks()-_FPS_Timer<FPS){
			SDL_Delay(FPS-SDL_GetTicks()+_FPS_Timer);
		}
		_FPS_Timer=SDL_GetTicks();
	}
	return 0;
}

void Game::lose_scene()
{
	hero.setStatus(8);
	die->play();
	for(int i=1;i<=40;i++){
		show();
		SDL_Delay(30);
	}
	SDL_Rect rect = {0, 600, windowWidth, windowHeight};
	for(int i = windowHeight; i >= 0; i -= 15){
		rect.y = i;
		show(losetex, &rect);
		SDL_Delay(5);
	}
	wait_for_click();
}

void Game::win_scene()
{
	hero.setStatus(10);
	for(int i=1;i<=50;i++){
		show();
		SDL_Delay(30);
	}
	
	SDL_Rect rect = {0, 600, windowWidth, windowHeight};
	for(int i = windowHeight; i >= 0; i -= 15){
		rect.y = i;
		show(wintex, &rect);
		SDL_Delay(5);
	}
	wait_for_click();
	hero.setStatus(0);
}

void Game::pause_scene()
{
	show(pausetex);
	wait_for_click();
}

void Game::wait_for_click()
{
	bool q = false;
	while (!q) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					q = true;
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					q = true;
					break;
			}
		}
	}
}
