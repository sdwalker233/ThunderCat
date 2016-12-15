//
//  status.hpp
//  SDL_game
//
//  Created by shad0w_walker on 2016/12/15.
//  Copyright © 2016年 GKP. All rights reserved.
//

#ifndef status_hpp
#define status_hpp

#include "utility.h"
#include "component.hpp"
class Life: public Component{
private:
	int count;
	SDL_Surface *lifeSurface1, *lifeSurface2;
public:
	Life();
	void increase();
	void decrease();
	int getLife();
	void show();
};

class Score: public Component{
private:
	int score;
	TTF_Font *font;
public:
	Score();
	void add(int _score);
	int getScore();
	void show();
	//~Score();
};
#endif /* status_hpp */
