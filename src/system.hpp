#pragma once

struct SDL_Renderer;

bool systemContinue();
void systemQuit();
SDL_Renderer* systemGetRenderer();
