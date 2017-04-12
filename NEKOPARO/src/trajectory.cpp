#include "trajectory.hpp"

Trajectory::Trajectory()
{
	shape = 0;
	dot[0] = IMG_Load("resources/pic/dot_white.png");
	dot[1] = IMG_Load("resources/pic/dot_black.png");
	dot[2] = IMG_Load("resources/pic/dot_red.png");
	dot[3] = IMG_Load("resources/pic/dot_blue.png");
	dot[4] = IMG_Load("resources/pic/dot_yellow.png");
	dot[5] = IMG_Load("resources/pic/dot_green.png");
	dot[6] = IMG_Load("resources/pic/dot_gold.png");
	du = new EffectSound("resources/music/du.wav");
	lightning = new EffectSound("resources/music/lightning.wav");
}

void Trajectory::clear()
{
	positions.clear();
	clearTexture();
	shape = 0;
	setVisible(true);
	start_time = 0;
	lasti = 0;
	lastshape = -1;
}

void Trajectory::addPostion(SDL_Point point)
{
	SDL_Point start = point, tmp;
	if(!positions.empty()) start = positions.back();
	int num = fmax(abs(start.x-point.x), abs(start.y-point.y));
	float interx = (point.x-start.x)/(float)num;
	float intery = (point.y-start.y)/(float)num;
	for(int i = 1; i < num; i++){
		tmp.x = start.x + interx*i;
		tmp.y = start.y + intery*i;
		positions.push_back(tmp);
	}
	positions.push_back(point);
	start_time = clock();
}

int Trajectory::recognize()
{
	//start_time = clock();
	if(positions.size() < 10) return 0;
	int max_x=0, max_y=0, min_x=1000, min_y=1000;
	int max_x_pos=0, max_y_pos=0, min_x_pos=0, min_y_pos=0;
	for(int i = 1; i < positions.size(); i++){
		if(positions[i].x>max_x){
			max_x = positions[i].x;
			max_x_pos = i;
		}
		if(positions[i].x<min_x){
			min_x = positions[i].x;
			min_x_pos = i;
		}
		if(positions[i].y>max_y){
			max_y = positions[i].y;
			max_y_pos = i;
		}
		if(positions[i].y<min_y){
			min_y = positions[i].y;
			min_y_pos = i;
		}
	}
	if(max_x-min_x>4*(max_y-min_y)){
		shape = 2;
		du->play();
		return shape;
	}
	if(max_y-min_y>4*(max_x-min_x)){
		shape = 3;
		du->play();
		return shape;
	}
	
	if(positions.size() <= 40) return 0;
	int lpos, rpos;
	double laverang, raverang, sumang;
	sumang = 0;
	for(lpos=21; lpos <= 40; lpos++){
		sumang += atan2(1.0*positions[10].y-positions[lpos].y, 1.0*positions[10].x-positions[lpos].x);
	}
	laverang = sumang/20;
	for(; lpos < positions.size(); lpos++){
		double tmpang = atan2(1.0*positions[10].y-positions[lpos].y, 1.0*positions[10].x-positions[lpos].x);
		if(fabs(tmpang-laverang)>0.25) break;
		sumang += tmpang;
		laverang = sumang/(lpos-20);
	}
	
	sumang = 0;
	int lastpos = (int)positions.size()-1;
	for(rpos = lastpos-21; rpos >= lastpos-40; rpos--){
		sumang += atan2(1.0*positions[lastpos-10].y-positions[rpos].y, 1.0*positions[lastpos-10].x-positions[rpos].x);
	}
	raverang = sumang/20;
	for(; rpos >= 0; rpos--){
		double tmpang = atan2(1.0*positions[lastpos-10].y-positions[rpos].y, 1.0*positions[lastpos-10].x-positions[rpos].x);
		if(fabs(tmpang-raverang)>0.25) break;
		sumang += tmpang;
		raverang = sumang/(lastpos-rpos-20);
	}
	//printf(" %d %d %d\n",lpos,rpos,positions.size());
	//printf("  %f %f\n", laverang, raverang);
	if(laverang>-M_PI/2 && laverang<0 &&raverang>M_PI/2 && raverang<M_PI && lpos<rpos){
		lightning->play();
		shape = 6;
		return shape;
	}
	
	if(laverang>-M_PI && laverang<-M_PI/2 && raverang>-M_PI/2 && raverang<0){
		shape = 4;
		du->play();
		return shape;
	}
	if(laverang>M_PI/2 && laverang<M_PI && raverang>0 && raverang<M_PI/2){
		shape = 5;
		du->play();
		return shape;
	}
	/*if(fabs(max_y_pos-(int)positions.size()/2)<fabs(min_y_pos-(int)positions.size()/2.0)){
		shape = 4;
		return shape;
	}
	else{
		shape = 5;
		return shape;
	}*/
	return 0;
}

void Trajectory::clearSurface()
{
	if(sur != nullptr) SDL_FreeSurface(sur);
	sur = IMG_Load(emptyPNG);
	SDL_SetSurfaceBlendMode(sur,SDL_BLENDMODE_BLEND);
	SDL_SetSurfaceAlphaMod(sur,150);
}

void Trajectory::show()
{
	if(start_time > 0 && clock() - start_time>ONE_SECOND)
		setVisible(false);
	if(positions.size() < 5) return;
	SDL_Rect rect = {0, 0, dotsize, dotsize};
	
	//if(lasti == 0) clearSurface();
	if(lastshape != shape){
		clearSurface();
		lastshape = shape;
		lasti = 0;
	}
	for (int i = lasti; i < positions.size(); i++) {
		rect.x = positions[i].x - dotsize/2;
		rect.y = positions[i].y - dotsize/2;
		addSurface(dot[shape], &rect);
	}
	finishSurface();
	lasti = (int)positions.size();
}

SDL_Texture* Trajectory::getTexture()
{
	
	if(start_time > 0 && clock() - start_time>ONE_SECOND)
		setVisible(false);
	if(visible)	return tex;
	else return nullptr;
}
