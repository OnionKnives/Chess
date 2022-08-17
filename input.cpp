#include <map>
#include <SDL.h>
#include <sstream>

#include "input.h"

using namespace std;

bool gameRunning = true;
map<SDL_Keycode, bool> keymap;
map<Uint8, MouseState> mousemap;
SDL_Point mousePos;

bool newChar = false;
char textInput;

void input() {
	SDL_Event event;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	mousemap[SDL_BUTTON_LEFT] = MouseState::None;
	mousemap[SDL_BUTTON_RIGHT] = MouseState::None;
	mousemap[SDL_BUTTON_MIDDLE] = MouseState::None;

	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT)
			shutdown();

		else if (event.type == SDL_TEXTINPUT) {
			newChar = true;
			textInput = *event.text.text;
		}

		else if (event.type == SDL_KEYDOWN)
			keymap[event.key.keysym.sym] = true;
		else if (event.type == SDL_KEYUP)
			keymap[event.key.keysym.sym] = false;

		else if (event.type == SDL_MOUSEBUTTONDOWN)
			mousemap[event.button.button] = MouseState::Down;
		else if (event.type == SDL_MOUSEBUTTONUP)
			mousemap[event.button.button] = MouseState::Up;
	}
}

bool running() {
	return gameRunning;
}

void shutdown() {
	gameRunning = false;
}

bool keyPressed(int key) {
	bool result = false;

	if (keymap.find(key) != keymap.end()) {
		result = keymap[key];
	}

	return result;
}

MouseState mouseClick(Uint8 key) {
	MouseState state = MouseState::None;

	if (mousemap.find(key) != mousemap.end())
		state = mousemap[key];

	return state;
}

void mousePosition(SDL_Point* p) {
	p->x = mousePos.x;
	p->y = mousePos.y;
}

bool newCharInput() {
	return newChar;
}

char getTextInputChar() {
	newChar = false;
	return textInput;
}