//
//  hero.cpp
//  NEKOPARO
//
//  Created by shad0w_walker on 2016/12/20.
//  Copyright © 2016年 GKP. All rights reserved.
//

#include "hero.hpp"

Hero::Hero()
{
	char filename[50];
	staus = 0;
	last_time = 0;
	len[0] = 8;len[1] = 0;len[2] = 4;len[3] = 5;
	len[4] = 4;len[5] = 4;len[6] = 4;len[7] = 6;
	len[8] = 5;len[9] = 4;len[10] = 13;
	for(int i = 0; i <= 10; i++){
		for(int j = 0; j < len[i]; j++){
			sprintf(filename, "resources/pic/hero/%d%d.png", i, j);
			heroSurface[i][j] = IMG_Load(filename);
		}
	}
}

void Hero::setPosition(int x, int y, int w, int h)
{
	position.x = x;
	position.y = y;
}

void Hero::setStatus(int s)
{
	staus = s;
	p = 0;
}

void Hero::show()
{
	if(clock() - last_time<ONE_SECOND/8) return;
	last_time = clock();
	clearSurface();
	cout<<staus<<" "<<p<<endl;
	addSurface(heroSurface[staus][p++], &position);
	if(p==len[staus]){
		if(staus == 8 || staus == 10){
			p--;
		}
		else{
			staus = 0;
			p = 0;
		}
	}
	finishSurface();
}
