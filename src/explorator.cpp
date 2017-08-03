#include "explorator.hpp"

#include <SDL.h>
#include <iostream>

#include "editor.hpp"
#include "system.hpp"

void explorator(BSP& bsp){
  SDL_Renderer* renderer = systemGetRenderer();
 
  Vector2<int> mouse;
  
  bool toEditor = false;
  
  while (systemContinue() && !toEditor) {
    //event
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      switch(e.type){
      case SDL_QUIT:
	systemQuit();
	break;
      case SDL_KEYDOWN:
	if(e.key.keysym.sym==SDLK_F5){
	  toEditor = true;
	}
	break;
      default:
	break;
      }
    }
    Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
    
    //begin draw
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);

    //walls
    for(unsigned int i(0);i<bsp.getNumberOfWalls();i++){
      Wall w=bsp.getWall(i);
      SDL_SetRenderDrawColor(renderer, 0,0,255,255);
      SDL_RenderDrawLine(renderer, w.p1.x, w.p1.y, w.p2.x, w.p2.y);
		
      Vector2f p1=w.p1+w.p2;
      p1/=2.0f;
      Vector2f p2=p1+w.normal*10.0f;
      SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    }

    //mouse
    Vector2f mousef = {static_cast<float>(mouse.x), static_cast<float>(mouse.y)};
    if(bsp.testPoint(mousef)){
      SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    }else{
      SDL_SetRenderDrawColor(renderer, 0,255,0,255);
    }

    SDL_Rect rect = {mouse.x-10, mouse.y-10, 20,20};
    SDL_RenderDrawRect(renderer, &rect);

    //end
    SDL_RenderPresent(renderer);
  }

  if(toEditor){
    editor(bsp);
  }
}
