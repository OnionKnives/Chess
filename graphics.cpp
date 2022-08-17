#include <string>
#include <SDL_image.h>

#include "game.h"
#include "board.h"
#include "graphics.h"

using namespace std;

struct WindowData {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	int width = 1280;
	int height = 720;
} window;

void initializeGraphics() {
	try {
		window.window = SDL_CreateWindow("Chess",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			window.width, window.height,
			0);

		if (window.window == nullptr)
			throw "Window failed to initialize";

		window.renderer = SDL_CreateRenderer(window.window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (window.renderer == nullptr)
			throw "Renderer failed to initialize";

		SDL_SetRenderDrawBlendMode(window.renderer, SDL_BLENDMODE_BLEND);
	}
	catch (const char* error) {
		SDL_Log("%s, %s", error, SDL_GetError());
	}
}

void shutdownGraphics() {
	SDL_DestroyRenderer(window.renderer);
	SDL_DestroyWindow(window.window);
}

int screenWidth() {
	return window.width;
}

int screenHeight() {
	return window.height;
}

SDL_Renderer* getRenderer() {
	return window.renderer;
}

void render() {
	SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(getRenderer());

	renderBoard();
	renderPieces();

	SDL_RenderPresent(getRenderer());
}