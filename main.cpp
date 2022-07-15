#include <iostream>
#include "SDL2/SDL.h"
#include "GL/gl.h"
int main()
{
	/*SDL_Window* m_sdlWindow;
	float screenWidth = 200;
	float screenHeight = 200;
SDL_GLContext m_glContext;
Uint32 m_flag = SDL_WINDOW_OPENGL;
	m_sdlWindow = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, m_flag);
glewInit();*/
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("Engine",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       300, 300, 0);
    while (1)
        ;
//nothing here
return 0;
}
