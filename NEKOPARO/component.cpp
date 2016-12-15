//
//  component.cpp
//  SDL_game
//
//  Created by shad0w_walker on 2016/12/15.
//  Copyright © 2016年 GKP. All rights reserved.
//

#include "component.hpp"

Component::Component()
{
	tex = nullptr;
	sur = nullptr;
}

void Component::setRender(SDL_Renderer *_ren)
{
	ren = _ren;
}

SDL_Texture* Component::getTexture()
{
	return tex;
}

void Component::clearSurface()
{
	if(sur != nullptr) SDL_FreeSurface(sur);
	sur = IMG_Load(emptyPNG);
}

void Component::addSurface(SDL_Surface *_sur, SDL_Rect *_rect)
{
	SDL_UpperBlit(_sur, NULL, sur, _rect);
}

void Component::finishSurface()
{
	if(tex != nullptr) SDL_DestroyTexture(tex);
	tex = SDL_CreateTextureFromSurface(ren, sur);
}
