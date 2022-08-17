#pragma once
#include <SDL.h>

void initializeGraphics();
void shutdownGraphics();
SDL_Texture* loadTextureFromFile(const char* filepath);

int screenWidth();
int screenHeight();
SDL_Renderer* getRenderer();

void render();