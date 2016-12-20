//
//  status.cpp
//  SDL_game
//
//  Created by shad0w_walker on 2016/12/15.
//  Copyright © 2016年 GKP. All rights reserved.
//

#include "status.hpp"

//*******************************
//class Life

Life::Life()
{
	count = MAX_LIFE;
	lifeSurface1 = IMG_Load("resources/pic/life1.png");
	lifeSurface2 = IMG_Load("resources/pic/life2.png");
}

void Life::increase()
{
	count++;
	if(count > MAX_LIFE) count = MAX_LIFE;
}

void Life::decrease()
{
	count--;
	if(count < 0) count = 0;
}

int Life::getLife()
{
	return count;
}

void Life::show()
{
	clearSurface();
	SDL_Rect rect = {0, 0, 50, 50};
	for(int i = 0; i < count; i++){
		rect.x = 50*i;
		addSurface(lifeSurface1, &rect);
	}
	for(int i = count; i < MAX_LIFE; i++){
		rect.x = 50*i;
		addSurface(lifeSurface2, &rect);
	}
	finishSurface();
}

//*******************************


//*******************************
//class Score

Score::Score()
{
	score = 0;
	font = TTF_OpenFont("resources/font/nekoparo.ttf", 50);
	if(font == nullptr) cout<<"font not found"<<endl;
}

void Score::add(int _score)
{
	score += _score;
}

int Score::getScore()
{
	return score;
}

void Score::show()
{
	stringstream stream;
	string text;
	stream << score;
	stream >> text;
	while(text.length() < 8) text.insert(0, "0");
	//cout<<text<<endl;
	SDL_Surface *_sur = TTF_RenderText_Blended(font, text.c_str(), BLACK);
	SDL_Rect rect = {550, -7, 100, 20};
	clearSurface();
	addSurface(_sur, &rect);
	finishSurface();
	SDL_FreeSurface(_sur);
}

/*Score::~Score()
{
	TTF_CloseFont(font);
}*/
//*******************************


//*******************************
//class Score

Lightning::Lightning()
{
	num = 0;
	lightningSurface1 = IMG_Load("resources/pic/lightning1.png");
	//lightningSurface2 = IMG_Load("resources/pic/lightning2.png");
}

int Lightning::getNum()
{
	return num;
}

void Lightning::increase()
{
	num++;
	if(num>MAX_LIGHTNING) num = MAX_LIGHTNING;
}

void Lightning::decrease()
{
	num--;
	if(num<0) num = 0;
}

void Lightning::show()
{
	clearSurface();
	SDL_Rect rect = {270, 0, 50, 50};
	for(int i = 0; i < num; i++){
		rect.x += 50;
		addSurface(lightningSurface1, &rect);
	}
	/*for(int i = num; i < MAX_LIGHTNING; i++){
		rect.x += 50;
		addSurface(lightningSurface2, &rect);
	}*/
	finishSurface();
}

//*******************************
