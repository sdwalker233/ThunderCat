//
//  utility.h
//  NEKOPARO
//
//  Created by shad0w_walker on 2016/12/14.
//  Copyright © 2016年 GKP. All rights reserved.
//

#ifndef utility_h
#define utility_h

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#define ONE_SECOND 1000000
#elif __UNIX__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#define ONE_SECOND 1000000
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#define ONE_SECOND 1000
#endif
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

const int windowWidth = 800;
const int windowHeight = 600;
const SDL_Rect FULL_RECT = {0, 0, windowWidth, windowHeight};
const int dotsize = 13;//dot in trajectory
const int MAX_LIFE = 5;
const int MAX_LIGHTNING = 3;

#define emptyPNG "resources/pic/empty.png"
#define blackPNG "resources/pic/black.png"

const SDL_Color BLACK = {0, 0, 0, 80};
const SDL_Color WHITE = {255, 255, 255, 80};
/*
  shape&color
           0->white		'#ffffff'
           1->black		'#000000'
    '-'    2->red		'#fc0d1e'
    '|'    3->blue		'#182afb'
    'V'    4->yellow	'#fef359'
    '^'    5->green		'#40fd5b'
 lightning 6->gold		'#fbbe2e'
 
*/


#endif /* utility_h */

