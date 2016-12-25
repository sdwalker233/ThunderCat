#ifndef status_hpp
#define status_hpp

#include "utility.h"
#include "component.hpp"
#include "mix_sound.hpp"

class Life: public Component{
private:
	int count;
	SDL_Surface *lifeSurface1, *lifeSurface2;
	EffectSound *hurt, *cured;
public:
	Life();
	void increase();
	void decrease();
	int getLife();
	void set(int x);
	void show();
};

class Score: public Component{
private:
	int score;
	TTF_Font *font;
	SDL_Color col;
public:
	Score();
	void add(int _score);
	int getScore();
	void set(int x);
	void show();
	void setColor(SDL_Color _col);
	//~Score();
};

class Lightning: public Component{
private:
	int num;
	SDL_Surface *lightningSurface1, *lightningSurface2;
	EffectSound *add;
public:
	Lightning();
	int getNum();
	void set(int x);
	void increase();
	void decrease();
	void show();
};
#endif /* status_hpp */
