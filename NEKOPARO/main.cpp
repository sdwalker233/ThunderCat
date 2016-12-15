#include "utility.h"
#include "game.hpp"

void SDLInit()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		throw SDL_GetError();
	}
	std::cout << "Init SDL successfully." << std::endl;
	TTF_Init();
}

void SDLQuit()
{
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char * argv[])
{
	try {
		SDLInit();
	} catch(const char* s) {
		std::cerr << s << std::endl;
		return -1;
	}
	
	Game game;
	game.run();
	
	SDLQuit();
	return 0;
}

