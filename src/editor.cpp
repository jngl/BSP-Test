#include "editor.hpp"

#include <SDL.h>
#include <iostream>

#include "system.hpp"
#include "explorator.hpp"

Vector2f magnetize(Vector2f p)
{
  Vector2f p2;
  p2.x=p.x-(int)p.x%20+10;
  p2.y=p.y-(int)p.y%20+10;
  return p2;
}

void editor(BSP& bsp){
  SDL_Renderer* renderer = systemGetRenderer();

  Vector2f oldPoint;
  Vector2<int> mouse;
  Vector2f mouseMagnetize;

  bool toExplorator = false;
  
  while (systemContinue() && !toExplorator) {
    //event
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      switch(e.type){
      case SDL_QUIT:
	systemQuit();
	break;
      case SDL_KEYDOWN:
	if(e.key.keysym.sym==SDLK_F5){
	  toExplorator = true;
	}
	break;
      case SDL_MOUSEBUTTONDOWN:
	oldPoint = magnetize({static_cast<float>(e.button.x), static_cast<float>(e.button.y)});
	break;
      case SDL_MOUSEBUTTONUP:
	bsp.addWall(oldPoint,magnetize({static_cast<float>(e.button.x), static_cast<float>(e.button.y)}));
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

    //current
    if(mouseState!=0){
      Wall w;
      w.p2.x=static_cast<float>(mouse.x);
      w.p2.y=static_cast<float>(mouse.y);
      w.p2=magnetize(w.p2);
      w.p1=oldPoint;

      SDL_SetRenderDrawColor(renderer, 0,255,0,255);
      SDL_RenderDrawLine(renderer, w.p1.x, w.p1.y, w.p2.x, w.p2.y);
      
      Vector2f p1=oldPoint+w.p2;
      p1/=2.0f;
      Vector2f p2=p1+getNormal(w.p1,w.p2)*10.0f;
      
      SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    }
    
    //mouse
    mouseMagnetize = magnetize({static_cast<float>(mouse.x), static_cast<float>(mouse.y)});
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    SDL_RenderDrawPoint(renderer, mouseMagnetize.x, mouseMagnetize.y);

    //end
    SDL_RenderPresent(renderer);
  }

  if(toExplorator){
    bsp.build();
    explorator(bsp);
  }
}

