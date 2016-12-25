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
	hurt = new EffectSound("resources/music/hurt.wav");
	cured = new EffectSound("resources/music/cured.wav");
}

void Life::increase()
{
	if(count < MAX_LIFE){
		count++;
		cured->play();
	}
}

void Life::decrease()
{
	if(count > 0){
		count--;
		hurt->play();
	}
}

int Life::getLife()
{
	return count;
}

void Life::set(int x)
{
	count = x;
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
	col = BLACK;
	font = TTF_OpenFont("resources/font/nekoparo.ttf", 50);
	if(font == nullptr) cout<<"font not found"<<endl;
}

void Score::setColor(SDL_Color _col)
{
	col = _col;
}

void Score::add(int _score)
{
	score += _score;
}

int Score::getScore()
{
	return score;
}

void Score::set(int x)
{
	score = x;
}

void Score::show()
{
	stringstream stream;
	string text;
	stream << score;
	stream >> text;
	while(text.length() < 8) text.insert(0, "0");
	//cout<<text<<endl;
	SDL_Surface *_sur = TTF_RenderText_Blended(font, text.c_str(), col);
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
	lightningSurface2 = IMG_Load("resources/pic/lightning2.png");
	add = new EffectSound("resources/music/addlightning.wav");
}

int Lightning::getNum()
{
	return num;
}

void Lightning::set(int x)
{
	num = x;
}

void Lightning::increase()
{
	if(num < MAX_LIGHTNING){
		num++;
		add->play();
	}
}

void Lightning::decrease()
{
	if(num > 0){
		num--;
	}
}

void Lightning::show()
{
	clearSurface();
	SDL_Rect rect = {270, 0, 50, 50};
	for(int i = 0; i < num; i++){
		rect.x += 50;
		addSurface(lightningSurface1, &rect);
	}
	for(int i = num; i < MAX_LIGHTNING; i++){
		rect.x += 50;
		addSurface(lightningSurface2, &rect);
	}
	finishSurface();
}

//*******************************
