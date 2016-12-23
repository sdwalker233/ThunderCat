//
//  trajectory.hpp
//  NEKOPARO
//
//  Created by shad0w_walker on 2016/12/12.
//  Copyright © 2016年 GKP. All rights reserved.
//

#ifndef trajectory_hpp
#define trajectory_hpp

#include "utility.h"
#include "component.hpp"
#include "mix_sound.hpp"

class Trajectory: public Component {
private:
	SDL_Surface *dot[7];
	vector<SDL_Point> positions;
	int shape;
	EffectSound *du, *lightning;
	clock_t start_time;
	int lasti, lastshape;
public:
	Trajectory();
	//Trajectory(const Trajectory& tra);
	void addPostion(SDL_Point point);
	int recognize();
	void show();
	void clear();
	void clearSurface();
	SDL_Texture* getTexture();
};

#endif /* trajectory_hpp */
