#include"monster.h"


string generateLabel()
{
	int MAXTIME=4,count,n;
	string res="";
	count=1+rand()%MAXTIME;		//最多产生5个符号
	for(int i=0;i<count;i++)
	{
		n=rand()%MAXTIME + 2;
		res += n+'0';
	}
	return res;
}


Monster::Monster()
{
	label=generateLabel();
	type=0;
	startpointX=0.0;
	startpointY=0.0;
	endingpointX=500.0;
	endingpointY=500.0;
	currentX=200.0;
	currentY=200.0;
	speed=1.0;
	monstersurface=IMG_Load("resources/pic/Aang.png");
	for(int i=2;i<6;i++)
	{
		char filename[30];
		sprintf(filename, "resources/pic/shape%d.png", i);
		shapesurface[i] = IMG_Load(filename);
	}
	cout<<label<<endl;
}

void Monster::show()
{
	SDL_Rect rect;
	SDL_Rect rect_monster={(int)currentX,(int)currentY,(int)MonsterWidth,(int)MonsterHeight};
	clearSurface();
	addSurface(monstersurface,&rect_monster);

	double firstx=MonsterWidth/2-label.length()*1.0*(ShapeWidth)/2+currentX;
	for(int i=0;i<label.length();i++)
	{
		rect.x=firstx+i*ShapeWidth;
		rect.y=currentY-ShapeHeight;
		rect.h=ShapeHeight;
		rect.w=ShapeWidth;
		addSurface(shapesurface[label[i]-'0'],&rect);
	}
	finishSurface();

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

void Monster::deleteLabel(int t)
{
	if(t == 6) label = "";
	if(label.length() && label[0] == '0'+t) label = label.substr(1, label.length());
}

bool Monster::isDead()
{
	if (label == "")
		return true;
	else
		return false;
}

void Monster::retreat()
{
	speed = -8.0;
}
