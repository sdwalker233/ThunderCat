#include "component.hpp"

Component::Component()
{
	tex = nullptr;
	sur = nullptr;
	visible = true;
}

void Component::setRender(SDL_Renderer *_ren)
{
	ren = _ren;
}

SDL_Texture* Component::getTexture()
{
	if(visible)	return tex;
	else return nullptr;
}

void Component::clearSurface()
{
	if(sur != NULL) SDL_FreeSurface(sur);
	sur = IMG_Load(emptyPNG);
}

void Component::addSurface(SDL_Surface *_sur, SDL_Rect *_rect)
{
	SDL_UpperBlit(_sur, NULL, sur, _rect);
}

void Component::finishSurface()
{
	if(tex != NULL) SDL_DestroyTexture(tex);
	tex = SDL_CreateTextureFromSurface(ren, sur);
}

void Component::setVisible(bool _visible)
{
	visible = _visible;
}
