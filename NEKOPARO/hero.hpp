//
//  hero.hpp
//  NEKOPARO
//
//  Created by shad0w_walker on 2016/12/20.
//  Copyright © 2016年 GKP. All rights reserved.
//

#ifndef hero_hpp
#define hero_hpp

#include "utility.h"
#include "component.hpp"

class Hero: public Component{
private:
	int staus, nextstatus, p;
	SDL_Surface* heroSurface[10][10];
	int len[10];
	clock_t last_time;
	SDL_Rect position;
	// 正常 0
	// - 2
	// | 3
	// V 4
	// ^ 5
	// lightning 6
	// scared 7
	// die 8
	//
public:
	Hero();
	void setPosition(int x, int y, int w=150, int h=150);
	void setStatus(int s);
	void show();
};

#endif /* hero_hpp */
