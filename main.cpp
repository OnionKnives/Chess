#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "game.h"
#include "board.h"
#include "input.h"
#include "graphics.h"

extern void initializeSprites();

int main(int argc, char* argv[]) {
	try {
		// Initialize SDL Systems
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw "SDL_Init: ";
		if (TTF_Init() != 0)
			throw "TTF_Init: ";
		if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
			throw "IMG_Init: ";
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			throw "Mix_Init: ";

		initializeGraphics();
		//loadMusic();
		//loadSFX();
		initializeSprites();
	}
	catch (const char* error) {
		SDL_Log("%s%s", error, SDL_GetError());
		shutdown();
	}

	// Initialize Game Parts
	initializeBoard();

	// Game Loop
	while (running()) {
		render();
		input();
		update();
	}

	shutdownGraphics();
	SDL_Quit();
	return 0;
}