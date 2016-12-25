#ifndef component_hpp
#define component_hpp

#include "utility.h"

class Component{
private:
	SDL_Renderer *ren;
protected:
	SDL_Texture *tex;
	SDL_Surface *sur;
	bool visible;
public:
	Component();
	void setRender(SDL_Renderer *_ren);
	virtual SDL_Texture* getTexture();
	virtual void clearSurface();
	void addSurface(SDL_Surface* _sur, SDL_Rect* _rect);
	void finishSurface();
	void setVisible(bool _visible);
};

#endif /* component_hpp */
