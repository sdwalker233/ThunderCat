#include"monster.h"

Monster::Monster()
{
	label="";
	type=0;
	startpointX=0.0;
	startpointY=0.0;
	endingpointX=0.0;
	endingpointY=0.0;
	currentX=0.0;
	currentY=0.0;
	speed=0.0;
}

void Monster::Initial(SDL_Renderer *&render,SDL_Texture *&texture,string filename)
{
	texture = IMG_LoadTexture(render,filename.c_str());
	if(texture==nullptr)
	{
		cout<<"SDL_CeeateTexture Error:"<<SDL_GetError()<<endl;
	}
}

void Monster::setType(int t)
{
	this->type=t;
}

void Monster::setStart(double x,double y)
{
	this->startpointX=x;
	this->startpointY=y;
}

void Monster::setEnding(double x,double y)
{
	this->endingpointX=x;
	this->endingpointY=y;
}

void Monster::setSpeed(double speed)
{
	this->speed=speed;
}

int Monster::getType()
{
	return type;
}

double Monster::getStartX()
{
	return startpointX;
}

double Monster::getStartY()
{
	return startpointY;
}

double Monster::getEndingX()
{
	return endingpointX;
}

double Monster::getEndingY()
{
	return endingpointY;
}

double Monster::getSpeed()
{
	return speed;
}


double Monster::getCurrentX()
{
	return this->currentX;
}

double Monster::getCurrentY()
{
	return this->currentY;
}

void Monster::move()
{
	currentX+=speed*cos(atan2(endingpointY-startpointY,endingpointX-startpointX));
	currentY+=speed*sin(atan2(endingpointY-startpointY,endingpointX-startpointX));
}
bool Monster::isReachEnding()
{
	if(currentX>endingpointX||currentY>endingpointY)
		return true;
	else 
		return false;
}


