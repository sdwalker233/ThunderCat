#ifndef hero_hpp
#define hero_hpp

#include "utility.h"
#include "component.hpp"
#include "mix_sound.hpp"

class Hero: public Component{
private:
	int staus, p;
	SDL_Surface* heroSurface[15][12];
	int len[15];
	Uint32 last_time;
	SDL_Rect position;
	// 正常 0
	// - 2
	// | 3
	// V 4
	// ^ 5
	// lightning 6
	// scared 7
	// die 8
	// hurt 9
	// win 10
public:
	Hero();
	void setPosition(int x, int y, int w=150, int h=150);
	void setStatus(int s);
	void show();
};

#endif /* hero_hpp */
