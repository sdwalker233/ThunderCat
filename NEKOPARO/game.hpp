//
//  game.hpp
//  NEKOPARO
//
//  Created by shad0w_walker on 2016/12/14.
//  Copyright © 2016年 GKP. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include "utility.h"
#include "trajectory.hpp"
#include "status.hpp"
#include "monster.h"
#include "hero.hpp"
#include "mix_sound.hpp"

class Game{
private:
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Event event;
	Trajectory tra, guidetra;
	Life life;
	Score score;
	Lightning lightning;
	vector<Monster> monsters;
	Hero hero;
	int monster_number;
	SDL_Texture *bgTexture, *pausebotton, *restartbotton, *pausetex, *wintex, *losetex;
	bool ingame;
	bool quit;
	EffectSound *die, *win1, *win2, *endlessend, *lose, *start, *click;
	int comb;
	bool guidemode;
	SDL_Point lastguide;
	SDL_Texture *guidetext;
public:
	Game();
	~Game();
	void run();
	int stage();
	void defaultRender();
	void show(SDL_Texture *extra_tex, const SDL_Rect *extra_rect);
	int welcome();
	void createMonster(int m_number);
	void scoll(const string& bgName);
	void normal();
	void endless();
	void lose_scene();
	void win_scene();
	void pause_scene();
	void wait_for_click();
	void guide();
};

#endif /* game_hpp */
