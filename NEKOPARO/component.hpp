//
//  component.hpp
//  SDL_game
//
//  Created by shad0w_walker on 2016/12/15.
//  Copyright © 2016年 GKP. All rights reserved.
//

#ifndef component_hpp
#define component_hpp

#include "utility.h"

class Component{
private:
	SDL_Renderer *ren;
protected:
	SDL_Texture *tex;
	SDL_Surface *sur;
public:
	Component();
	void setRender(SDL_Renderer *_ren);
	SDL_Texture* getTexture();
	virtual void clearSurface();
	void addSurface(SDL_Surface* _sur, SDL_Rect* _rect);
	void finishSurface();
};

#endif /* component_hpp */
