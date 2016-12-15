//
//  trajectory.hpp
//  SDL_game
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
	EffectSound *du;
public:
	Trajectory();
	void addPostion(SDL_Point point);
	int recognize();
	void show();
	void clear();
	void clearSurface();
};

#endif /* trajectory_hpp */
