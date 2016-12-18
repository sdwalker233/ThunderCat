//
//  game.hpp
//  SDL_game
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

class Game{
private:
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Event event;
	Trajectory tra;
	Life life;
	Score score;
	vector<Monster> monsters;
	int monster_number;
	SDL_Texture *tex_background;
public:
	Game();
	~Game();
	void run();
	void stage();
	void show();
	void welcome();
	void createMonster(int m_number);
};

#endif /* game_hpp */
