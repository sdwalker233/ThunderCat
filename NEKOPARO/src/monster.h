#include "utility.h"
#include "component.hpp"

const int MonsterWidth=100;
const int MonsterHeight=76;
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
	bool isout;
	int minlabel,maxlabel;
public:
	Monster();
	void show();
	void setType(int t);
	void setStart(double x,double y);
	void setEnd(double x,double y);
	void setSpeed(double speed);
	int getType();
	double getStartX();
	double getStartY();
	double getEndX();
	double getEndY();
	double getCurrentX();
	double getCurrentY();
	double getSpeed();
	void move();
	bool isReachEnd();
	bool isReachStart();
	int deleteLabel(int ch);
	bool isDead();
	void retreat();
	bool isOut();
	string generateLabel(int l, int r);
	void setLabelLen(int l, int r);
	void setLabel(const string& s);
	//~Monster();
};

