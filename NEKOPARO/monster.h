#include "utility.h"
#include "component.hpp"

const int MonsterWidth=352;
const int MonsterHeight=267;
const int ShapeWidth=20;
const int ShapeHeight=20;

class Monster:public Component{
private:
	string label;
	int type;
	double startpointX;
	double startpointY;
	double endingpointX;
	double endingpointY;
	double currentX;
	double currentY;
	double speed;
	SDL_Surface *monstersurface;
	SDL_Surface *shapesurface[6];
public:
	Monster();
	void show();
	void setType(int t);
	void setStart(double x,double y);
	void setEnding(double x,double y);
	void setSpeed(double speed);
	int getType();
	double getStartX();
	double getStartY();
	double getEndingX();
	double getEndingY();
	double getCurrentX();
	double getCurrentY();
	double getSpeed();
	void move();
	bool isReachEnding();
	void deleteLabel(int ch);
	bool isDead();
	void retreat();
};

