ThunderCat
===
* ThunderCat is a simple game with **SDL2**.  
* You can play it on any platform (Windows or MacOS or Linux).
* Inspired by and get some resources from [Google-Halloween-2016](https://www.google.com/doodles/halloween-2016).
  
Compile
---
```
cd ThunderCat
g++ -O3 -std=c++11 src/*.cpp -Isrc/ -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -o thundercat
./thundercat
```
Also you can open with VS or Xcode, just add [SDL2](https://www.libsdl.org/download-2.0.php), [SDL2_image](https://www.libsdl.org/projects/SDL_image/), [SDL2_TTF](https://www.libsdl.org/projects/SDL_ttf/), [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/).

Downloads
---
* [__Download page__](https://github.com/shad0w-walker233/ThunderCat/releases/tag/v1.1)

Screenshot
---
![menu.jpg](screenshot/menu.jpg)
![game.jpg](screenshot/game.jpg)