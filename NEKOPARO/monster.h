#include "utility.h"

class Monster{
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

public:
	Monster();
	void Initial(SDL_Renderer *&render,SDL_Texture *&texture,string filename);
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
};

