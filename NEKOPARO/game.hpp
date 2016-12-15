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

class Game{
private:
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Event event;
	Trajectory tra;
	Life life;
	Score score;
	SDL_Texture *tex_background;
public:
	Game();
	~Game();
	void run();
	void show();
};

#endif /* game_hpp */
