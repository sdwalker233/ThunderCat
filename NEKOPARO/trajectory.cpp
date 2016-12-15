//
//  trajectory.cpp
//  SDL_game
//
//  Created by shad0w_walker on 2016/12/12.
//  Copyright © 2016年 GKP. All rights reserved.
//

#include "trajectory.hpp"

Trajectory::Trajectory()
{
	shape = 0;
	dot[0] = IMG_Load("resources/pic/dot_white.png");
	dot[1] = IMG_Load("resources/pic/dot_black.png");
	dot[2] = IMG_Load("resources/pic/dot_red.png");
	dot[3] = IMG_Load("resources/pic/dot_blue.png");
	dot[4] = IMG_Load("resources/pic/dot_purple.png");
	dot[5] = IMG_Load("resources/pic/dot_green.png");
	dot[6] = IMG_Load("resources/pic/dot_yellow.png");
}

void Trajectory::clear()
{
	postions.clear();
	shape = 0;
}

void Trajectory::addPostion(SDL_Point point)
{
	SDL_Point start = point, tmp;
	if(!postions.empty()) start = postions.back();
	int num = max(abs(start.x-point.x), abs(start.y-point.y));
	float interx = (point.x-start.x)/(float)num;
	float intery = (point.y-start.y)/(float)num;
	for(int i = 1; i < num; i++){
		tmp.x = start.x + interx*i;
		tmp.y = start.y + intery*i;
		postions.push_back(tmp);
	}
	postions.push_back(point);
}

int Trajectory::recognize()
{
	int max_x=0, max_y=0, min_x=1000, min_y=1000;
	int max_x_pos=0, max_y_pos=0, min_x_pos=0, min_y_pos=0;
	for(int i = 1; i < postions.size(); i++){
		if(postions[i].x>max_x){
			max_x = postions[i].x;
			max_x_pos = i;
		}
		if(postions[i].x<min_x){
			min_x = postions[i].x;
			min_x_pos = i;
		}
		if(postions[i].y>max_y){
			max_y = postions[i].y;
			max_y_pos = i;
		}
		if(postions[i].y<min_y){
			min_y = postions[i].y;
			min_y_pos = i;
		}
	}
	if(max_x-min_x>4*(max_y-min_y)){
		shape = 2;
		return shape;
	}
	if(max_y-min_y>4*(max_x-min_x)){
		shape = 3;
		return shape;
	}
	
	int lpos, rpos;
	double laverang, raverang, sumang;
	sumang = 0;
	for(lpos=11; lpos <= 30; lpos++){
		sumang += atan2(postions[5].y-postions[lpos].y, postions[5].x-postions[lpos].x);
	}
	laverang = sumang/20;
	for(; lpos < postions.size(); lpos++){
		double tmpang = atan2(postions[5].y-postions[lpos].y, postions[5].x-postions[lpos].x);
		if(fabs(tmpang-laverang)>0.25) break;
		sumang += tmpang;
		laverang = sumang/(lpos-10);
	}
	
	sumang = 0;
	int lastpos = (int)postions.size()-1;
	for(rpos = lastpos-11; rpos >= lastpos-30; rpos--){
		sumang += atan2(postions[lastpos-5].y-postions[rpos].y, postions[lastpos-5].x-postions[rpos].x);
	}
	raverang = sumang/20;
	for(; rpos >= 0; rpos--){
		double tmpang = atan2(postions[lastpos-5].y-postions[rpos].y, postions[lastpos-5].x-postions[rpos].x);
		if(fabs(tmpang-raverang)>0.25) break;
		sumang += tmpang;
		raverang = sumang/(lastpos-rpos-10);
	}
	//printf(" %d %d %d\n",lpos,rpos,postions.size());
	//printf("  %f %f\n", laverang, raverang);
	if(laverang>-M_PI/2 && laverang<0 &&raverang>M_PI/2 && raverang<M_PI && lpos<rpos){
		shape = 6;
		return shape;
	}
	
	if(laverang>-M_PI && laverang<-M_PI/2 && raverang>-M_PI/2 && raverang<0){
		shape = 4;
		return shape;
	}
	if(laverang>M_PI/2 && laverang<M_PI && raverang>0 && raverang<M_PI/2){
		shape = 5;
		return shape;
	}
	/*if(fabs(max_y_pos-(int)postions.size()/2)<fabs(min_y_pos-(int)postions.size()/2.0)){
		shape = 4;
		return shape;
	}
	else{
		shape = 5;
		return shape;
	}*/
	return 0;
}

void Trajectory::clearSurface()
{
	if(sur != nullptr) SDL_FreeSurface(sur);
	sur = IMG_Load(emptyPNG);
	SDL_SetSurfaceBlendMode(sur,SDL_BLENDMODE_BLEND);//透明度模式
	SDL_SetSurfaceAlphaMod(sur,150);//设置透明度
}

void Trajectory::show()
{
	SDL_Rect rect = {0, 0, dotsize, dotsize};
	clearSurface();
	
	for (int i = 0; i < postions.size(); i++) {
		rect.x = postions[i].x - dotsize/2;
		rect.y = postions[i].y - dotsize/2;
		addSurface(dot[shape], &rect);
	}
	finishSurface();
	
	du.play();
}
