#include <SDL.h>
#include <iostream>

#include "bsp.hpp"
#include "editor.hpp"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

struct App
{
  SDL_Window* window;
  SDL_Renderer* renderer;
};

App app;
bool cont = true;

bool initApp(App& app){
  //sdl
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    std::cerr<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<std::endl;
    return false;
  }

  //window
  app.window = SDL_CreateWindow( "BSP-Test",
					 SDL_WINDOWPOS_UNDEFINED,
					 SDL_WINDOWPOS_UNDEFINED,
					 SCREEN_WIDTH,
					 SCREEN_HEIGHT,
					 0 );
  if(app.window == nullptr){
    std::cerr<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<std::endl;
    return false;
  }


  //renderer
  app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
  if(app.renderer == nullptr){
    std::cerr<<"Renderer could not be created! SDL_Error: "<<SDL_GetError()<<std::endl;
    return false;
  }

  //end
  return true;
}

void destroyApp(App& app){
  SDL_DestroyRenderer(app.renderer);
  SDL_DestroyWindow(app.window);
  SDL_Quit();
}

bool systemContinue(){
  return cont;
}

void systemQuit(){
  cont=false;
}

SDL_Renderer* systemGetRenderer(){
  return app.renderer;
}

int main( int argc, char* args[] )
{
  if(!initApp(app)){
    return 1;
  }

  BSP bsp;
  editor(bsp);

  destroyApp(app);
  return 0;
}
